#ifndef PROTOPARTICLE_H
#define PROTOPARTICLE_H

#include "object.h"

namespace clas12 {

  class protoParticle : public core::object {
    public:
      virtual ~protoParticle() {}
      int id;
      float beta;
      int charge;
      float chi2pid;
      int pid;
      float px;
      float py;
      float pz;
      int status;
      float vx;
      float vy;
      float vz;
  };
};

#endif 

