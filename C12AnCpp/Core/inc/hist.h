#pragma once 

#include "object.h"

#include <string>
using std::string;

namespace core {
  class hist : public object {
    public:
      hist( string, string, int, float, float);
      virtual ~hist() {};
      virtual void fill( float ) = 0;
    private:
      string name;
      string title;
      int nbins;
      float min;
      float max;
  };

};

