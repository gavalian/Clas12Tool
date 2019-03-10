
#include "HipoRootAction.h"
#include "ParticleTree.h"
#include "clas12reader.h"
#include "clas12defs.h"
#include "region_particle.h"
#include <TH1.h>
#include <TMath.h>
#include <memory>
#include <cmath>

namespace hiporoot{
  using namespace clas12;

  class clas12data {
  public:

    
    ClassDef(clas12data,1);
  };
  
  class NNNNN : public HipoRootAction{

  private :
    std::vector<clas12data> *_treedata=nullptr;
    
  public:
    
    void Action(hiporoot::HipoROOTOut *hiprout) final{
      auto ptree=dynamic_cast<ParticleTree*>(hiprout);
      
      auto tree=ptree->Tree();
      if(!tree->GetBranch("CLAS12Data")){
	_treedata=new std::vector<clas12data>;
	tree->Branch("CLAS12Data",&_treedata);
      }
      clas12::clas12reader c12(ptree->NextFile().Data());
      std::vector<region_part_ptr>* particles=c12.getDetParticlesPtr();

      clas12data particleData;
      while(c12.next()==true){
	if(ECCCC) continue;
	
	for(auto& p : *particles){
	  ////particleData.VVVVIIII = XXXX;

	  if(PCCCC)_treedata->push_back(particleData);
	}
	if(_treedata->size()) tree->Fill();
 	_treedata->clear();
     }
    }
    
  };

  
}
