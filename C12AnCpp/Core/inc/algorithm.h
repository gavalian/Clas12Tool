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

#ifndef _ALGORITHM_H
#define _ALGORITHM_H

// _______ Core includes __________
#include "outObjMgr.h"
#include "tuple.h"
#include "hist.h"
#include "object.h"
#include "objContainer.h"
#include "dataReader.h"

// _______ STL includes __________
#include <string>
#include <memory>

namespace core {
 
//////////////////////////////////////////////////////////////////////
//
// Algorithm base class
//////////////////////////////////////////////////////////////////////     
  class algorithm {
    public:
      algorithm() {};
      void setObjContainer( objContainer *o) { _obj = o; }
      virtual void setDataReader( dataReader *r ) { _reader = r; }
      virtual dataReader* getDataReader() { return _reader; }

      // User defined methods
      // -----------------------------------------------
      virtual void init() = 0;
      virtual void processEvent() = 0;
      virtual void terminate() = 0;
      // -----------------------------------------------

      virtual void bookObject( std::string, std::shared_ptr<object>);
      virtual void* getObject( std::string  );
     
      virtual void setOutMgr( outObjMgr *m ) { _oom = m; }

      // create or get instances of analysis objects
      virtual tuple* ntuple( std::string );
      virtual hist*  histo( std::string, int, float, float );
      
    private:
      objContainer *_obj;  // pointer to Temporary Data Container
      dataReader *_reader; // interface to data source
      outObjMgr *_oom;     // analysis object output manager
  };

}

#endif

