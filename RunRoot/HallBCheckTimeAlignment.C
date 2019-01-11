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
#include <TBenchmark.h>
#include <TCanvas.h>
#include "reader.h"
#include "hallB_event.h"

using namespace clas12;

//just make the code a bit neater when using unique_ptr
using P4_=TLorentzVector;
using p4_uptr = std::unique_ptr<P4_>;

void HallBCheckTimeAlignment(){
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

   //get the hipo data
   hipo::reader  reader;
   reader.open(inputFile.Data());

   //create the hallb event
   hallB_event event(reader);

 
   //a histogram (pre C++11 !)
   auto* hRFTimeFD=new TH1F("RFTimeFD","RFTimeFD",2000,-200,200);
   auto* hDeltaTimeFD=new TH1F("DeltaTimeFD","DeltaTimeFD",2000,-200,200);
   auto* hDeltaTimeFT=new TH1F("DeltaTimeFT","DeltaTimeFT",2000,-200,200);
   auto* hDeltaTimeCD=new TH1F("DeltaTimeCD","DeltaTimeCD",2000,-200,200);
   
   gBenchmark->Start("timer");
   int counter=0;
   
   const double fPDGMass=0.00051099891;
   while(event.next()==true){ 
     
    
     hRFTimeFD->Fill(event.head()->getStartTime()-event.head()->getRFTime());
     //Loop over all particles to see how to access detector info.
     for(auto& p : event.getDetParticles()){
       if(p->getPid()==11){//e-
	 double pP=p->par()->getP();
	 double HypBeta= pP/sqrt(pP*pP+fPDGMass*fPDGMass);
	 double HypTime=p->getPath()/100/HypBeta/2.99792e+08*1E9  ;
	 double DeltaTime=p->getTime()-HypTime - event.head()->getStartTime() ;

	 if(p->region()==1000)hDeltaTimeFT->Fill(DeltaTime);
	 else if(p->region()==2000)hDeltaTimeFD->Fill(DeltaTime);
	 else if(p->region()==3000)hDeltaTimeCD->Fill(DeltaTime);
       }
       
     }
       counter++;
     if(counter==1E6) break;
     
   }
   gBenchmark->Stop("timer");
   gBenchmark->Print("timer");
   auto c1=new TCanvas();
   c1->Divide(2,2);
   c1->cd(1);
   hRFTimeFD->DrawCopy();
   c1->cd(2);
   hDeltaTimeFT->DrawCopy();
   c1->cd(3);
   hDeltaTimeFD->DrawCopy();
   c1->cd(4);
   hDeltaTimeCD->DrawCopy();
   c1->Draw();
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count()<< " events = "<<counter<< " s\n";

}
