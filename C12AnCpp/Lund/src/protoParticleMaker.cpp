#include "protoParticleMaker.h"
#include "protoParticle.h"
#include "lundReader.h"
using namespace lund;

#include "objVector.h"

#include <memory>
using namespace std;

void protoParticleMaker::processEvent() {

  lundEv *ev = static_cast<lundReader*>(getDataReader())->getLundEv();
  if( ! ev ) return;

  shared_ptr<core::objVector> particles = make_shared<core::objVector>();
  
  for( auto pl : ev->parts ){
    unique_ptr<protoParticle> p = make_unique<protoParticle>();
    p->id = pl[0];
    p->lifetime = pl[1];
    p->type = pl[2];
    p->pid = pl[3];
    p->motherID = pl[4];
    p->daughterID = pl[5];
    p->px = pl[6];
    p->py = pl[7];
    p->pz = pl[8];
    p->E = pl[9];
    p->M = pl[10];
    p->vx = pl[11];
    p->vy = pl[12];
    p->vz = pl[13];

    particles->push_back( move(p) );
  }

  bookObject( "protoParticles", particles);
}

