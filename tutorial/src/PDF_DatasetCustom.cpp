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

    /*
    RooWorkspace* w = this->getWorkspace();
    RooRealVar* m_var = w->var(massVarName.c_str());
    m_var->setRange("full", 4720, 6520);
    m_var->setRange("lsb", 4720, 5000);
    m_var->setRange("rsb", 5800, 6520);
    */

    // Turn off RooMsg
    RooMsgService::instance().setGlobalKillBelow(ERROR);
    RooMsgService::instance().setSilentMode(kTRUE);

    //RooAbsReal* nll = pdf->createNLL(*dataToFit,RooFit::Range("lsb,rsb"),RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)),RooFit::Extended(kTRUE)); 
    RooAbsReal* nll = pdf->createNLL(*dataToFit, RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)),RooFit::Extended(kTRUE)); 
    this->minNll = nll->getVal();
    //subtract initial value from likelihood, to improve precision in case it's very large
    double nll_init_val = nll->getVal(nll->getVariables());
    RooAbsArg* arg = (RooAbsArg*)nll;
    std::string nllString= "@0-"+to_string(nll_init_val);
    RooFormulaVar nll_toFit = RooFormulaVar("nll_norm", nllString.c_str() , RooArgList(*arg, "nll_list"));

    RooMinimizer m = RooMinimizer(nll_toFit);
    m.setStrategy(this->fitStrategy);
    m.setMaxFunctionCalls(500000);
    m.setMaxIterations(100000);
    RooFitResult* result;
    int i = 0;

    std::cout << "=====================================" <<std::endl;

    m.simplex();
    //loop until convergence
    /*
        -1 = Not Available
         0 = Available but not positive definite
         1 = covariance only approximate
         2 = full matrix but forced positive definite
         3 = Full Accurate matrix
    */
    while (i==0 or result->covQual()<3){
        m.migrad();
        m.hesse();
        result = m.save();
        i=i+1;
        std::cout << "covQual=" << result->covQual() <<std::endl;
        std::cout << "FitStatus=" << result->status() <<std::endl;
        
        if (i>100){ //give up after N iterations
                std::cout << "Fit keeps failing." <<std::endl;
                exit(EXIT_FAILURE);
        }
    }

    std::cout << "Fit Converged after " << i << " loops"<<std::endl;
    this->fitStatus = result->status();

    if(sanity){
        plotting((plotDir+"SignalBGFit").c_str(), dataToFit, counterSB, 0);
        counterSB=counterSB+1;
    }

    RooMsgService::instance().setSilentMode(kFALSE);
    RooMsgService::instance().setGlobalKillBelow(INFO);

    std::cout << "Wifi: Fit Status=" << this->fitStatus << ": Nll=" << this->minNll <<std::endl;
    fitFile << "Fit Status=" << this->fitStatus << ": Nll=" << this->minNll <<std::endl;
    std::cout << "=====================================" <<std::endl;

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

    //RooAbsReal* nll = pdf->createNLL(*dataToFit, RooFit::Range(__class.m_range), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)),RooFit::Extended(kTRUE)); 
    RooAbsReal* nll_bkg = pdfBkg->createNLL(*dataToFit, RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)),RooFit::Extended(kTRUE)); 
    this->minNllBkg = nll_bkg->getVal();
    //subtract initial value from likelihood, to improve precision in case it's very large
    double nll_bkg_init_val = nll_bkg->getVal(nll_bkg->getVariables());
    RooAbsArg* arg = (RooAbsArg*)nll_bkg;
    std::string nllString= "@0-"+to_string(nll_bkg_init_val);
    RooFormulaVar nll_bkg_toFit = RooFormulaVar("nll_bkg_norm", nllString.c_str(), RooArgList(*arg, "nll_bkg_list"));

    RooMinimizer m = RooMinimizer(nll_bkg_toFit);
    m.setStrategy(this->fitStrategy);
    m.setMaxFunctionCalls(500000);
    m.setMaxIterations(100000);
    RooFitResult* result;
    int i = 0;

    m.simplex();
    //loop until convergence
    /*
        -1 = Not Available
         0 = Available but not positive definite
         1 = covariance only approximate
         2 = full matrix but forced positive definite
         3 = Full Accurate matrix
    */
    while (i==0 or result->covQual()<3){
        m.migrad();
        m.hesse();
        result = m.save();
        i=i+1;
        std::cout << result->covQual() <<std::endl;
        
        if (i>100){ //give up after N iterations
                std::cout << "Fit keeps failing." <<std::endl;
                exit(EXIT_FAILURE);
        }
    }

    std::cout << "Fit Converged after " << i << " loops" <<std::endl;
    this->fitStatus = result->status();

    if(sanity){
        plotting((plotDir+"BackgroundFit").c_str(), dataToFit, counterBG, 0);
        counterBG=counterBG+1;
    }

    RooMsgService::instance().setSilentMode(kFALSE);
    RooMsgService::instance().setGlobalKillBelow(INFO);

    std::cout << "Intranet: Fit Status=" << this->fitStatus << " : Nll=" << this->minNllBkg <<std::endl;
    fitBGFile << "Fit Status=" << this->fitStatus << " : Nll=" << this->minNllBkg <<std::endl;
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
