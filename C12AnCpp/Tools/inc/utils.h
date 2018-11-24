#pragma once

#include "Root/particle.h"

#include <tuple>


namespace tools {
  namespace utils {

    std::tuple<double,double,double> getDISvariables( root::particle *, float, float );
  }
}

