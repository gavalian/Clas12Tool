/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "clas12reader.h"

namespace clas12 {

  clas12reader::clas12reader(std::string filename){
    cout<<" clas12reader::clas12reader reading "<<filename.data()<<endl;
    _reader.open(filename.data()); //keep a pointer to the reader

    hipo::dictionary  factory;
    _reader.readDictionary(factory);

    //initialise banks pointers
    _bparts = std::make_shared<particle>(factory.getSchema("REC::Particle"));
    _bmcparts = std::make_shared<mcparticle>(factory.getSchema("MC::Lund"));
    _bcovmat= std::make_shared<covmatrix>(factory.getSchema("REC::CovMat"));
    _bhead  = std::make_shared<header>(factory.getSchema("REC::Event"));
    _bcal   = std::make_shared<calorimeter>(factory.getSchema("REC::Calorimeter"));
    _bscint = std::make_shared<scintillator>(factory.getSchema("REC::Scintillator"));
    _btrck  = std::make_shared<tracker>(factory.getSchema("REC::Track"));
    _btraj  = std::make_shared<traj>(factory.getSchema("REC::Traj"));
    _bcher  = std::make_shared<cherenkov>(factory.getSchema("REC::Cherenkov"));
    _bft    = std::make_shared<forwardtagger>(factory.getSchema("REC::ForwardTagger"));
    _bvtp    = std::make_shared<clas12::vtp>(factory.getSchema("RAW::vtp"));
    _bscal = std::make_shared<clas12::scaler>(factory.getSchema("RAW::scaler"));

 
    //add some detector regions to their vectors
    addARegionFDet();
    addARegionCDet();
    addARegionFT();
  
  }
  ///////////////////////////////////////////////////////
  ///read the data
  void clas12reader::clearEvent(){
    //clear previous event
    _n_rfdets=0;
    _n_rcdets=0;
    _n_rfts=0;
    
    _detParticles.clear();
    _detParticles.reserve(_nparts);
    _pids.clear();
    _pids.reserve(_nparts);

  }
  bool clas12reader::readEvent(){
    _reader.read(_event);
    _event.getStructure(*_bparts.get());
    
    //First check if event passes criteria
    _nparts=_bparts->getSize();
    _pids.clear();
    _pids.reserve(_nparts);
      //Loop over particles and find their Pid
    for(ushort i=0;i<_nparts;i++){
      _bparts->setEntry(i);
      _pids.emplace_back(_bparts->getPid());
    }
    //check if event is of the right type
    if(!passPidSelect()) return false;

    //now getthe data for the rest of the banks
    _event.getStructure(*_bmcparts.get());
    _event.getStructure(*_bcovmat.get());
    _event.getStructure(*_bhead.get());
    _event.getStructure(*_bcal.get());
    _event.getStructure(*_bscint.get());
    _event.getStructure(*_btrck.get());
    _event.getStructure(*_btraj.get());
    _event.getStructure(*_bcher.get());
    _event.getStructure(*_bft.get());
    _event.getStructure(*_bvtp.get());
    _event.getStructure(*_bscal.get());
    return true;
  }
  ////////////////////////////////////////////////////////
  ///initialise next event from the reader
  bool clas12reader::next(){

    clearEvent();
    //keep going until we get an event that passes
    bool validEvent=false;
    while(_reader.next()){
      validEvent=true;
      if(readEvent()) //got one
	break;
    }
    if(!validEvent) return false;//no more events in reader

    //can proceed with valid event
    sort();
    
    return true;
  }
  ////////////////////////////////////////////////////////
  ///initialise next event from the reader
  bool clas12reader::nextInRecord(){
     
    clearEvent();
    //keep going until we get an event that passes
    bool validEvent=false;
    while(_reader.nextInRecord()){
      validEvent=true;
      if(readEvent()) //got one
	break;
    }
    if(!validEvent) return false;//no more events in record

    //can proceed with valid event
    sort();
 
    return true;
  }
  ////////////////////////////////////////////////////////
  /// Loop over particles and find their region
  /// Add appropriate region_partcle to event particle vector
  void clas12reader::sort(){

    
    _nparts=_bparts->getRows();
    _n_rfdets=0;
    _n_rcdets=0;
    _n_rfts=0;

    _detParticles.clear();
    _detParticles.reserve(_nparts);

    if(_nparts==0) return;
    
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
