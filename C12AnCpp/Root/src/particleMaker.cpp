#include "particleMaker.h"

// core includes 
#include "objVector.h"
#include "object.h"

// clas12 includes
#include "protoParticle.h"
//using clas12::protoParticle;

// root includes
#include "particle.h"

// ROOT include
#include "TDatabasePDG.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <cmath>
using std::vector;


using namespace root;
void particleMaker::init(){
  // adding the missing deuteron to the pdg table
  TDatabasePDG::Instance()->AddParticle("deuteron","deuteron",1.875613,true,0,+1,"nuclei",45);

  _pname[11]   = "electrons";
  _pname[221]  = "pions";
  _pname[2212] = "protons";
  _pname[2112] = "neutrons";
  _pname[22]   = "photons";
  _pname[45]   = "deuterons";
  _pname[321]  = "kaons"; 
  _pname[0]    = "unidentified"; 
}

//
// transform protoParitcles in particles, sorting them by species
void particleMaker::processEvent(){

  // get protoparticles from temporary container
  core::objVector *vpp = (core::objVector *)getObject("protoParticles");
  if( ! vpp ) return;

  // map of particle vectors
  std::unordered_map<int, std::shared_ptr<core::objVector>> particles;  

  // loop over protoparticles
  for( unsigned int i=0; i<vpp->size();i++){
    clas12::protoParticle *p = dynamic_cast<clas12::protoParticle*>( (*vpp)[i].get() );

    // skip NAN value particles
    if( p->px != p->px ) continue;

    // create paticles and sort them by type
    if( particles.find(abs(p->pid)) == particles.end() ){
      particles[abs(p->pid)] = std::make_shared<core::objVector>();
      std::unique_ptr<particle> part = std::make_unique<particle>(*(particle::getParticle( p->pid, p->px, p->py, p->pz )));
      part->setProtoParticle( p );
      particles[abs(p->pid)]->push_back( std::move(part) );
    }
    else {
      std::unique_ptr<particle> part = std::make_unique<particle>(*(particle::getParticle( p->pid, p->px, p->py, p->pz )));
      part->setProtoParticle( p );
      particles[abs(p->pid)]->push_back( std::move(part) );
    }
  }

  for( auto const &p : particles ){
    bookObject( _pname[p.first], p.second  );
  }
}

