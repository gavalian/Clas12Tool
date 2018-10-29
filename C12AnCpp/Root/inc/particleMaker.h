#ifndef _ROOT_PARTICLEMAKER_H
#define _ROOT_PARTICLEMAKER_H

#include "algorithm.h"

#include <map>
#include <string>

namespace root {

  class particleMaker : public core::algorithm {
   
    public:
      virtual void init();
      virtual void processEvent();
      virtual void terminate() {} 

    private:

      std::map<int,std::string> _pname;
  };
};

#endif

