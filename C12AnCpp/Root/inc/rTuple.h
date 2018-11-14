#pragma once

#include "tuple.h"

#include <string>
using std::string;

#include "TTree.h"

namespace root {

  class rTuple : public core::tuple {
    public:
      rTuple( string, string );
      virtual ~rTuple() { delete tree; }

      /*void column( string, float * );*/
      void fill();
      void write();
    private:
      TTree *tree;  
  };

};

