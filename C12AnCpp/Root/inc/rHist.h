#pragma once

#include "hist.h"
#include "TH1F.h"

#include <string>
using std::string;

namespace root {

  class rHist : public core::hist {
    public:
      rHist( string, string, int, float, float);
      virtual ~rHist() { delete _hist; }
      virtual void fill( float );
    private:
      TH1F *_hist;
  };

};

