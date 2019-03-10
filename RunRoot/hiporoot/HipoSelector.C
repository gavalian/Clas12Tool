#define HipoSelector_cxx
// The class definition in HipoSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//


#include "HipoSelector.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TRandom.h>
#include <TStyle.h>
#include <chrono>
#include <thread>
#include <iostream>

namespace hiporoot{
  
  HipoSelector::HipoSelector(TTree * ){

  }
  HipoSelector::HipoSelector(TString filename) : _chain(new HipoChain()) {
    _chain->Add(filename);
  }
  HipoSelector::HipoSelector(HipoChain* chain) : _chain(chain) {
  
  }

  // void HipoSelector::Run(){

  // }

  void HipoSelector::Begin(TTree * /*tree*/)
  {
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();

    
    if(!fInput){
      fInput=new TList();
      //  fInput->SetOwner(kTRUE);
    }
     
    if(!_chain){
      cout<<"Sorry no hipofiles given, exiting...."<<endl;
      exit(0);
    }
    if(!_chain->GetNFiles()){
      cout<<"Sorry no hipofiles given, exiting...."<<endl;
      exit(0);
    }
    
    fInput->Add(_chain);//make chain of files avaialbel on slaves
  }
  
  void HipoSelector::SlaveBegin(TTree * /*tree*/)
  {
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
    _chain=dynamic_cast<HipoChain*>(fInput->FindObject("HIPOFILES"));
  
    _hist1=new TH1F("Time","Time",600,-100,500);   
    fOutput->Add(_hist1);
  }

  Bool_t HipoSelector::Process(Long64_t entry)
  {
    gSystem->Sleep(gRandom->Uniform()*100+0.05);
    //check if need new file
    _iRecord=entry-_NfileRecords; //get record to analyse,subtract records of previous files
    if( _iRecord>=_NcurrRecords ){
      _iFile=_chain->GetFileFromRecord(entry);
      cout<<"Start New file "<<entry<<" "<<_iRecord<<" "<<_NcurrRecords<<" "<<_NfileRecords<<" "<<_iFile<<endl;
      _NfileRecords=_chain->GetRecordsToHere(_iFile); //Add records from previous file to give offset
       
      _c12.reset(new clas12::clas12reader(_chain->GetFileName(_iFile).Data()));
      _NcurrRecords= _c12->getReader().getNRecords(); //records in this file
      _iRecord=entry-_NfileRecords; //get first record in this file to process
      cout<<"Stop New file "<<entry<<" "<<_iRecord<<" "<<_NcurrRecords<<" "<<_NfileRecords<<" "<<_iFile<<endl;
      //  if(_iRecord==0)     gSystem->Exec(Form("vmtouch -vt %s",_chain->GetFileName(_iFile).Data()));

     }

    _c12->getReader().loadRecord(_iRecord);
    while(_c12->nextInRecord()==true){
      ProcessEvent();
    }

    //cout<<"Done record "<<_iRecord<<" "<<_iFile<<endl;
    return kTRUE;
  }
  
  Bool_t HipoSelector::ProcessEvent(){

    _hist1->Fill(_c12->head()->getStartTime());
    return kTRUE;
    
  }
  
  void HipoSelector::SlaveTerminate()
  {
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
      
  }

  void HipoSelector::Terminate()
  {
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.

   TCanvas *c1 = new TCanvas("c1", "Proof ProofFirst canvas",200,10,400,400);
   _hist1 = dynamic_cast<TH1F*>(fOutput->FindObject("Time"));
   if (_hist1) _hist1->Draw();
   c1->Update();
  }

    
}
