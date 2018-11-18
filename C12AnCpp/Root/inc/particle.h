/*   ___________  ___        _____        
//  / ___<  /_  |/ _ | ___  / ___/__  ___ 
// / /__ / / __// __ |/ _ \/ /__/ _ \/ _ \
// \___//_/____/_/ |_/_//_/\___/ .__/ .__/
//                           /_/  /_/    
// Yet another analysis framework for CLAS12 data, but in C++
//
// Author: fbossu (@ jlab.org)
// Date:   2018/11/16
//
// License: GPLv3 attached
*/

#pragma once

// _______ ROOT includes __________
#include "TLorentzVector.h"

// _______ Core includes __________
#include "Core/object.h"
#include "Core/protoParticle.h"

// _______ STL includes __________
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
      
      void setProtoParticle( core::protoParticle *p ) { _ppart = p; }
      core::protoParticle* getProtoParticle() const { return _ppart; }
  
      virtual particle operator + ( particle&) const;
      virtual particle operator - ( particle&) const;
    private:
      int _pid;
      std::vector<particle*> _daughters;
      core::protoParticle *_ppart; 
  };
};

