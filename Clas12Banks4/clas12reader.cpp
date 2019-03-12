/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "clas12reader.h"

namespace clas12 {

  clas12reader::clas12reader(string filename){
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
  void clas12reader::readEvent(){
    _reader.read(_event);
    _event.getStructure(*_bparts.get());
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
  }
  ////////////////////////////////////////////////////////
  ///initialise next event from the reader
  bool clas12reader::next(){
    if(!_reader.next())
      return false;

    readEvent();
    sort();
    
    return true;
  }
  ////////////////////////////////////////////////////////
  ///initialise next event from the reader
  bool clas12reader::nextInRecord(){
    if(!_reader.nextInRecord())
      return false;
    
    readEvent();
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
  ////////////////////////////////////////////////////////
  ///Filter and return detParticles by given PID
  std::vector<region_part_ptr> clas12reader::getByID(int id){
    return container_filter(_detParticles, [id](region_part_ptr dr)
			    {return dr->getPid()==id;});
  }

}
