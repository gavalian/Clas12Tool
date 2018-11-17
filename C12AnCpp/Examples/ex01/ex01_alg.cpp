#include "ex01_alg.h"

#include "particle.h"
#include "objVector.h"
#include "tuple.h"

void ex01_alg::init(){
}

void ex01_alg::terminate(){
}

void ex01_alg::processEvent(){

  // get the electrons from the temporary data container
  // ----------------------------------------------------
  core::objVector *electrons = (core::objVector*) getObject("electrons");
  if( ! electrons ){ 
    //cout << "no electrons!!\n"; 
    return; 
  }

  // get a ntuple (it automatically creates it for you the first time you call it)
  // the string represents the name of the output object. 
  // you will find a tree/ntuple with this name in your output file
  // -----------------------------------------------------------------------------
  core::tuple *tpl = this->ntuple("etpl");

  // get a histogram (also histograms are automatically created for you the first time
  // you call it.)
  // you need to specify the number of bins, the min and the max edges
  // You will find it in the output file
  // ------------------------------------------------------------------------------------
  core::hist *h = this->histo("he",500,0, 12);

  // loop over electrons
  for( unsigned int i=0; i < electrons->size(); i++ ){

    // careful: objVector contains unique_ptr of the particles
    // that's why we need to call the ".get()" to retrive the actual pointer
    // ----------------------------------------------------------------------
    root::particle *p1 = (root::particle*) (*electrons)[i].get();

    // book columns of your ntuple
    // --------------------------- 
    tpl->column( "P", p1->P() );
    tpl->column( "Theta", p1->Theta() );
    tpl->column( "Phi", p1->Phi() );
    tpl->column( "PID", p1->getPid() );

    // fill the ntuple
    // ---------------
    tpl->fill();
    
    // fill the histogram
    // ------------------
    h->fill( p1->P() );
  }
}

