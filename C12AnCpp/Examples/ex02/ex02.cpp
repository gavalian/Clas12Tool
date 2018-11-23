#include <iostream>

#include "Core/manager.h"

#include "Root/rootOutObjMgr.h"
#include "Root/particleMaker.h"

#include "Clas12/protoParticleReader.h"
#include "Clas12/recEventReader.h"
#include "Clas12/hipoReader.h"

#include "Tools/combineParticles.h"

#include "ex02_alg.h"

int main( int argn, const char* argv[]) {
  if( argn < 2 ) return 0;

  // instatiate the manager
  // ----------------------
  core::manager *M = core::manager::instance();

  // output manager. Here we have chosen to work with ROOT objects
  // the output histograms and ntuples will be saved it "test.root"
  // --------------------------------------------------------------
  root::rootOutObjMgr oom("test.root");
  M->setOutObjMgr( &oom );

  // We want to analyse DST in hipo format
  // So we create an hipoReader.
  // We can pass either:
  //   - a .hipo file 
  //   - a .txt file that conatins a list hipo file paths
  // --------------------------------------------------------------
  clas12::hipoReader reader( argv[argn-1] );
  reader.open();
  M->addDataReader( &reader );

  // =========== ALGORITHMS =========================
  // Here we specify the set of algorithms needed for our analysis
  // -------------------------------------------------------------

  // algorithm that reads the event bank
  clas12::recEventReader er;
  M->addAlgorithm( &er );

  // algorithm that reads the particle bank
  clas12::protoParticleReader pr;
  M->addAlgorithm( &pr );

  // algorithm that creates particles species containers
  root::particleMaker pm;
  M->addAlgorithm( &pm );

  // combine particle: makes the pi pi candidates
  tools::combineParticles cp( "pipi", "pions + pions");
  M->addAlgorithm( &cp );

  // -----------------------------
  // USER SPECIFIC ALGORITHM
  // -----------------------------
  ex02_alg ta;
  M->addAlgorithm( &ta );


  // Run the analysis
  // ----------------
  M->run();

  // the program authmatically save and close the output file
  return 0;

}


