#include "particle.h"

#include "TDatabasePDG.h"
#include "TMath.h"

using namespace root;

particle::particle( const particle &p ){
printf(" AAAAAA 00\n");
  _pid = p.getPid();
printf(" AAAAAA 01\n");
  SetXYZT( p.X(),p.Y(),p.Z(),p.T());
printf(" AAAAAA 02\n");
  for( int i=0; i<p.getNdaughters();i++) addDaughter(p.getDaughter(i));
printf(" AAAAAA 03\n");

  setProtoParticle( p.getProtoParticle() );
printf(" AAAAAA 04\n");
}

particle* particle::getParticle( int pid, float px, float py, float pz){

  float m  = TDatabasePDG::Instance()->GetParticle(pid)->Mass();
  float p0 = TMath::Sqrt(px*px + py*py + pz*pz + m*m);
  return new particle( pid, px, py,pz,p0); 
}


void particle::addDaughter( particle *p ){
  _daughters.push_back( p );
}

int particle::getNdaughters() const { return _daughters.size(); }

particle* particle::getDaughter( int i ) const { return _daughters[i]; }

particle particle::operator + ( particle& p1 )const {
printf(" grrrr 00\n");
  TLorentzVector vn( this->Vect() + p1.Vect(), this->T() + p1.T() );
printf(" grrrr 01\n");
  
  particle pn( 0, vn);
printf(" grrrr 02\n");
  pn.addDaughter( const_cast<particle*>(this) );
printf(" grrrr 03\n");
  pn.addDaughter( &p1 ); 
printf(" grrrr 04\n");
  return pn; 
}

