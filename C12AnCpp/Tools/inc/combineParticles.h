//   ___________  ___        _____        
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
//

#pragma once

//________ Core includes __________
#include "algorithm.h"

// _______ Root includes __________
#include "particle.h"

// _______ STL includes __________
#include <string>

//////////////////////////////////////////////////////////////////////
//
// Algorithm to create all candidates from two input particles
// It stores the candidates as root::particle in the Temp. Data Cont.
//////////////////////////////////////////////////////////////////////
namespace tools {

  class combineParticles : public core::algorithm  {

    public:
      combineParticles( std::string , std::string);
      
      void init();

      void processEvent();
      void terminate() {}

    private:
      std::string _name;
      std::string _opt;

      std::string _p1, _p2;
      short _sign;
  };

}

