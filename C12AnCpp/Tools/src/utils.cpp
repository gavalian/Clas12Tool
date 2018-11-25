#include "Tools/utils.h"

using namespace tools;

std::tuple<double,double,double> utils::getDISvariables( root::particle *el, float Ein, int Tpid ) {

  root::particle projectile( 11,0,0,Ein);
  root::particle target( Tpid,0,0,0);

  root::particle q = projectile - *el;

  double Q2 = -q.M2(); 

  double xB = Q2 / (2.* target.Dot( q ) );

  double W2 = (target + q).M2();

  return std::make_tuple(Q2,xB,W2);
}
