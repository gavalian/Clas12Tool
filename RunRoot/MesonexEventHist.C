#include <cstdlib>
#include <iostream>
#include <chrono>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TApplication.h>
#include <TROOT.h>
#include <TBenchmark.h>
#include "reader.h"
#include "mesonex_event.h"



void MesonexEventHist(){
  // Record start time
  auto start = std::chrono::high_resolution_clock::now();
 
   TString inputFile;
 
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
   cout<<"Analysing hipo file "<<inputFile<<endl;
   
   hipo::reader  reader;
   reader.open(inputFile.Data());

   clas12::mesonex_event  event(reader);

   TFile* outFile=TFile::Open("hists.root","recreate");
   TH1F* htdiff=new TH1F("TimeDiff","Time Difference between ToF and PCal",100,-20,20);// ==0 for FT hits, ==CTOF for CD hits
   TH2F*  hPth=new TH2F("ThetaP","#theta v p",100,0,12,100,0,180);
   
   TLorentzVector p4;
   clas12::particle *pars= event.particles_ptr();
   
   int counter=0;
   while(reader.next()==true){
     event.reset();
    
     double starttime = event.header().getStartTime();
 
     while(event.next_particle()){
       int  pid = pars->getPid();
       p4.SetXYZM(pars->getPx(),pars->getPy(),pars->getPz(),0);
       hPth->Fill(p4.P(),p4.Theta()*TMath::RadToDeg());
       
       float time=event.getTime();
       event.getPCAL();
       float PCalTime=event.calorimeter_ptr()->getTime();
       float tdiff=time-PCalTime;
       if(tdiff!=0)htdiff->Fill(tdiff);
     }
   
      counter++;
      if(counter==1E7) break;
   }
   hPth->Write();
   htdiff->Write();
   delete outFile;
   
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count() << " s\n";

}
