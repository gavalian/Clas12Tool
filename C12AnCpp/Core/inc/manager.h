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

#ifndef MANAGER_H
#define MANAGER_H

// _______ Core includes __________
#include "dataReader.h"
#include "dataWriter.h"
#include "objContainer.h"
#include "algContainer.h"
#include "algorithm.h"

namespace core {

//////////////////////////////////////////////////////////////////////                         
//
// Manager steers the data processing flow and orchestrates the algs
////////////////////////////////////////////////////////////////////// 
  class manager {
    public:
      ~manager();
      
      static manager* instance();

      void addDataReader( dataReader *dr ) { _reader = dr; }
      dataReader* getDataReader(){ return _reader; }

      void addDataWriter( dataWriter *dw ) { _writer = dw; }
      dataWriter* getDataWriter(){ return _writer; }
      
      void setOutObjMgr( outObjMgr *oom ) { _outmgr = oom; } 

      void addAlgorithm( algorithm* );

      void run();
    private:
      manager(); // private constructor for singleton implementation
      static manager *_manager;

      dataReader *_reader;
      dataWriter *_writer;

      objContainer *_obj;  // Temporary Data Conteiner
      algContainer *_alg;  // Algorithm list

      outObjMgr *_outmgr;  // manager of analysis output objects
  };

}

#endif

