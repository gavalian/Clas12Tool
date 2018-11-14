#pragma once

#include "dataReader.h"
#include "reader.h"

#include <vector>
#include <string>

namespace clas12 {

  class hipoReader : public core::dataReader {

    public:
      hipoReader( std::string );
      virtual void open();
      virtual void close();
      virtual void* next();

      hipo::reader* getReader() { return _reader; }
    private:
      const char* _filename;
      std::vector<std::string> _filelist;
      unsigned int _ifile;
      hipo::reader *_reader;
  };

}

