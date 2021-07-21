#include "PDF_DatasetCustom.h"
#include "RooExponential.h"
#include "RooMinimizer.h"
#include "TMath.h"
#include <chrono>
#include <RooHist.h>
#include <RooPlot.h>
#include <TROOT.h>
//#include <RooCurve.h>

PDF_DatasetCustom::PDF_DatasetCustom(RooWorkspace* w): PDF_Datasets(w){};
PDF_DatasetCustom::PDF_DatasetCustom(RooWorkspace* w, int nObs, OptParser* opt): PDF_Datasets::PDF_Datasets(w,nObs,opt){};
PDF_DatasetCustom::~PDF_DatasetCustom(){};

RooFitResult* PDF_DatasetCustom::fit(RooDataSet* dataToFit) {
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::duration<float, std::milli> duration;
    static clock::time_point start = clock::now();
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
    std::string suffix = Form("_Scanpoint%i_Toy%i_JobID%i",this->scanPoint,this->nToy,this->jobID);

    // Turn off RooMsg
    RooMsgService::instance().setGlobalKillBelow(ERROR);
    RooMsgService::instance().setSilentMode(kTRUE);

    // Choose Dataset to fit to
    // unfortunately Minuit2 does not initialize the status of the roofitresult, if all parameters are constant. Therefore need to stay with standard Minuit fitting.
    // RooFitResult* result  = pdf->fitTo( *dataToFit, RooFit::Save() , RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)), RooFit::Minimizer("Minuit2", "Migrad"));
    
    RooFitResult* result;
    int counter =0;
    int fitStrategy = 2;
    do{
        if(counter ==30) break;
        //If blinded only fit on the sidebands - if a BGonly toy proxy dataset is used, this shouldn't be used as it has data over the whole range.  
        if(fBlindFlag and not fIsToyDataset){ 
            result  = pdf->fitTo( *dataToFit,RooFit::Save()
                                            ,RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName))
                                            ,RooFit::Extended(kTRUE) 
                                            ,RooFit::Range("lsb,rsb")
                                            ,RooFit::Minos(true)
                                            ,RooFit::Strategy(fitStrategy)
        );}
        else{ 
            result  = pdf->fitTo( *dataToFit,RooFit::Save()
                                            ,RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName))
                                            ,RooFit::Extended(kTRUE) 
                                            //,RooFit::Minimizer("Minuit", "migrad") 
                                            ,RooFit::Minos(true)
                                            ,RooFit::Strategy(fitStrategy)
        );}

        std::cout<<"S"<<this->scanPoint<<" | "<<counter<<" | PDF_DatasetCustom::Fit::Status = "<<result->status()<<" | covQual= "<<result->covQual()<<std::endl;
        counter+=1;
    }while( !(result->status() == 0 && result->covQual()==3) ); 
    this->fitStatus = result->status();

    //Output FitResult to text file
    std::string outstring = this->plotDir+"FitResult"+suffix+".txt";
    std::ofstream outfile(outstring, std::ofstream::out);
    result->printMultiline(outfile, 1111, kTRUE);
    
    RooAbsReal* nll; 
    if(fBlindFlag and not fIsToyDataset){
        nll=pdf->createNLL(*dataToFit,RooFit::Extended(kTRUE),RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)),RooFit::Range("lsb,rsb"));
        //nll = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)));
    }
    else{ nll = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)));}
    this->minNll = nll->getVal();

    RooMsgService::instance().setSilentMode(kFALSE);
    RooMsgService::instance().setGlobalKillBelow(INFO);
    duration elapsed = clock::now() - start;
    std::cout << "Fit Converged in " << elapsed.count()/1000 << "s after " << counter << " iterations " <<"| Nll=" << this->minNll <<std::endl;

    if(fSanity){
        plotting((plotDir+"SignalBGFit").c_str(), suffix, dataToFit, counterSB, 0);
        counterSB+=1;
    }
    delete nll;

    return result;
};


