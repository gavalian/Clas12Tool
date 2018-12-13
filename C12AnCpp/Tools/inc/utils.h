#pragma once

#include "Root/particle.h"

#include <tuple>


namespace tools {
  namespace utils {

    // compute Q2, xB, W2
    // takes as input a scattered electron, the energy of the electron beam 
    // and the id of the target particle
    std::tuple<double,double,double> getDISvariables( root::particle *, float, int );
  }
}

