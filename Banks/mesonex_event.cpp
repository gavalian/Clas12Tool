/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "clas12defs.h"
#include "mesonex_event.h"


namespace clas12 {

  void mesonex_event::init(hipo::reader &r){
    _particles.init("REC::Particle",r);
    _header.init("REC::Event",r);
    _calorimeter.init("REC::Calorimeter",r);
    _tof.init("REC::Scintillator",r);
    _cherenkov.init("REC::Cherenkov",r);
    _ft.init("REC::ForwardTagger",r);
    _track.init("REC::Track",r);
   }

  vecPIDs mesonex_event::pids(){
    vecPIDs temp(_particles.getSize());

    for(int ip=0; ip<_particles.getSize(); ip++)
      temp[ip]=_particles.getPid(ip);

    return temp;
  }

  bool mesonex_event::next_particle(){
    auto nparts=_particles.getSize();

    //check if another particle
    if( _pentry == nparts)
      return false;
   
    _particles.setEntry(_pentry);
   
    checkTof(); //find prefered ToF hit

    checkFT();  //sort FT hodo&cal hit

    checkTrack(); //find particle track
    
    checkCalorimeter(); //set PCAL

    // _cherenkov.print();
    _pentry++;
    return true;
  }
  
  ///////////////////////////////////////////////////////////////
  //Find hodo and cal hits to get time, and delta E etc.
  void mesonex_event::checkFT(){
    _pftcal=_ft.getIndex(_pentry,clas12::FTCAL);   
    _pfthodo=_ft.getIndex(_pentry,clas12::FTHODO);
  }
  ///////////////////////////////////////////////////////////////
  //if FTOF save tof index with preference layer1, layer2, layer0
  //if CTOF save preference CTOF then CND
  void mesonex_event::checkTof(){
    _ptof=-1;//particle tof index
    _isFTOF=false;
    _isCTOF=false;
    _isCND=false;
    if((_ptof=_tof.getIndex(_pentry,clas12::FTOF,1))>-1){
      _isFTOF=true;
      return;
    }
    if((_ptof=_tof.getIndex(_pentry,clas12::FTOF,0))>-1){
       _isFTOF=true;    
      return;
    }
    if((_ptof=_tof.getIndex(_pentry,clas12::FTOF,2))>-1){
      _isFTOF=true;
      return;
    }
    if((_ptof=_tof.getIndex(_pentry,clas12::CTOF,0))>-1){
      _isCTOF=true;
      return;
    }
    if((_ptof=_tof.getIndex(_pentry,clas12::CND,0))>-1){
      _isCND=true;
      return;
    }
  }

  ////////////////////////////////////////////////////////////////
  //Look for track for this particle
  void mesonex_event::checkTrack(){
    //return _tracker
    auto trackids=_track.scanForParticle(_pentry);
    if(trackids.size()){
      //should only be 1 track per particle so just take first index
      _track.setIndex(trackids[0]);
     }
    else _track.setIndex(-1);
  }
  
  //////////////////////////////////////////////////////////////////
  ///Use PCAL for time, path, sector,...
  void mesonex_event::checkCalorimeter(){
    getPCAL();
 }
}//namespace clas12
 
