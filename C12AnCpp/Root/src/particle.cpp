#include "Root/particle.h"

#include "TDatabasePDG.h"
#include "TMath.h"

using namespace root;

particle::particle( const particle &p ){
  _pid = p.getPid();
  SetXYZT( p.X(),p.Y(),p.Z(),p.T());
  for( int i=0; i<p.getNdaughters();i++) addDaughter(p.getDaughter(i));

  setProtoParticle( p.getProtoParticle() );
}

particle::particle( int pid, float px, float py, float pz){
  _pid = pid;
  float m  = TDatabasePDG::Instance()->GetParticle(pid)->Mass();
  float p0 = TMath::Sqrt(px*px + py*py + pz*pz + m*m);
  SetXYZT( px,py,pz,p0);
  _ppart = 0x0;
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
  TLorentzVector vn( this->Vect() + p1.Vect(), this->T() + p1.T() );
  
  particle pn( 0, vn);
  pn.addDaughter( const_cast<particle*>(this) );
  pn.addDaughter( &p1 ); 
  return pn; 
}


particle particle::operator - ( particle& p1 )const {
  TLorentzVector vn( this->Vect() - p1.Vect(), this->T() - p1.T() );
  
  particle pn( 0, vn);
  pn.addDaughter( const_cast<particle*>(this) );
  pn.addDaughter( &p1 ); 
  return pn; 
}
