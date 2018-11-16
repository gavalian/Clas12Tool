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

// _______ Core includes __________
#include "tuple.h"
#include "hist.h"
#include "objMap.h"

// _______ STL includes __________
#include <string>
using std::string;

namespace core {
//////////////////////////////////////////////////////////////////////
//
// Manager of user analysis objects, i.e. hists and ntuples
// This is the abstract class for specific implementation 
// for backend libraries
////////////////////////////////////////////////////////////////////// 
  class outObjMgr {
    public:
      virtual ~outObjMgr() {};
      virtual bool hasTuple( string );
      virtual bool hasHist( string );

      virtual tuple* getTuple( string );
      virtual hist*  getHist( string );

      // specific implementations
      virtual tuple* mkTuple( string ) = 0;
      virtual hist* mkHist( string, int, float, float ) = 0;

    protected:
      objMap<string> _tuples;
      objMap<string> _hists;
  };

}

