#include <iostream>
#include "algorithm.h"
#include "protoParticleReader.h"
#include "particleMaker.h"
#include "particle.h"
#include "hipoReader.h"
#include "manager.h"
#include <vector>
//#include <unordered_map>
#include <map>
using namespace root;

#include "TH1F.h"

using namespace std;

#include "recTrack.h"
#include "recTrackReader.h"
using namespace clas12;

#include "objMap.h"
#include "objVector.h"
using namespace core;

#include "histogram.h"

class test : public core::algorithm {

  public:
    virtual void init();
    virtual void terminate();
    virtual void processEvent();

  private:
    hist *H;
    TH1F *h;
};

void test::init(){
  H = new hist(1000,0,1.);
  h = new TH1F("pi0","pi0",1000,0,1.);
}

#include <fstream>
void test::terminate(){
  //H->show();
  std::ofstream of("of.txt",std::ios::out);
  H->write(of);
  of.close();

  h->SaveAs("h.root");
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

  cout << tr->NDF << " " << tr->getP() << endl;
  

  core::objVector *photons = (core::objVector*) getObject("photons");
  if( ! photons ){ 
    //cout << "no photons!!\n"; 
    return; 
  }

  for( int i=0; i < photons->size(); i++ ){
    particle *p1 = (root::particle*) (*photons)[i].get();
    for( int j=i+1; j < photons->size(); j++){
      particle *p2 = (root::particle*) (*photons)[j].get();
      auto l = *p1 + *p2;
      //cout << l.M() << endl;
      H->fill(l.M());
      h->Fill(l.M());
    }
  }
  
}

int main( int argn, const char* argv[]) {

  core::manager *M = core::manager::instance();

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

  return 0;

}


