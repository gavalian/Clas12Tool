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
#include "Core/outObjMgr.h"
#include "Core/tuple.h"
#include "Core/hist.h"

// _______ STL includes __________
#include <string>
using std::string;

// _______ ROOT includes __________
#include "TFile.h"

namespace root {
//////////////////////////////////////////////////////////////////////
//
// Manager of user analysis objects, i.e. hists and ntuples in ROOT
// Output objects will be saved in a single ROOT file
//////////////////////////////////////////////////////////////////////  
  class rootOutObjMgr : public core::outObjMgr {
    public:
      rootOutObjMgr( string );
      ~rootOutObjMgr();
      virtual core::tuple* mkTuple( string );
      virtual core::hist* mkHist( string, int, float, float );
      virtual void open();
      virtual void close();
    private:
      string _fname;
      TFile *_fout;
  };

};

