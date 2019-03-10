#include <cstdlib>
#include <iostream>
#include <chrono>
#include <TFile.h>
#include <TTree.h>
#include <TApplication.h>
#include <TROOT.h>
#include <TDatabasePDG.h>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include "clas12reader.h"

using namespace clas12;

//just make the code a bit neater when using shared_ptr
using P4_t=TLorentzVector;
using p4_ptr = std::shared_ptr<P4_t>;

void SetLorentzVector(p4_ptr p4,clas12::region_part_ptr rp){
  p4->SetXYZM(rp->par()->getPx(),rp->par()->getPy(),
              rp->par()->getPz(),p4->M());
}

void CLAS12Reader3Pi(TString filename){

   //some particles
   auto db=TDatabasePDG::Instance();
   auto beam=P4_t(0,0,10.6,10.6);
   auto target=P4_t(0,0,0,db->GetParticle(2212)->Mass());
   //remember these are really just TLorentzVector*
   //but std::shared_ptr makes sure they are delted at end of scope
 
    p4_ptr el{new P4_t(0,0,0,db->GetParticle(11)->Mass())};
    p4_ptr pr{new P4_t(0,0,0,db->GetParticle(2212)->Mass())};
    p4_ptr g1{new P4_t(0,0,0,0)};
    p4_ptr g2{new P4_t(0,0,0,0)};
    p4_ptr pip{new P4_t(0,0,0,db->GetParticle(211)->Mass())};
    p4_ptr pim{new P4_t(0,0,0,db->GetParticle(-211)->Mass())};

    //a histogram (pre C++11 !)
    auto* hmiss=new TH1F("missM","missM",100,-2,3);
    auto* hmissCalCut=new TH1F("missM","missM",100,-2,3);
    auto* hm2g=new TH1F("m2g","Mass(2#gamma)",100,0,0.6);
    auto* hm2gCut=new TH1F("m2gCut","Mass(2#gamma) cut on Exclusivity",100,0,0.6);
    auto* hm2gCalCut=new TH1F("m2gCalCut","Mass(2#gamma) cut on FCAL",100,0,0.6);

    gBenchmark->Start("timer");
    clas12reader event(filename.Data());

    while(event.next()==true){
        // get particles by type
        auto electrons=event.getByID(11);
        auto gammas=event.getByID(22);
        auto protons=event.getByID(2212);
        auto pips=event.getByID(211);
        auto pims=event.getByID(-211);

        if(electrons.size()==1 && gammas.size()==2 && protons.size()==1 &&
             pips.size()==1 &&pims.size() == 1){
       
            // set the particle momentum
            // i.e. auto el = electrons[0]->p4(); etc.
            SetLorentzVector(el,electrons[0]);
            SetLorentzVector(pr,protons[0]);
            SetLorentzVector(g1,gammas[0]);
            SetLorentzVector(g2,gammas[1]);
            SetLorentzVector(pip,pips[0]);
            SetLorentzVector(pim,pims[0]);
            //calculate missing particle 4-vector
            TLorentzVector miss=beam+target-*el-*pr-*g1-*g2-*pip-*pim;
            hmiss->Fill(miss.M2()); //fill hist
            //calculate pi0 4-vector
            TLorentzVector pi0 = *g1+*g2;
            hm2g->Fill(pi0.M()); //fill hist
            //Apply cut on missing mass squared
            if(TMath::Abs(miss.M2())<0.5)hm2gCut->Fill(pi0.M());//fill hist
            
            //if(gammas[0]->cal(PCAL)->getEnergy()&&gammas[0]->cal(ECIN)->getEnergy()&&
             // gammas[1]->cal(PCAL)->getEnergy()&&gammas[1]->cal(ECIN)->getEnergy())
            if(gammas[0]->cal(PCAL)->getEnergy()&&
              gammas[1]->cal(PCAL)->getEnergy()){
                hmissCalCut->Fill(miss.M2()); //fill hist
                hm2gCalCut->Fill(pi0.M());//fill hist
            }
        }
        
    }
   
    gBenchmark->Stop("timer");
    gBenchmark->Print("timer");
  
    //make canvas (required in notebook)
    TCanvas* can=new TCanvas();
    can->Divide(2,1);
    can->cd(1);
    hmiss->DrawCopy();
    hmissCalCut->SetLineColor(2);
    hmissCalCut->DrawCopy("same");
    can->cd(2);
    hm2g->DrawCopy();
    hm2gCut->SetLineColor(3);
    hm2gCut->DrawCopy("same");
    hm2gCalCut->SetLineColor(2);
    hm2gCalCut->DrawCopy("same");

    can->Draw();
}