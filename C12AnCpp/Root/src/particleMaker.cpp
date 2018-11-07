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


void particleMaker::processEvent(){

  core::objVector *v = (core::objVector *)getObject("protoParticles");
  if( ! v ) return;

  std::unordered_map<int, std::shared_ptr<core::objVector>> particles;  

  for( int i=0; i<v->size();i++){
    clas12::protoParticle *p = dynamic_cast<clas12::protoParticle*>( (*v)[i].get() );
    //std::cout << " p "
         //<< p->id << " "
         //<< p->pid << " "
         //<< p->charge << " "
         //<< p->px << " "
         //<< p->py << " "
         //<< p->pz << " "
         //<< p->status << " \n";

    // skip NAN value particles
    if( p->px != p->px ) continue;

    if( particles.find(p->pid) == particles.end() ){
      //printf("debug 0 ");
      //particles[p->pid] = new core::objVector();
      particles[p->pid] = std::make_shared<core::objVector>();
      //printf("debug 1 ");

      std::unique_ptr<particle> part = std::make_unique<particle>(*(particle::getParticle( p->pid, p->px, p->py, p->pz )));
      particles[p->pid]->push_back( std::move(part) );
    }
    else {
      //std::unique_ptr<particle> part = std::make_unique<particle>(particle::getParticle( p->pid, p->px, p->py, p->pz ));
      std::unique_ptr<particle> part = std::make_unique<particle>(*(particle::getParticle( p->pid, p->px, p->py, p->pz )));
      particles[p->pid]->push_back( std::move(part) );
    }
  }

  for( auto const &p : particles ){
    //std::unique_ptr<core::objVector> v = std::move( (p.second) );
    bookObject( _pname[p.first], p.second  );
    //bookObject( _pname[p.first], std::move( p.second ) );
  }
}

