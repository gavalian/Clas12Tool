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
#include "forwardtagger.h"
#include "region_ft.h"

using namespace clas12;


void RegionFT(){
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

   //make a link to the REC::ForwrdTagger banks
   auto  banksFT=make_shared<forwardtagger>(forwardtagger("REC::ForwardTagger",reader));

   //make a link to the REC::Particles bank
   auto  banksPart=make_shared<particle>(particle("REC::Particle",reader));

   
   //connect ft and particle banks to detector_region for parsing
   clas12::region_ft  FT(banksPart,banksFT);
   
 
   int counter=0;
   while(reader.next()==true){

     FT.configure_event();
     auto calor=FT.CAL();
     calor->setIndex(0);
     cout<<FT.getTime()<<" "<<FT.getEnergy()<<" "<<FT.getDeltaEnergy()<<endl;
     counter++;
     if(counter==1E3) break;
   }
   
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count()<< " events = "<<counter<< " s\n";

}
