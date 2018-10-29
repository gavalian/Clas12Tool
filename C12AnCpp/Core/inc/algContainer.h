#ifndef ALGCONTAINER_H
#define ALGCONTAINER_H

#include <vector>
#include "algorithm.h"

namespace core {

  class algContainer : private std::vector<algorithm*>{
    public:
      static algContainer* instance();
      using std::vector<algorithm*>::push_back;
      using std::vector<algorithm*>::begin;
      using std::vector<algorithm*>::end;
      using std::vector<algorithm*>::size;

    private:
      static algContainer* _algCont;
  };

  algContainer* algContainer::_algCont = 0;
  
  algContainer* algContainer::instance() {
    if( _algCont == 0 ){
      _algCont = new algContainer();
    }
    return _algCont;
  }
  
};

#endif

