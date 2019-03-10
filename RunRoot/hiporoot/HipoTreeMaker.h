#pragma once


#include "HipoROOTOut.h"
#include <TTree.h>
#include <TFile.h>

namespace hiporoot {

  
  class HipoTreeMaker : public HipoROOTOut {


  public :
    HipoTreeMaker(TString filename, TString treefilename);
    virtual ~HipoTreeMaker();


 
    virtual HipoTreeMaker* Branch(TString varExp,TString condExp="1");


    TTree* Tree() const {return _tree;}

    void Fill();
    void AddParticleCut(TString cut);
    void AddEventCut(TString cut);
    
  protected :
    
    vector<TString> _branchNames;
    vector<TString> _branchTypes;
    TString _evcut={"0"};
    TString _pcut={"1"};

  private :

    TFile* _treefile=nullptr;
    TTree* _tree=nullptr;
  };
}
