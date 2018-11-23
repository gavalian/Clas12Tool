#include "ex02_alg.h"

#include "Root/particle.h"
#include "Core/objVector.h"
#include "Core/tuple.h"

#include "Clas12/recEvent.h"

#include "Tools/kineTool.h"

#include <iostream>
void ex02_alg::init(){
}

void ex02_alg::terminate(){
}

void ex02_alg::processEvent(){

  // get the rec event from the temporary data container
  // ----------------------------------------------------
  clas12::recEvent* ev = (clas12::recEvent*) getObject("recEvent");
  if( ! ev ){ 
    //cout << "no electrons!!\n"; 
    return; 
  }
  core::hist *htr = this->histo("htrigger", 32,0,32);
  for( int i=0;i<32;i++) if( (ev->TRG >> i) & 0x1 ) htr->fill(i);

  // get the electrons from the temporary data container
  // ----------------------------------------------------
  core::objVector *electrons = (core::objVector*) getObject("electrons");
  if( ! electrons ){ 
    //cout << "no electrons!!\n"; 
    return; 
  }

  // get the pi pi candidates, formed by the combineParticle algorithm
  // -----------------------------------------------------------------
  core::objVector *pipi = (core::objVector*) getObject("pipi");
  if( ! pipi ){ 
    return; 
  }

  if( pipi->size() == 0 ) return;

  // get a ntuple (it automatically creates it for you the first time you call it)
  // the string represents the name of the output object. 
  // you will find a tree/ntuple with this name in your output file
  // -----------------------------------------------------------------------------
  core::tuple *tpl = this->ntuple("tpl");

  // instantiate the kineTool: you can use to fill the kinematics of particles
  // -------------------------------------------------------------------------
  tools::kineTool ktool;

  // loop over electrons
  for( unsigned int i=0; i < electrons->size(); i++ ){

    // careful: objVector contains unique_ptr of the particles
    // that's why we need to call the ".get()" to retrive the actual pointer
    // ----------------------------------------------------------------------
    root::particle *p1 = (root::particle*) (*electrons)[i].get();
    
    if( p1->getPid() < 0 ) continue;

    //if( p1->P() < 1. ) continue;

    // book columns of your ntuple
    // --------------------------- 
    tpl->column( "P", p1->P(), "e_" );
    tpl->column( "Theta", p1->Theta() , "e_" );
    tpl->column( "Phi", p1->Phi(), "e_" );
 
    for( unsigned int j=0; j < pipi->size(); j++ ){
      root::particle *pp = (root::particle*) (*pipi)[j].get();
      if( pp->getDaughter(0)->getPid() == pp->getDaughter(1)->getPid() ) continue;
  
      //if( pp->getDaughter(0)->P() < .5 ) continue;

      tpl->column( "M", pp->M(), "pipi_");
      ktool.execute( tpl, pp , "pipi_");
      ktool.execute( tpl, pp->getDaughter(0)  , "pi1_");
      ktool.execute( tpl, pp->getDaughter(1)  , "pi2_");

      // fill the ntuple
      // ---------------
      tpl->fill();
    }

    
  }
}

