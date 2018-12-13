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
   clas12::calorimeter* cal=event.calorimeter_ptr();
   clas12::cherenkov* cher=event.cherenkov_ptr();
   clas12::particle* part=event.particles_ptr();

   //clas12::vector3      electron;

   int counter=0;
   while(reader.next()==true){
     event.reset();
     
      int np = part->getSize();
    
     double starttime = event.header().getStartTime();
     int pcount=0;
     while(event.next_particle()){
       //std::cout<<" particle "<<pcount++<<" "<<event.tof().getSize()<<std::endl ;
       int  pid = part->getPid();
       float time=event.getTime()-starttime;
       float ECal=event.getCalTotEnergy();
       float PCalE=cal->getEnergy(); //precal by default
       event.getPCAL();
       float PCalTime=cal->getTime();
       event.getHTCC();
       int nHTCC=cher->getNphe();
       event.getLTCC();
       int nLTCC=cher->getNphe();
       float trchi2=event.getTrackChi2();
       // if(event.isFT()) std::cout<< "    FT HIT "<<std::endl;
       //printf("pid = %8d time = %8.3f ec = %8.3f  pcal = %8.3f pcaltime=%8.3f htcc = %d ltcc=%d track = %8.3f\n", pid,time,ECal,PCalE,PCalTime,nHTCC,nLTCC,trchi2);
     }
      counter++;
     if(counter==1E6) break;
   }
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count()<< " events = "<<counter<< " s\n";

}
