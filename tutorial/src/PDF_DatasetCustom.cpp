#include "PDF_DatasetCustom.h"
#include "RooExponential.h"
#include "RooMinimizer.h"
#include "TMath.h"

PDF_DatasetCustom::PDF_DatasetCustom(RooWorkspace* w): PDF_Datasets(w){};
PDF_DatasetCustom::~PDF_DatasetCustom(){};

RooFitResult* PDF_DatasetCustom::fit(RooDataSet* dataToFit) {

    if (this->getWorkspace()->set(constraintName) == NULL) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "ERROR: No RooArgSet with constraints found." << std::endl;
        std::cout << "The Workspace must contain a RooArgSet with constraint PDFs." << std::endl;
        std::cout << "These are usually Gaussians that constrain parameters via global observables." << std::endl;
        std::cout << "This set can be empty." << std::endl;
        std::cout << "By default its name should be 'default_internal_constraint_set_name'." << std::endl;
        std::cout << "Other names can be passed via PDF_Datasets::initConstraints" << std::endl;
        exit(EXIT_FAILURE);
    }

    RooWorkspace* w = this->getWorkspace();
    RooRealVar* m_var = w->var(massVarName.c_str());
    m_var->setRange("full", 4720, 6520);
    m_var->setRange("lsb", 4720, 5000);
    m_var->setRange("rsb", 5800, 6520);

    // Turn off RooMsg
    RooMsgService::instance().setGlobalKillBelow(ERROR);
    RooMsgService::instance().setSilentMode(kTRUE);

    // Choose Dataset to fit to
    // unfortunately Minuit2 does not initialize the status of the roofitresult, if all parameters are constant. Therefore need to stay with standard Minuit fitting.
    // RooFitResult* result  = pdf->fitTo( *dataToFit, RooFit::Save() , RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)), RooFit::Minimizer("Minuit2", "Migrad"));
    RooFitResult* result  = pdf->fitTo( *dataToFit, RooFit::Save() , RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)), RooFit::Extended(kTRUE));

    if(sanity){
        plotting((plotDir+"SignalBGFit").c_str(), dataToFit, counterSB, 0);
        counterSB=counterSB+1;
    }
    
    this->fitStatus = result->status();
    // RooAbsReal* nll = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE))
    RooAbsReal* nll = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)));
    this->minNll = nll->getVal();
    std::cout << "Wifi: Fit Status=" << this->fitStatus << ": Nll=" << this->minNll <<std::endl;
    fitFile << "Fit Status=" << this->fitStatus << ": Nll=" << this->minNll <<std::endl;

    RooMsgService::instance().setSilentMode(kFALSE);
    RooMsgService::instance().setGlobalKillBelow(INFO);


    delete nll;

    return result;
};


RooFitResult* PDF_DatasetCustom::fitBkg(RooDataSet* dataToFit) {

    if (this->getWorkspace()->set(constraintName) == NULL) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "ERROR: No RooArgSet with constraints found." << std::endl;
        std::cout << "The Workspace must contain a RooArgSet with constraint PDFs." << std::endl;
        std::cout << "These are usually Gaussians that constrain parameters via global observables." << std::endl;
        std::cout << "This set can be empty." << std::endl;
        std::cout << "By default its name should be 'default_internal_constraint_set_name'." << std::endl;
        std::cout << "Other names can be passed via PDF_Datasets::initConstraints" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!pdfBkg)
    {
        std::cout << "ERROR in PDF_Datasets::fitBkg -- No background PDF given!" << std::endl;
        exit(EXIT_FAILURE);
    }
    double parvalue = getWorkspace()->var("BFsig")->getVal();
    bool isconst = getWorkspace()->var("BFsig")->isConstant();
    getWorkspace()->var("BFsig")->setVal(0.0);
    getWorkspace()->var("BFsig")->setConstant(true);

    // Turn off RooMsg
    RooMsgService::instance().setGlobalKillBelow(ERROR);
    RooMsgService::instance().setSilentMode(kTRUE);
    // Choose Dataset to fit to

    // unfortunately Minuit2 does not initialize the status of the roofitresult, if all parameters are constant. Therefore need to stay with standard Minuit fitting.
    // RooFitResult* result  = pdfBkg->fitTo( *dataToFit, RooFit::Save() , RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)), RooFit::Minimizer("Minuit2", "Migrad"));

    RooFitResult* result  = pdf->fitTo( *dataToFit, RooFit::Save() , RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)), RooFit::Extended(kTRUE));
    // RooFitResult* result  = pdfBkg->fitTo( *dataToFit, RooFit::Save() , RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)), RooFit::Extended(kTRUE));
    RooMsgService::instance().setSilentMode(kFALSE);
    RooMsgService::instance().setGlobalKillBelow(INFO);
    this->fitStatus = result->status();
    
    if(sanity){
        plotting((plotDir+"BackgroundFit").c_str(), dataToFit, counterBG, 0);
        counterBG=counterBG+1;
    }

    // RooAbsReal* nll_bkg = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE));
    // RooAbsReal* nll_bkg = pdfBkg->createNLL(*dataToFit, RooFit::Extended(kTRUE));
    RooAbsReal* nll_bkg = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)));
    // RooAbsReal* nll_bkg = pdfBkg->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)));
    this->minNllBkg = nll_bkg->getVal();
    std::cout << "Intranet: Fit Status=" << this->fitStatus << ": Nll=" << this->minNllBkg <<std::endl;
    fitBGFile << "Fit Status=" << this->fitStatus << ": Nll=" << this->minNllBkg <<std::endl;
    getWorkspace()->var("BFsig")->setVal(parvalue);
    getWorkspace()->var("BFsig")->setConstant(isconst);    

    delete nll_bkg;

    return result;
};

