#ifndef PARTICLE_H
#define PARTICLE_H

#include "TLorentzVector.h"
#include "object.h"

namespace root {
  class particle : public core::object,  public TLorentzVector {
    public: 
      particle( int id, float x, float y, float z, float t) : TLorentzVector(x,y,z,t) { _pid = id; }
      particle( particle &);
      static particle* getParticle( int, float, float, float);
      virtual void setPid( int p ) { _pid = p; }
      virtual int getPid() { return _pid; } 

      /*virtual */
    private:
      int _pid;
      /*ClassDef(particle,1)*/
  };
};

#endif 

