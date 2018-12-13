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
#include "reader.h"
#include "hallB_event.h"

using namespace clas12;

//just make the code a bit neater when using unique_ptr
using P4_=TLorentzVector;
using p4_uptr = std::unique_ptr<P4_>;

void HallBEvent(){
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

   //some particles
   auto db=TDatabasePDG::Instance();
   auto beam=P4_(0,0,10.6,10.6);
   auto target=P4_(0,0,0,db->GetParticle(2212)->Mass());
   //remember these are really just TLorentzVector* 
   auto el=p4_uptr(new P4_(0,0,0,db->GetParticle(11)->Mass()));
   auto pr=p4_uptr(new P4_(0,0,0,db->GetParticle(2212)->Mass()));
   auto g1=p4_uptr(new P4_(0,0,0,0));
   auto g2=p4_uptr(new P4_(0,0,0,0));
   auto pip=p4_uptr(new P4_(0,0,0,db->GetParticle(211)->Mass()));
   auto pim=p4_uptr(new P4_(0,0,0,db->GetParticle(-211)->Mass()));

   //a histogram (pre C++11 !)
   auto* hmiss=new TH1F("missM","missM",200,-2,3);
   
   gBenchmark->Start("timer");
   int counter=0;
   
   //  while(reader.next()==true){// (map 4.5s for 1M events)
                             
   while(event.next()==true){ //(5.6s) vector + all loop (7.6s)
                              //  7M =75.05 seconds Cpu Time =  48.65s
                              //(7.2s) map  + all loop (9.4s)
                              //(6.9s) uomap+ all loop (8.7s)
                              //7M =  85.74 seconds Cpu Time =  59.70s
                              //i.e. using maps is 2.5x slower!


     
     event.head()->getStartTime();
     
     //Loop over all particles to see how to access detector info.
     for(auto& p : event.getDetParticles()){
       //  get predefined selected information
       p->getTime();
       p->getDetEnergy();
       p->getDeltaEnergy();
       // get any detector information (if exists for this particle)
       // there should be a get function for any entry in the bank
       switch(p->region()) {// (+1s per 1M)
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
     // get particles by type (+1s overhead per 1M (include fill hist))
     auto electrons=event.getByID(11);
     auto gammas=event.getByID(22);
     auto protons=event.getByID(2212);
     auto pips=event.getByID(211);
     auto pims=event.getByID(-211);

     if(electrons.size()==1 && gammas.size()==2 && protons.size()==1 &&
     	pips.size()==1 &&pims.size() == 1){
       
       // set the particle momentum
       // if we wanted to integrate more ROOT we could
       // return direct TLorentzVector
       // i.e. auto el = electrons[0]->p4(); etc.
       el->SetXYZM(electrons[0]->par()->getPx(),electrons[0]->par()->getPy(),
     		   electrons[0]->par()->getPz(),el->M());
       pr->SetXYZM(protons[0]->par()->getPx(),protons[0]->par()->getPy(),
     		   protons[0]->par()->getPz(),pr->M());
       g1->SetXYZM(gammas[0]->par()->getPx(),gammas[0]->par()->getPy(),
     		   gammas[0]->par()->getPz(),0);
       g2->SetXYZM(gammas[1]->par()->getPx(),gammas[1]->par()->getPy(),
     		   gammas[1]->par()->getPz(),0);
       pip->SetXYZM(pips[0]->par()->getPx(),pips[0]->par()->getPy(),
     		    pips[0]->par()->getPz(),pip->M());
       pim->SetXYZM(pims[0]->par()->getPx(),pims[0]->par()->getPy(),
     		    pims[0]->par()->getPz(),pim->M());

       TLorentzVector miss=beam+target-*el-*pr-*g1-*g2-*pip-*pim;
       hmiss->Fill(miss.M2());
       
     }
     
     counter++;
     // if(counter==1E6) break;
     
   }
   gBenchmark->Stop("timer");
   gBenchmark->Print("timer");
   hmiss->DrawCopy();
   
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count()<< " events = "<<counter<< " s\n";

}