RooFitResult* PDF_DatasetCustom::fitBkg(RooDataSet* dataToFit) {
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::duration<float, std::milli> duration;
    static clock::time_point start = clock::now();
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

    if (!pdfBkg){
        std::cout << "ERROR in PDF_Datasets::fitBkg -- No background PDF given!" << std::endl;
        exit(EXIT_FAILURE);
    }
    double parvalue = getWorkspace()->var("BFsig")->getVal();
    bool isconst = getWorkspace()->var("BFsig")->isConstant();
    getWorkspace()->var("BFsig")->setVal(0.0);
    getWorkspace()->var("BFsig")->setConstant(true);

    std::string suffix = Form("_Scanpoint%i_Toy%i_JobID%i",this->scanPoint,this->nToy,this->jobID);

    // Turn off RooMsg
    RooMsgService::instance().setGlobalKillBelow(ERROR);
    RooMsgService::instance().setSilentMode(kTRUE);

    // unfortunately Minuit2 does not initialize the status of the roofitresult, if all parameters are constant. Therefore need to stay with standard Minuit fitting.
    // RooFitResult* result  = pdfBkg->fitTo( *dataToFit, RooFit::Save() , RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)), RooFit::Minimizer("Minuit2", "Migrad"));
    
    RooFitResult* result;
    int counter =0;
    int fitStrategy = 2;
    do{
        if(counter ==30) break;

        if(fBlindFlag and not fIsToyDataset){
           std::cout << "PDF_DatasetCustom::fitBkg: Fitting with blinding" <<std::endl;
           //result = pdf->fitTo( *dataToFit, RooFit::Save() 
           result = pdfBkg->fitTo( *dataToFit, RooFit::Save() 
                                ,RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName))
                                ,RooFit::Extended(kTRUE)
                                ,RooFit::Range("lsb,rsb")
                                ,RooFit::Minos(true)
                                ,RooFit::Strategy(fitStrategy)
                                );
        }
        else{
            //result  = pdf->fitTo( *dataToFit, RooFit::Save() 
            result  = pdfBkg->fitTo( *dataToFit, RooFit::Save() 
                                ,RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName))
                                ,RooFit::Extended(kTRUE)
                                //,RooFit::Minimizer("Minuit", "minimize") //Used in Test 2
                                //,RooFit::Minimizer("Minuit", "migrad") //Used in Test 3
                                ,RooFit::Minos(true)
                                ,RooFit::Strategy(fitStrategy)
                                );
        }
        std::cout<<this->scanPoint<< " | " << counter << " | PDF_DatasetCustom::FitBkg::Status = " << result->status() << " | covQual= " << result->covQual() <<std::endl;
        counter+=1;
    }while( !(result->status() == 0 && result->covQual()==3) );
    this->fitStatus = result->status();

    //Output FitResult to text file
    //std::string outstring = this->plotDir+Form("BGFitResultFor_Scanpoint%i_Toy%i_JobID%i",this->scanPoint,this->nToy,this->jobID)+"_"+this->jobType+".txt";
    std::string outstring = this->plotDir+"BGFitResult"+suffix+".txt";
    std::ofstream outfile(outstring, std::ofstream::out);
    std::ofstream outfileBG(outstring, std::ofstream::out);
    result->printMultiline(outfileBG, 1111, kTRUE);
    
    RooAbsReal* nll_bkg; 
    if(fBlindFlag and not fIsToyDataset){ 
        //nll_bkg=pdf->createNLL(*dataToFit,RooFit::Extended(kTRUE),RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)),RooFit::Range("lsb,rsb"));
        nll_bkg=pdfBkg->createNLL(*dataToFit,RooFit::Extended(kTRUE),RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)),RooFit::Range("lsb,rsb"));
       //nll_bkg = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName)));
    }
    //else{ nll_bkg = pdf->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName))); }
    else{ nll_bkg = pdfBkg->createNLL(*dataToFit, RooFit::Extended(kTRUE), RooFit::ExternalConstraints(*this->getWorkspace()->set(constraintName))); }

    this->minNllBkg = nll_bkg->getVal();
    //std::cout << "BG: Fit Status=" << this->fitStatus << ": Nll=" << this->minNllBkg <<std::endl;

    RooMsgService::instance().setSilentMode(kFALSE);
    RooMsgService::instance().setGlobalKillBelow(INFO);
    duration elapsed = clock::now() - start;
    std::cout << "Fit Converged in " << elapsed.count()/1000 << "s after " << counter << " iterations | Nll=" << this->minNllBkg <<std::endl;

    if(fSanity){
        plotting((plotDir+"BackgroundFit").c_str(), suffix, dataToFit, counterBG, 0);
        counterBG+=1;
    }
    getWorkspace()->var("BFsig")->setVal(parvalue);
    getWorkspace()->var("BFsig")->setConstant(isconst);    
    delete nll_bkg;

    return result;
};

