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

//just make the code a bit neater when using unique_ptr
using P4_t=TLorentzVector;
//using p4_ptr = std::unique_ptr<P4_t>;
using p4_ptr = std::shared_ptr<P4_t>;

void SetLorentzVector(p4_ptr p4,clas12::region_part_ptr rp){
  p4->SetXYZM(rp->par()->getPx(),rp->par()->getPy(),
	      rp->par()->getPz(),p4->M());

}

void Ex1_CLAS12Reader(){
  // Record start time
  auto start = std::chrono::high_resolution_clock::now();


  /////////////////////////////////////
  //ignore this just getting file name!
   TString inputFile;
   TString outputFile;

   for(Int_t i=1;i<gApplication->Argc();i++){
    TString opt=gApplication->Argv(i);
    if((opt.Contains(".hipo"))){
      inputFile=opt(5,opt.Sizeof());
    }
   }
   if(inputFile==TString())  {
      std::cout << " *** please provide a file name..." << std::endl;
     exit(0);
   }
   /////////////////////////////////////

   
   cout<<"Analysing hipo file "<<inputFile<<endl;

   TChain fake("hipo");
   fake.Add(inputFile.Data());
   //get the hipo data
   //   reader.open(inputFile.Data());
   auto files=fake.GetListOfFiles();

   //some particles
   auto db=TDatabasePDG::Instance();
   auto beam=P4_t(0,0,10.6,10.6);
   auto target=P4_t(0,0,0,db->GetParticle(2212)->Mass());
   //remember these are really just TLorentzVector*
   //but std::unique_ptr makes sure they are delted at end of scope
   auto el=p4_ptr(new P4_t(0,0,0,db->GetParticle(11)->Mass()));
   auto pr=p4_ptr(new P4_t(0,0,0,db->GetParticle(2212)->Mass()));
   auto g1=p4_ptr(new P4_t(0,0,0,0));
   auto g2=p4_ptr(new P4_t(0,0,0,0));
   auto pip=p4_ptr(new P4_t(0,0,0,db->GetParticle(211)->Mass()));
   auto pim=p4_ptr(new P4_t(0,0,0,db->GetParticle(-211)->Mass()));

   //a histogram (pre C++11 !)
   auto* hmiss=new TH1F("missM","missM",200,-2,3);
   auto* hm2g=new TH1F("m2g","m2g",200,0,1);
   auto* hm2gCut=new TH1F("m2gCut","m2g",200,0,1);
   
   gBenchmark->Start("timer");
   int counter=0;
 
   
   for(Int_t i=0;i<files->GetEntries();i++){
     //create the hallb event
      clas12reader event(files->At(i)->GetTitle());


     while(event.next()==true){
       event.head()->getStartTime();
        //Loop over all particles to see how to access detector info.
	for(auto& p : event.getDetParticles()){
  	 //  get predefined selected information
	 p->getTime();
	 p->getDetEnergy();
	 p->getDeltaEnergy();

	 // get any detector information (if exists for this particle)
	 // there should be a get function for any entry in the bank
	 switch(p->getRegion()) {
	 case FD :
	   p->cal(PCAL)->getEnergy();
	   p->cal(ECIN)->getEnergy();
	   p->cal(ECOUT)->getEnergy();
	   p->sci(FTOF1A)->getEnergy();
	   p->sci(FTOF1B)->getEnergy();
	   p->sci(FTOF2)->getEnergy();
	   p->trk(DC)->getSector();
	   p->che(HTCC)->getNphe();
	   p->che(LTCC)->getNphe();
	   p->traj(TRAJ_HTCC)->getX();
	   break;
	 case FT :
	   p->ft(FTCAL)->getEnergy();
	   p->ft(FTHODO)->getEnergy();
	   break;
	 case CD:
	   p->sci(CTOF)->getEnergy();
	   p->sci(CND)->getEnergy();
	   break;
	 }
	 //   covariance matrix (comment in to see!)
	 // p->covmat()->print();
	 p->cmat();
       }
    
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
	
	 TLorentzVector miss=beam+target-*el-*pr-*g1-*g2-*pip-*pim;
	 hmiss->Fill(miss.M2());
	 TLorentzVector pi0 = *g1+*g2;
	 hm2g->Fill(pi0.M());
	 if(TMath::Abs(miss.M2())<0.5)hm2gCut->Fill(pi0.M());
       }
     
       counter++;
     }
   }
   gBenchmark->Stop("timer");
   gBenchmark->Print("timer");
   TCanvas* can=new TCanvas();
   can->Divide(2,1);
   can->cd(1);
   hmiss->DrawCopy();
   can->cd(2);
   hm2g->DrawCopy();
   hm2gCut->SetLineColor(2);
   hm2gCut->DrawCopy("same");
  
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count()<< " events = "<<counter<< " s\n";

}
