#pragma once


#include "HipoTreeMaker.h"
#include "clas12reader.h"
#include <map>

namespace hiporoot {

  
  class ParticleTree : public HipoTreeMaker {


  public :
    ParticleTree(TString filename, TString treefilename);
    virtual ~ParticleTree();


    void Loop() final;
    void PreCompileAction() final;
    
    
    using c12_uptr = std::unique_ptr<clas12::clas12reader>;
    
    c12_uptr clas12(){
      return std::move(c12_uptr
		       (new clas12::clas12reader(HipoFileName().Data())));
    }
    
  private :
 
 
  };
}
