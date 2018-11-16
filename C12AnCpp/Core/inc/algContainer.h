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

#ifndef ALGCONTAINER_H
#define ALGCONTAINER_H

// _______ Core includes __________
#include "algorithm.h"

// _______ STL includes __________
#include <vector>

namespace core {
//////////////////////////////////////////////////////////////////////
//
// Algorithm container. 
//////////////////////////////////////////////////////////////////////
  class algContainer : private std::vector<algorithm*>{
    public:
      static algContainer* instance();
      using std::vector<algorithm*>::push_back;
      using std::vector<algorithm*>::begin;
      using std::vector<algorithm*>::end;
      using std::vector<algorithm*>::size;

    private:
      algContainer() {} 
      static algContainer* _algCont;
  };

  algContainer* algContainer::_algCont = 0;
  
  algContainer* algContainer::instance() {
    if( _algCont == 0 ){
      _algCont = new algContainer();
    }
    return _algCont;
  }
  
}

#endif