void   PDF_DatasetCustom::generateToys(int SeedShift) {
    std::string suffix = Form("_Scanpoint%i_Toy%i_JobID%i",this->scanPoint,this->nToy,this->jobID);

    initializeRandomGenerator(SeedShift);
    RooDataSet* toys;
    if(fIsToyDataset){ 
          //toys = this->pdf->generate(RooArgSet(*observables), *(RooDataSet*)(wspc->data(dataName)), wspc->data(dataName)->numEntries(), kFALSE, kFALSE, kFALSE);
          toys = this->pdf->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
    }
    else{ toys = this->pdf->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE); }

    if(fSanity){
        std::cout << "PDF_DatasetCustom::generateToys: Plotting..." <<std::endl;
        plotting((plotDir+"ToyDataSet").c_str(), suffix, toys, counterToy, 1);
        counterToy+=1;
    }

    // Having the delete in here causes a segmentation fault, likely due to a double free
    // related to Root's internal memory management. Therefore we do not delete,
    // which might or might not cause a memory leak.
    // if(this->toyObservables) delete this->toyObservables;
    this->toyObservables  = toys;
    this->isToyDataSet    = kTRUE;
};

void PDF_DatasetCustom::generateBkgToys(int SeedShift) {
    std::string suffix = Form("_Scanpoint%i_Toy%i_JobID%i",this->scanPoint,this->nToy,this->jobID);
    initializeRandomGenerator(SeedShift);

    if(isBkgPdfSet){
        double parvalue = getWorkspace()->var("BFsig")->getVal();
        bool isconst = getWorkspace()->var("BFsig")->isConstant();
        getWorkspace()->var("BFsig")->setVal(0.0);
        getWorkspace()->var("BFsig")->setConstant(true);

        RooDataSet* toys;
        std::cout << "Generating toys..." <<std::endl;
        RooArgSet toyObservables = *wspc->set("NeededVars");
        if(fIsToyDataset){ 
            //toys = this->pdf->generate(RooArgSet(*observables), *(RooDataSet*)(wspc->data(dataName)),wspc->data(dataName)->numEntries(),kFALSE,kFALSE,kFALSE);
            //toys = this->pdfBkg->generate(RooArgSet(*observables), *(RooDataSet*)(wspc->data(dataName)),wspc->data(dataName)->numEntries(),kFALSE,kFALSE,kFALSE);
            //toys = this->pdfBkg->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
            toys = this->pdfBkg->generate(toyObservables, wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
        }
        else{ 
            //toys = this->pdf->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
            //toys = this->pdfBkg->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
            toys = this->pdfBkg->generate(toyObservables, wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);
        }
        //if(fIsToyDataset){toys=this->pdfBkg->generate(RooArgSet(*observables),*(RooDataSet*)(wspc->data(dataName)),wspc->data(dataName)->numEntries(),kFALSE,kFALSE,kFALSE);}
        //else{ toys = this->pdfBkg->generate(RooArgSet(*observables), wspc->data(dataName)->numEntries(), kFALSE, kTRUE, "", kFALSE, kTRUE);}
    
        if(fSanity){
            std::cout << "PDF_DatasetCustom::generateBkgToys: Plotting..." <<std::endl;
            plotting((plotDir+"ToyBGDataSet").c_str(), suffix, toys, counterBGToy, 1);
            counterBGToy+=1;
        }

        getWorkspace()->var("BFsig")->setVal(parvalue);
        getWorkspace()->var("BFsig")->setConstant(isconst);    
        this->toyBkgObservables  = toys;
    }
    else{
        std::cerr << "Error in PDF_Datasets::generateBkgToys: No bkg pdf given." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "End of generateBkgToys" <<std::endl;
};

void PDF_DatasetCustom::plotting(std::string plotString, std::string plotSuffix, RooDataSet* data, int count, bool isToy){
    RooWorkspace* w = this->getWorkspace();
    gROOT->SetBatch(true);

    if(isToy){
        TCanvas* canvas = new TCanvas("cToy","cToy",600,600);
        RooPlot* frame = w->var(massVarName.c_str())->frame();
        data->plotOn(frame); //This is the toy dataset
        RooDataSet* originalData = (RooDataSet*) w->data(dataName); //This is the original dataset
        originalData->plotOn(frame, RooFit::MarkerColor(kBlue));
        std::string fitRange;
        if(fBlindFlag){ fitRange="lsb,rsb"; }
        else{ fitRange="full";}
        this->pdf->plotOn(frame,RooFit::ProjWData(*data), RooFit::Range(fitRange.c_str()), RooFit::NormRange(fitRange.c_str()), RooFit::LineColor(kRed));
        this->pdfBkg->plotOn(frame,RooFit::ProjWData(*data), RooFit::Range(fitRange.c_str()), RooFit::NormRange(fitRange.c_str()), RooFit::LineColor(kGreen)); 
        frame->Draw();
        plotString = plotString+"_"+to_string(count)+plotSuffix+".pdf";
        canvas->SaveAs((plotString).c_str());
        canvas->Close();
    }
    else{
        std::string categories[8] = {"Brem_DD_Run1","Brem_LL_Run1","NoBrem_DD_Run1","NoBrem_LL_Run1","Brem_DD_Run2","Brem_LL_Run2","NoBrem_DD_Run2","NoBrem_LL_Run2"};
        std::string fitRange;
        if(fBlindFlag){ fitRange="lsb,rsb"; }
        else{ fitRange="full";}

        for(int i=0; i<8; i++){
            std::string cat = categories[i];
            if(cat.find("Run1") != std::string::npos and plotString.find("2016only") != std::string::npos){
                continue; 
            }
            TCanvas* canvas = new TCanvas(Form("c%i_%s",i,cat.c_str()),Form("c%i_%s",i,cat.c_str()),600,600);
            TPad* pad1= new TPad(Form("p1_%i_%s",i,cat.c_str()),Form("p1_%i_%s",i,cat.c_str()),0,0.35,1,1);
            TPad* pad2= new TPad(Form("p2_%i_%s",i,cat.c_str()),Form("p2_%i_%s",i,cat.c_str()),0,0.02,1,0.33);
            pad1->SetBottomMargin(0.01);
            pad1->SetTopMargin(0.1);
            pad1->SetBorderMode(0);
            pad2->SetTopMargin(0.001);
            pad2->SetBorderMode(0);
            pad1->Draw();
            pad2->Draw();
            
            RooPlot* frame = w->var(massVarName.c_str())->frame();
            std::string cutting = "category==category::"+cat;
            data->plotOn(frame,RooFit::Cut(cutting.c_str()), RooFit::Name(Form("data_%s",cat.c_str())));
            RooCategory* slicedCategory = w->cat("category");

            pad1->cd();
            this->pdf->plotOn(frame,RooFit::Slice(*slicedCategory, cat.c_str())
                             ,RooFit::ProjWData(*data)
                             ,RooFit::Range(fitRange.c_str())
                             ,RooFit::NormRange(fitRange.c_str())
                             ,RooFit::LineColor(kRed));
            this->pdfBkg->plotOn(frame,RooFit::Slice(*slicedCategory, cat.c_str()) 
                                ,RooFit::ProjWData(*data)
                                ,RooFit::Range(fitRange.c_str())
                                ,RooFit::NormRange(fitRange.c_str())
                                ,RooFit::LineColor(kGreen));

            frame->Draw();
            pad2->cd();
            RooPlot* frame2 = w->var(massVarName.c_str())->frame();
            frame2->SetTitle("");
            frame2->SetXTitle("#it{m}(#it{#scale[1.2]{e}}#scale[0.8]{#lower[-0.8]{#pm}}#it{#mu}#scale[0.8]{#lower[-0.5]{#mp}}#it{#Lambda^{0}})");
            frame2->GetXaxis()->SetLabelSize(0.1);
            frame2->SetYTitle("Pulls");
            frame2->GetYaxis()->SetLabelSize(0.1);
            std::vector<RooHist*> pullHists;   
            auto dataHist = (RooHist*) frame->getHist(Form("data_%s",cat.c_str()));
            if(fBlindFlag){
                auto curveSBLSB = (RooCurve*) frame->getObject(1);
                auto curveSBUSB = (RooCurve*) frame->getObject(2);
                auto curveBGLSB = (RooCurve*) frame->getObject(3);
                auto curveBGUSB = (RooCurve*) frame->getObject(4);
                RooHist* SigBGtmpLSB=dataHist->makePullHist(*curveSBLSB, true);
                SigBGtmpLSB->SetMarkerColor(kRed);
                RooHist* SigBGtmpUSB=dataHist->makePullHist(*curveSBUSB,true);
                SigBGtmpUSB->SetMarkerColor(kRed);
                RooHist* BGtmpLSB=dataHist->makePullHist(*curveBGLSB,true);
                BGtmpLSB->SetMarkerColor(kGreen);
                RooHist* BGtmpUSB=dataHist->makePullHist(*curveBGUSB,true);
                BGtmpUSB->SetMarkerColor(kGreen);
                pullHists.push_back(SigBGtmpLSB);
                pullHists.push_back(SigBGtmpUSB);
                pullHists.push_back(BGtmpLSB);
                pullHists.push_back(BGtmpUSB);
            }
            else{
                auto curveSB = (RooCurve*) frame->getObject(1);
                auto curveBG = (RooCurve*) frame->getObject(2);
                RooHist* SigBGtmp=dataHist->makePullHist(*curveSB,true);
                SigBGtmp->SetMarkerColor(kRed);
                RooHist* BGtmp=dataHist->makePullHist(*curveBG,true);
                BGtmp->SetMarkerColor(kGreen);
                pullHists.push_back(SigBGtmp);
                pullHists.push_back(BGtmp);
            }

            for(int i=0; i<pullHists.size(); i++){
                frame2->addPlotable(pullHists[i],"P");
            }
            frame2->Draw();
            canvas->Update();
            
            std::string plotOutput = plotString+"_"+to_string(count)+plotSuffix+"_"+cat+"_"+this->jobType+"_SBNorm.pdf";
            canvas->SaveAs((plotOutput).c_str());
            canvas->Close();
        }

        /*//RooSimultaneous doesn't seem to handle plotting category-less. 
        TCanvas* canvas2 = new TCanvas("c9","c9",600,600);
        TPad* pad3= new TPad("p3_9_all","p3_9_all",0,0.35,1,1);
        TPad* pad4= new TPad("p4_9_all","p4_9_all",0,0.02,1,0.33);
        pad3->SetBottomMargin(0.01);
        pad3->SetTopMargin(0.1);
        pad3->SetBorderMode(0);
        pad4->SetTopMargin(0.001);
        pad4->SetBorderMode(0);
        pad3->Draw();
        pad4->Draw();

        pad3->cd();
        RooPlot* frame3 = w->var(massVarName.c_str())->frame();
        data->plotOn(frame3, RooFit::Name("data_all"));
        std::cout << this->pdf << " " << this->pdfBkg <<std::endl;
        this->pdf->plotOn(frame3,RooFit::Range(fitRange.c_str())
                          ,RooFit::NormRange(fitRange.c_str())
                          ,RooFit::LineColor(kRed));

        this->pdfBkg->plotOn(frame3,RooFit::Range(fitRange.c_str())
                             ,RooFit::NormRange(fitRange.c_str())
                             ,RooFit::LineColor(kGreen));
        frame3->Print("V");
        frame3->Draw();
        
        pad4->cd();
        RooPlot* frame4 = w->var(massVarName.c_str())->frame();
        frame4->SetTitle("");
        frame4->SetXTitle("#it{m}(#it{#scale[1.2]{e}}#scale[0.8]{#lower[-0.8]{#pm}}#it{#mu}#scale[0.8]{#lower[-0.5]{#mp}}#it{#Lambda^{0}})");
        frame4->GetXaxis()->SetLabelSize(0.1);
        frame4->SetYTitle("Pulls");
        frame4->GetYaxis()->SetLabelSize(0.1);
        std::vector<RooHist*> pullHistsAll;   
        auto dataHist = (RooHist*) frame3->getHist("data_all");
        if(fBlindFlag){
            frame3->Print("V");
            std::cout << "T2241" <<std::endl;
            auto curveSBLSBall = (RooCurve*) frame3->getObject(1);
            auto curveSBUSBall = (RooCurve*) frame3->getObject(2);
            auto curveBGLSBall = (RooCurve*) frame3->getObject(3);
            auto curveBGUSBall = (RooCurve*) frame3->getObject(4);
            std::cout << curveSBLSBall << " " << curveSBUSBall <<std::endl;
            std::cout << "T4444" <<std::endl;
            RooHist* SigBGtmpLSB=dataHist->makePullHist(*curveSBLSBall,true);
            SigBGtmpLSB->SetMarkerColor(kRed);
            RooHist* SigBGtmpUSB=dataHist->makePullHist(*curveSBUSBall,true);
            SigBGtmpUSB->SetMarkerColor(kRed);
            RooHist* BGtmpLSB=dataHist->makePullHist(*curveBGLSBall,true);
            BGtmpLSB->SetMarkerColor(kGreen);
            RooHist* BGtmpUSB=dataHist->makePullHist(*curveBGUSBall,true);
            BGtmpUSB->SetMarkerColor(kGreen);
            pullHistsAll.push_back(SigBGtmpLSB);
            pullHistsAll.push_back(SigBGtmpUSB);
            pullHistsAll.push_back(BGtmpLSB);
            pullHistsAll.push_back(BGtmpUSB);
        }
        else{
            auto curveSBall = (RooCurve*) frame3->getObject(1);
            auto curveBGall = (RooCurve*) frame3->getObject(2);
            RooHist* SigBGtmp=dataHist->makePullHist(*curveSBall,true);
            SigBGtmp->SetMarkerColor(kRed);
            RooHist* BGtmp=dataHist->makePullHist(*curveBGall,true);
            BGtmp->SetMarkerColor(kGreen);
            pullHistsAll.push_back(SigBGtmp);
            pullHistsAll.push_back(BGtmp);
        }

        for(int i=0; i<pullHistsAll.size(); i++){
            frame4->addPlotable(pullHistsAll[i],"P");
        }
        frame4->Draw();
        canvas2->Update();

        std::string plotOutput = plotString+"_"+to_string(count)+plotSuffix+"_All_"+this->jobType+"_SBNorm.pdf";
        canvas2->SaveAs((plotOutput).c_str());
        canvas2->Close();
        */
    }
    std::cout << "PDF_DatasetCustom::plotting: End"<<std::endl; 
};

/*
void PDF_DatasetCustom::setSanity(bool sanityFlag){ 
    fSanity = sanityFlag;
}
void PDF_DatasetCustom::setBlind(bool blindFlag){ 
    fBlindFlag = blindFlag;
}
void PDF_DatasetCustom::setToyDataset(bool toyFlag){ 
    fIsToyDataset = toyFlag;
}
*/
