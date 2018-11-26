#include <cstdlib>
#include <iostream>
#include <chrono>
#include <TFile.h>
#include <TTree.h>
#include <TApplication.h>
#include <TROOT.h>
#include <TBenchmark.h>
#include "reader.h"
#include "mesonex_event.h"



void MesonexEvent(){
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
   
   hipo::reader  reader;
   reader.open(inputFile.Data());

   clas12::mesonex_event  event(reader);

   //clas12::vector3      electron;

   int counter=0;
   while(reader.next()==true){
     event.reset();
     int np = event.particles().getSize();
    
     double starttime = event.header().getStartTime();
     int pcount=0;
     while(event.next_particle()){
       int  pid = event.particles().getPid();
       float time=event.getTime()-starttime;
       float ECal=event.getCalTotEnergy();
       float PCalE=event.calorimeter().getEnergy(); //precal by default
       event.getPCAL();
       float PCalTime=event.calorimeter().getTime();
       event.getHTCC();
       int nHTCC=event.cherenkov().getNphe();
       event.getLTCC();
       int nLTCC=event.cherenkov().getNphe();
       float trchi2=event.getTrackChi2();
      }
   
      counter++;
      if(counter==1E7) break;
   }
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count() << " s\n";

}
