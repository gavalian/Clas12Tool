#include "Clas12/recTrack.h"
#include <cmath>

using namespace clas12;

float   recTrack::getP(){   return sqrt(px_nomm*px_nomm+py_nomm*py_nomm+pz_nomm*pz_nomm); }
float   recTrack::getPT(){  return sqrt(px_nomm*px_nomm+py_nomm*py_nomm); }
float   recTrack::getPhi(){ return atan2( py_nomm, px_nomm ); }
float   recTrack::getTheta(){ return acos( pz_nomm/getP() ); }
