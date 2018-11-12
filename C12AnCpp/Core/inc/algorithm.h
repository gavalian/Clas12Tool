#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "outObjMgr.h"
#include "tuple.h"
#include "hist.h"
#include "objContainer.h"
#include "dataReader.h"

#include <string>
#include <memory>
#include "object.h"

namespace core {
  
  class algorithm {
    public:
      algorithm() {};
      void setObjContainer( objContainer *o) { _obj = o; }
      virtual void setDataReader( dataReader *r ) { _reader = r; }
      virtual dataReader* getDataReader() { return _reader; }

      virtual void init() = 0;
      virtual void processEvent() = 0;
      virtual void terminate() = 0;

      virtual void bookObject( std::string, std::shared_ptr<object>);
      virtual void* getObject( std::string  );
     
      virtual void setOutMgr( outObjMgr *m ) { _oom = m; }

      virtual tuple* ntuple( std::string );
      virtual hist*  histo( std::string, int, float, float );
      
    private:
      objContainer *_obj;
      dataReader *_reader;
      outObjMgr *_oom;
  };

};

#endif

