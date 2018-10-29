#include "particle.h"

#include "TDatabasePDG.h"
#include "TMath.h"

using namespace root;

//ClassImp(particle)

particle::particle( particle &p ){
  _pid = p.getPid();
  SetXYZT( p.X(),p.Y(),p.Z(),p.T());
}

particle* particle::getParticle( int pid, float px, float py, float pz){

  float m  = TDatabasePDG::Instance()->GetParticle(pid)->Mass();
  float p0 = TMath::Sqrt(px*px + py*py + pz*pz + m*m);
  return new particle( pid, px, py,pz,p0); 
}