void   PDF_DatasetCustom::generateToys(int SeedShift) {

    initializeRandomGenerator(SeedShift);
    RooDataSet* toys = this->pdf->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
    //toys->Print("v");

    if(sanity){
        plotting((plotDir+"ToyDataSet").c_str(), toys, counter, 1);
        counter=counter+1;
    }

    // Having the delete in here causes a segmentation fault, likely due to a double free
    // related to Root's internal memory management. Therefore we do not delete,
    // which might or might not cause a memory leak.
    // if(this->toyObservables) delete this->toyObservables;
    this->toyObservables  = toys;
    this->isToyDataSet    = kTRUE;
};

void PDF_DatasetCustom::generateBkgToys(int SeedShift) {

    initializeRandomGenerator(SeedShift);

    if(isBkgPdfSet){
        std::string massVarname="Lb_DTFLambdaPV_M";
        double parvalue = getWorkspace()->var("BFsig")->getVal();
        bool isconst = getWorkspace()->var("BFsig")->isConstant();
        getWorkspace()->var("BFsig")->setVal(0.0);
        getWorkspace()->var("BFsig")->setConstant(true);
        // RooDataSet* toys = pdfBkg->generate(*observables, RooFit::NumEvents(wspc->data(dataName)->numEntries()), RooFit::Extended(kTRUE));
        //RooDataSet* toys = pdf->generate(*observables, RooFit::NumEvents(wspc->data(dataName)->numEntries()), RooFit::Extended(kTRUE));
        RooDataSet* toys = pdf->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
	//RooDataSet* toys = pdf->generate(RooArgSet(wspc->var(massVarname.c_str()), wspc->cat("category")),0,kFALSE,kTRUE,"",kFALSE,kTRUE)
    
        if(sanity){
            plotting((plotDir+"ToyBGDataSet").c_str(), toys, counterToy, 1);
            counterToy=counterToy+1;
        }

        getWorkspace()->var("BFsig")->setVal(parvalue);
        getWorkspace()->var("BFsig")->setConstant(isconst);    
        //toys->Print("v");
        this->toyBkgObservables  = toys;
    }
    else{
        std::cerr << "Error in PDF_Datasets::generateBkgToys: No bkg pdf given." << std::endl;
        exit(EXIT_FAILURE);
    }
};


void PDF_DatasetCustom::plotting(std::string plotString, RooDataSet* data, int count, bool isToy){
    RooWorkspace* w = this->getWorkspace();
    RooRealVar* m_var = w->var(massVarName.c_str());
    m_var->setRange("full", 4720, 6520);
    m_var->setRange("lsb", 4720, 5000);
    m_var->setRange("rsb", 5800, 6520);
    
    if(!isToy){
        std::string categories[8] = {"Brem_DD_Run1","Brem_LL_Run1","NoBrem_DD_Run1","NoBrem_LL_Run1","Brem_DD_Run2","Brem_LL_Run2","NoBrem_DD_Run2","NoBrem_LL_Run2"};

        for(int i=0; i<8; i++){
            std::string cat = categories[i];
            TCanvas* canvas = new TCanvas(Form("c%i",i),Form("c%i",i),600,600);
            RooPlot* frame = w->var(massVarName.c_str())->frame();
            std::string cutting = "category==category::"+cat;
            data->plotOn(frame,RooFit::Cut(cutting.c_str()));
            //pdf->plotOn(frame);
            RooCategory* slicedCategory = w->cat("category");
            pdf->plotOn(frame,RooFit::Slice(*slicedCategory,cat.c_str()), RooFit::ProjWData(*data), RooFit::NormRange("lsb,rsb"));

            frame->Draw();
            std::string plotOutput = plotString+"_"+to_string(count)+"_"+cat+".pdf";
            canvas->SaveAs((plotOutput).c_str());
            canvas->Close();
        }
    }
    else{
            TCanvas* canvas = new TCanvas("cToy","cToy",600,600);
            RooPlot* frame = w->var(massVarName.c_str())->frame();
            data->plotOn(frame);
            pdf->plotOn(frame,RooFit::ProjWData(*data), RooFit::NormRange("full"));
            frame->Draw();
            plotString = plotString+"_"+to_string(count)+".pdf";
            canvas->SaveAs((plotString).c_str());
            canvas->Close();
    }
};
