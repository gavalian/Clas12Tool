//

#pragma once

#include "TLorentzVector.h"
#include "object.h"

#include "protoParticle.h"

#include <vector>

namespace root {
  class particle : public core::object,  public TLorentzVector {
    public: 
      particle( int id, float x, float y, float z, float t) : TLorentzVector(x,y,z,t) { _pid = id; }
      particle( int id, TLorentzVector v ) : TLorentzVector(v) { _pid = id; }
      particle( const particle & );
      static particle* getParticle( int, float, float, float);
      void setPid( int p ) { _pid = p; }
      int getPid() const { return _pid; } 

      void addDaughter( particle *);
      int getNdaughters() const;
      particle* getDaughter( int ) const;
      
      void setProtoParticle( clas12::protoParticle *p ) { _ppart = p; }
      clas12::protoParticle* getProtoParticle() const { return _ppart; }
      virtual particle operator + ( particle&) const;
    private:
      int _pid;
      std::vector<particle*> _daughters;
      clas12::protoParticle *_ppart; 
  };
};

