#include <cstdlib>
#include <iostream>
#include <chrono>
#include <TFile.h>
#include <TTree.h>
#include <TApplication.h>
#include <TROOT.h>
#include <TBenchmark.h>
#include "reader.h"
#include "particle.h"
#include "calorimeter.h"
#include "scintillator.h"
#include "tracker.h"
#include "cherenkov.h"
#include "region_fdet.h"

using namespace clas12;


void RegionFDET(){
  // Record start time
  auto start = std::chrono::high_resolution_clock::now();
 
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
   cout<<"Analysing hipo file "<<inputFile<<endl;

   //get the hipo data
   hipo::reader  reader;
   reader.open(inputFile.Data());

   //make a link to the REC::Particles bank
   //  auto  banksPART=make_shared<particle>("REC::Particle",reader);
   auto  banksPART=make_shared<particle>();banksPART->init("REC::Particle",reader);
    
  //make a link to the REC::Calorimeter banks
   //   auto  banksCAL=make_shared<calorimeter>("REC::Calorimeter",reader);
   auto  banksCAL=make_shared<calorimeter>();banksCAL->init("REC::Calorimeter",reader);
  //make a link to the REC::Scintillator banks
   auto  banksSCINT=make_shared<scintillator>();banksSCINT->init("REC::Scintillator",reader);
  //make a link to the REC::Tracker banks
   auto  banksTRCK=make_shared<tracker>();banksTRCK->init("REC::Track",reader);
  //make a link to the REC::Cherenkov banks
   auto  banksCHER=make_shared<cherenkov>();banksCHER->init("REC::Cherenkov",reader);

 
   
   //connect ft and particle banks to detector_region for parsing
   clas12::region_fdet  FDet(banksPART,banksCAL,banksSCINT,banksTRCK,banksCHER);
   
 
   int counter=0;
   while(reader.next()==true){
    auto Np=banksPART->getSize();
     
     for(int i=0;i<Np;i++){
       //cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii "<<i<<endl;
       banksPART->setEntry(i);
       FDet.coordinate();
       //  cout<<FDet.getTime()<<" "<<FDet.getCalEnergy()<<" "<<FDet.getDeltaEnergy()<<endl;
     }
     //   auto calor=FT.CAL();
     // calor->setIndex(0);
     // cout<<FT.getTime()<<" "<<FT.getEnergy()<<" "<<FT.getDeltaEnergy()<<endl;
     //counter++;
     // if(counter==1E3) break;
     
   }
   
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count()<< " events = "<<counter<< " s\n";

}
