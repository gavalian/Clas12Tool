/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "bankreader.h"

namespace clas12 {

  //  bankreader::bankreader(hipo::reader &r){
  bankreader::bankreader(string filename){
    _reader.open(filename.data()); //keep a pointer to the reader

    hipo::dictionary  factory;
    _reader.readDictionary(factory);

    //initialise banks pointers
    // _bparts = std::make_shared<hipo::bank>(factory.getSchema("REC::Particle"));
    // _bmcparts = std::make_shared<hipo::bank>(factory.getSchema("MC::Lund"));
    // _bcovmat= std::make_shared<hipo::bank>(factory.getSchema("REC::CovMat"));
    // _bhead  = std::make_shared<hipo::bank>(factory.getSchema("REC::Event"));
    // _bcal   = std::make_shared<hipo::bank>(factory.getSchema("REC::Calorimeter"));
    // _bscint = std::make_shared<hipo::bank>(factory.getSchema("REC::Scintillator"));
    // _btrck  = std::make_shared<hipo::bank>(factory.getSchema("REC::Track"));
    // _btraj  = std::make_shared<hipo::bank>(factory.getSchema("REC::Traj"));
    // _bcher  = std::make_shared<hipo::bank>(factory.getSchema("REC::Cherenkov"));
    // _bft    = std::make_shared<hipo::bank>(factory.getSchema("REC::ForwardTagger"));

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

 
    // //add some detector regions to their vectors
    // addARegionFDet();
    // addARegionCDet();
    // addARegionFT();
  
  }
  ////////////////////////////////////////////////////////
  ///initialise next event from the reader
  bool bankreader::next(){
    if(!_reader.next())
      return false;
    
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
    return true;
   }
}
