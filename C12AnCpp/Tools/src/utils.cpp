#include "Tools/utils.h"

using namespace tools;

std::tuple<double,double,double> utils::getDISvariables( root::particle *el, float Ein, float Tm ) {

  root::particle *projectile = root::particle::getParticle( 11,0,0,Ein);
  root::particle *target     = root::particle::getParticle( 2212,0,0,0);

  root::particle q = *projectile - *el;

  double Q2 = -q.M2(); 

  double xB = Q2 / (2.* target->Dot( q ) );

  double W2 = (*target + q).M2();

  delete projectile;
  delete target;
  return std::make_tuple(Q2,xB,W2);
}
