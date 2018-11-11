#pragma once

#include "outObjMgr.h"
#include "tuple.h"
#include "hist.h"

#include <string>
using std::string;

namespace root {
  
  class rootOutObjMgr : public core::outObjMgr {
    public:
      virtual core::tuple* mkTuple( string );
      virtual core::hist* mkHist( string, int, float, float );
  };

};

