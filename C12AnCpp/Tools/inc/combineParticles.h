#pragma once

#include "particle.h"

#include "algorithm.h"

#include <string>

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

