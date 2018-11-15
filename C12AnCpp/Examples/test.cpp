#include <iostream>
#include "algorithm.h"
#include "protoParticleReader.h"
#include "particleMaker.h"
#include "particle.h"
#include "hipoReader.h"
#include "manager.h"
#include "rootOutObjMgr.h"
using namespace root;

#include "TH1F.h"

using namespace std;

#include "recTrack.h"
#include "recTrackReader.h"
using namespace clas12;

#include "objMap.h"
#include "objVector.h"
#include "tuple.h"
using namespace core;

#include "kineTool.h"
#include "combineParticles.h"

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
  //core::objVector *protoparticles = (core::objVector *)getObject("protoParticles");
  //if( ! protoparticles ) return;
  //cout << " ++++ new event " << protoparticles->size() << endl;
  //for( int i=0;i<protoparticles->size();i++){
    //clas12::protoParticle *a = (clas12::protoParticle*) (*protoparticles)[i].get();
    //cout << " patricle: " 
      //<< a->id <<" "
      //<< a->pid <<" "
      //<< a->charge <<" "
      //<< a->beta << endl;
  //}

  core::objVector *e = (core::objVector*) getObject("electrons");
  if( ! e ) return;
  if( e->size() == 0 ) return;

  recTrack* tr = (recTrack*)(*tracks)[1].get();

  //cout << tr->NDF << " " << tr->getP() << endl;
  

  core::objVector *photons = (core::objVector*) getObject("photons");
  if( ! photons ){ 
    //cout << "no photons!!\n"; 
    return; 
  }


  tools::kineTool Ktool;

  core::tuple *tpl = this->ntuple("pi0");

  core::hist *h = this->histo("hpi0",500,0, 1);

  for( int i=0; i < photons->size(); i++ ){
    particle *p1 = (root::particle*) (*photons)[i].get();
    if ( p1->P() < 2.5 ) continue;
    for( int j=i+1; j < photons->size(); j++){
      particle *p2 = (root::particle*) (*photons)[j].get();
      if ( p2->P() < 1.5 ) continue;
      root::particle l = *p1 + *p2;
      //cout << l.M() << endl;
      h->fill(l.M());
      float M = l.M(); 
      float P = l.Mag();
      float theta = l.Theta();
      float phi = l.Phi();
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
  cout << " debug 00\n";
  core::tuple *tplpi0 = this->ntuple("tuplePi0");
  for( int i=0; i<pi0s->size(); i++ ){
  cout << " debug 01\n";
    particle *pi = (root::particle*) (*pi0s)[i].get();
  cout << " debug 02\n";
    tplpi0->column( "M", pi->M(), "pi0_" );
  cout << " debug 03\n";
    tplpi0->column( "Theta", pi->Theta(), "pi0_" );
  cout << " debug 04\n";
    tplpi0->column( "Phi", pi->Phi(), "pi0_" );
    
  cout << " debug 05\n";
    Ktool.execute( tplpi0, pi, "pi0_");
  cout << " debug 06\n";
    Ktool.execute( tplpi0, pi->getDaughter(0), "gamma1_");
  cout << " debug 07\n";
    Ktool.execute( tplpi0, pi->getDaughter(1), "gamma1_");
  cout << " debug 08\n";

    tplpi0->fill();
  cout << " debug 10\n";
  } 
}

#include "TFile.h"

int main( int argn, const char* argv[]) {

  TFile *of = TFile::Open("prova.root","recreate");

  core::manager *M = core::manager::instance();
  M->setOutObjMgr( new rootOutObjMgr() );
  clas12::hipoReader reader( argv[argn-1] );
  reader.open();
  M->addDataReader( &reader );

  clas12::protoParticleReader pr;
  clas12::recTrackReader tr;
  root::particleMaker pm;
  tools::combineParticles pi0m( "pi0s","photons+photons");

  test ta;

  M->addAlgorithm( &pr );
  M->addAlgorithm( &tr );
  M->addAlgorithm( &pm );
  M->addAlgorithm( &pi0m );
  M->addAlgorithm( &ta );

cout << "aaaa \n";
  M->run();

  of->Write();
  of->Close();
  return 0;

}


