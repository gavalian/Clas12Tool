#pragma once 

#include "tuple.h"
#include "hist.h"
#include "objMap.h"

#include <string>
using std::string;

namespace core {
  class outObjMgr {
    public:
      virtual ~outObjMgr() {};
      virtual bool hasTuple( string );
      virtual bool hasHist( string );

      virtual tuple* getTuple( string );
      virtual hist*  getHist( string );
      virtual tuple* mkTuple( string ) = 0;
      virtual hist* mkHist( string, int, float, float ) = 0;

    protected:
      objMap<string> _tuples;
      objMap<string> _hists;
  };

};

