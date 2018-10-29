#ifndef MANAGER_H
#define MANAGER_H

#include "dataReader.h"
#include "dataWriter.h"
#include "objContainer.h"
#include "algContainer.h"
#include "algorithm.h"

namespace core {

  class manager {
    public:
      ~manager();
      
      static manager* instance();

      void addDataReader( dataReader *dr ) { _reader = dr; }
      void addDataWriter( dataWriter *dw ) { _writer = dw; }
      dataReader* getDataReader(){ return _reader; }
      dataWriter* getDataWriter(){ return _writer; }

      void addAlgorithm( algorithm* );

      void run();
    private:
      manager();
      static manager *_manager;

      dataReader *_reader;
      dataWriter *_writer;

      objContainer *_obj;
      algContainer *_alg;
  };

};

#endif

