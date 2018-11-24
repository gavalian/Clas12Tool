#include <iostream>
#include <memory>
#include <tuple>
using namespace std;

#include "Core/algorithm.h"
#include "Core/objMap.h"
#include "Core/objVector.h"
#include "Core/tuple.h"
using namespace core;

#include "Root/particle.h"
#include "Core/manager.h"
#include "Root/rootOutObjMgr.h"
#include "Root/particleMaker.h"
using namespace root;



#include "Clas12/hipoReader.h"
#include "Clas12/protoParticleReader.h"
#include "Clas12/recTrack.h"
#include "Clas12/recTrackReader.h"
using namespace clas12;


#include "Tools/kineTool.h"
#include "Tools/combineParticles.h"
#include "Tools/utils.h"

class test : public core::algorithm {

  public:
    virtual void init();
    virtual void terminate();
    virtual void processEvent();
};

void test::init(){
}

void test::terminate(){
}

void test::processEvent(){

  core::objMap<int> *tracks = (core::objMap<int> *)getObject("recTracks");
  if( ! tracks ) return;

  core::objVector *e = (core::objVector*) getObject("electrons");
  if( ! e ) return;
  if( e->size() == 0 ) return;

  double Q2,xB,W2;
  std::tie(Q2,xB,W2) = tools::utils::getDISvariables( (root::particle*) (*e)[0].get(), 10.56, 0.938 );

  core::tuple *tdis = this->ntuple("dis");
  tdis->column("Q2", Q2);
  tdis->column("xB", xB);
  tdis->column("W2", W2);
  tdis->fill();

  core::objVector *photons = (core::objVector*) getObject("photons");
  if( ! photons ){ 
    return; 
  }


  tools::kineTool Ktool;

  core::tuple *tpl = this->ntuple("pi0");

  core::hist *h = this->histo("hpi0",500,0, 1);

  for( int i=0; i < photons->size(); i++ ){
    particle *p1 = (root::particle*) (*photons)[i].get();
    //if ( p1->P() < 2.5 ) continue;
    for( int j=i+1; j < photons->size(); j++){
      particle *p2 = (root::particle*) (*photons)[j].get();
      //if ( p2->P() < 1.5 ) continue;
      root::particle l = *p1 + *p2;
      //cout << l.M() << endl;
      h->fill(l.M());
      tpl->column( "M", l.M() );
      tpl->column( "P", l.P() );
      tpl->column( "Theta", l.Theta() );
      tpl->column( "Phi", l.Phi() );
      
      Ktool.execute( tpl, p1, "pi0_" );     

      tpl->fill();
    }
  }
 
  
  core::objVector *pi0s = (core::objVector*) getObject("pi0s");
  if( ! pi0s ){ 
    cout << "no pi0s!!\n"; 
    return; 
  }
  core::tuple *tplpi0 = this->ntuple("tuplePi0");
  for( int i=0; i<pi0s->size(); i++ ){
    particle *pi = (root::particle*) (*pi0s)[i].get();
    tplpi0->column( "M", pi->M(), "pi0_" );
    tplpi0->column( "Theta", pi->Theta(), "pi0_" );
    tplpi0->column( "Phi", pi->Phi(), "pi0_" );
    
    Ktool.execute( tplpi0, pi, "pi0_");
    Ktool.execute( tplpi0, pi->getDaughter(0), "gamma1_");
    Ktool.execute( tplpi0, pi->getDaughter(1), "gamma2_");

    tplpi0->fill();
  } 
}

#include "TFile.h"

int main( int argn, const char* argv[]) {


  core::manager *M = core::manager::instance();
  rootOutObjMgr p("prova.root");
  M->setOutObjMgr( &p );
  clas12::hipoReader reader( argv[argn-1] );
  reader.open();
  M->addDataReader( &reader );

  clas12::protoParticleReader pr;
  clas12::recTrackReader tr;
  root::particleMaker pm;
  tools::combineParticles pi0m( "pi0s","  photons +   photons ");

  test ta;

  M->addAlgorithm( &pr );
  M->addAlgorithm( &tr );
  M->addAlgorithm( &pm );
  M->addAlgorithm( &pi0m );
  M->addAlgorithm( &ta );

cout << "aaaa \n";
  M->run();
cout << "bbbb \n";

  p.close();
  return 0;

}


