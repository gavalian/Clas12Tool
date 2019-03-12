/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "clas12reader.h"
#include <iostream>

namespace clas12 {
  using std::cout;
  using std::endl;
  
  clas12reader::clas12reader(std::string filename){
    cout<<" clas12reader::clas12reader reading "<<filename.data()<<endl;
    _reader.open(filename.data()); //keep a pointer to the reader

    //initialise banks pointers
    _bparts = std::make_shared<particle>();
    _bmcparts = std::make_shared<mcparticle>();
    _bcovmat= std::make_shared<covmatrix>();
    _bhead  = std::make_shared<header>();
    _bcal   = std::make_shared<calorimeter>();
    _bscint = std::make_shared<scintillator>();
    _btrck  = std::make_shared<tracker>();
    _btraj  = std::make_shared<traj>();
    _bcher  = std::make_shared<cherenkov>();
    _bft    = std::make_shared<forwardtagger>();
    _bvtp   = std::make_shared<clas12::vtp>();

    //initialise banks
    _bparts->init("REC::Particle",_reader);
    _bmcparts->init("MC::Lund",_reader);
    _bcovmat->init("REC::CovMat",_reader);
    _bhead->init("REC::Event",_reader);
    _bvtp->init("RAW::vtp",_reader);
    _bcal->init("REC::Calorimeter",_reader);
    _bscint->init("REC::Scintillator",_reader);
    _bcher->init("REC::Cherenkov",_reader);
    _bft->init("REC::ForwardTagger",_reader);
    _btrck->init("REC::Track",_reader);
    _btrck->init("REC::Traj",_reader);
 
    //add some detector regions to their vectors
    addARegionFDet();
    addARegionCDet();
    addARegionFT();
  
  }
  ////////////////////////////////////////////////////////
  ///initialise next event from the reader
  bool clas12reader::next(){
    if(!_reader.next())
      return false;

    sort();
    
    return true;
  }
  ////////////////////////////////////////////////////////
  ///initialise next event from the reader
  // bool clas12reader::nextInRecord(){
  //   if(!_reader.nextInRecord())
  //     return false;
    
  //   sort();
    
  //   return true;
  // }
  ////////////////////////////////////////////////////////
  /// Loop over particles and find their region
  /// Add appropriate region_partcle to event particle vector
  void clas12reader::sort(){

    
    _nparts=_bparts->getSize();
    _n_rfdets=0;
    _n_rcdets=0;
    _n_rfts=0;

    _detParticles.clear();
    _detParticles.reserve(_nparts);

    _pids.clear();
    _pids.reserve(_nparts);
    
    if(_nparts==0) return;
    
    //Loop over particles and find their Pid
    for(ushort i=0;i<_nparts;i++){
      _bparts->setEntry(i);
      _pids.emplace_back(_bparts->getPid());
    }
    //check if event is of the write type
    if(!passPidSelect()) return;
    
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
    }
  }
  bool clas12reader::passPidSelect(){
    //if no selections take event
    if(_pidSelect.empty()&&_pidSelectExact.empty()) return true;

    //check is there is at least enough particles
    if(_pidSelectExact.size()+_pidSelect.size()>_nparts)
      return false;

    //check if any unwanted particles
    if(_zeroOfRestPid){
      auto uniquePids=_pids;//make a copy
      std::sort(uniquePids.begin(), uniquePids.end());
      auto ip = std::unique(uniquePids.begin(), uniquePids.begin() + _nparts); 
      uniquePids.resize(std::distance(uniquePids.begin(), ip));
      //now just loop over the unique particle types
      for(auto const& pid : uniquePids){
	//check if we have a PID not given in a selection
	if(!(std::count(_givenPids.begin(),_givenPids.end(), pid)))
	  return false;
      }
    }
      //check for requested exact matches
    for(auto const& select : _pidSelectExact){
       if(!(select.second==getNPid(select.first)))
	return false;
    }
    
    //check for requeseted at least  matches
    for(auto const& select : _pidSelect){
      if((select.second>getNPid(select.first)))
	return false;
    }
    return true;
  }
  
  ////////////////////////////////////////////////////////
  ///Filter and return detParticles by given PID
  std::vector<region_part_ptr> clas12reader::getByID(int id){
    return container_filter(_detParticles, [id](region_part_ptr dr)
			    {return dr->getPid()==id;});
  }

}
