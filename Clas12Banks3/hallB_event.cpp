/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "hallB_event.h"
//#include "vtp.h"

namespace clas12 {

  hallB_event::hallB_event(hipo::reader &r){
    _reader=&r; //keep a pointer to the reader
    //initialise banks pointers
    _bparts = std::make_shared<particle>();
    _bmcparts = std::make_shared<mcparticle>();
    _bcovmat= std::make_shared<covmatrix>();
    _bhead  = std::make_shared<header>();
    _bcal   = std::make_shared<calorimeter>();
    _bscint = std::make_shared<scintillator>();
    _btrck  = std::make_shared<tracker>();
    _bcher  = std::make_shared<cherenkov>();
    _bft    = std::make_shared<forwardtagger>();
    _bvtp   = std::make_shared<clas12::vtp>();

    //initialise banks
    _bparts->init("REC::Particle",r);
    _bmcparts->init("MC::Lund",r);
    _bcovmat->init("REC::CovMat",r);
    _bhead->init("REC::Event",r);
    _bvtp->init("RAW::vtp",r);
    _bcal->init("REC::Calorimeter",r);
    _bscint->init("REC::Scintillator",r);
    _bcher->init("REC::Cherenkov",r);
    _bft->init("REC::ForwardTagger",r);
    _btrck->init("REC::Track",r);

    //add some detector regions to their vectors
    addARegionFDet();
    addARegionCDet();
    addARegionFT();
  
  }
  ////////////////////////////////////////////////////////
  /// Loop over particles and find their region
  /// Add appropriate region_partcle to event particle vector
  void hallB_event::sort(){
    
    _nparts=_bparts->getSize();

    _n_rfdets=0;
    _n_rcdets=0;
    _n_rfts=0;

    _detParticles.clear();
    _detParticles.reserve(_nparts);

    //Loop over particles and find their region
    for(ushort i=0;i<_nparts;i++){ 
      _bparts->setEntry(i);
      
      //Check if FDet particle
      if(_rfdets[_n_rfdets]->sort()){
	//	add a FDet particle to the event list
	_detParticles.emplace_back(_rfdets[_n_rfdets]);
	_n_rfdets++;
	//check if need more vector entries
	//only required of previous events have
	//less particles than this
	if(_n_rfdets==_rfdets.size())
	  addARegionFDet();
	continue;
      }
      
     //Check if CDet particle
      if(_rcdets[_n_rcdets]->sort()){
	//	add a FDet particle to the event list
	_detParticles.emplace_back(_rcdets[_n_rcdets]);
	_n_rcdets++;
	//check if need more vector entries
	//only required of previous events have
	//less particles than this
	if(_n_rcdets==_rcdets.size())
	  addARegionCDet();
	continue;
      }
       //Check if FT particle
      if(_rfts[_n_rfts]->sort()){
	//add a FDet particle to the event list
	_detParticles.emplace_back(_rfts[_n_rfts]);
	_n_rfts++;
	//check if need more vector entries
	//only required of previous events have
	//less particles than this
	if(_n_rfts==_rfts.size())
	  addARegionFT();
	continue;
      }
      //cout<<"Warning hallB_event::sort() apparent particle with no detectors "<<i <<endl;
      // cout<<_bcal->scanForParticle(i).size()<<" "<<_bscint->scanForParticle(i).size()<<" "<<_btrck->scanForParticle(i).size()<<" "<<_bcher->scanForParticle(i).size()<<" "<<_bft->scanForParticle(i).size()<<" "<<endl;
      // _bparts->show();
      // _bcal->show();_bscint->show();_btrck->show();_bcher->show();_bft->show();
    }
  }
  ////////////////////////////////////////////////////////
  ///Filter and return detParticles by given PID
  std::vector<region_part_ptr> hallB_event::getByID(int id){
    return container_filter(_detParticles, [id](region_part_ptr dr)
			    {return dr->getPid()==id;});
  }

}
