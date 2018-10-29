#include "dataReader.h"
#include "reader.h"
#pragma once

namespace clas12 {

  class hipoReader : public core::dataReader {

    public:
      hipoReader( const char * );
      virtual void open();
      virtual void close();
      virtual void* next();

      hipo::reader* getReader() { return _reader; }
    private:
      const char* _filename;
      hipo::reader *_reader;
  };

};

