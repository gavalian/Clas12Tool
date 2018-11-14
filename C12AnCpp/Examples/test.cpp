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

  tools::kineTool tool;

  core::tuple *tpl = this->ntuple("pi0");

  core::hist *h = this->histo("hpi0",500,0,0.5);

  for( int i=0; i < photons->size(); i++ ){
    particle *p1 = (root::particle*) (*photons)[i].get();
    for( int j=i+1; j < photons->size(); j++){
      particle *p2 = (root::particle*) (*photons)[j].get();
      auto l = *p1 + *p2;
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
      
      tool.execute( tpl, p1, "pi0_" );     

      tpl->fill();
    }
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
  test ta;

  M->addAlgorithm( &pr );
  M->addAlgorithm( &tr );
  M->addAlgorithm( &pm );
  M->addAlgorithm( &ta );

cout << "aaaa \n";
  M->run();

  of->Write();
  of->Close();
  return 0;

}


