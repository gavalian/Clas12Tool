#include <iostream>

#include "Core/manager.h"
#include "Core/tuple.h"

#include "Root/rootOutObjMgr.h"
#include "Root/particleMaker.h"

#include "Lund/lundReader.h"
#include "Lund/protoParticleMaker.h"

#include "ex_lund_alg.h"

int main( int argn, const char* argv[]) {

  // instatiate the manager
  // ----------------------
  core::manager *M = core::manager::instance();

  // output manager. Here we have chosen to work with ROOT objects
  // the output histograms and ntuples will be saved it "test.root"
  // --------------------------------------------------------------
  root::rootOutObjMgr oom("test.root");
  M->setOutObjMgr( &oom );

  // We want to analyse LUND files
  // So we create a lundReader
  // --------------------------------------------------------------
  lund::lundReader reader( argv[argn-1] );
  M->addDataReader( &reader );

  // =========== ALGORITHMS =========================
  // Here we specify the set of algorithms needed for our analysis
  // -------------------------------------------------------------

  // algorithm that reads the particles in the lund format
  lund::protoParticleMaker pr;
  M->addAlgorithm( &pr );

  // algorithm that creates particles species containers
  root::particleMaker pm;
  M->addAlgorithm( &pm );

  // -----------------------------
  // USER SPECIFIC ALGORITHM
  // -----------------------------
  ex_lund_alg ta;
  M->addAlgorithm( &ta );


  // Run the analysis
  // ----------------
  M->run();

  // the program authmatically save and close the output file
  return 0;

}


