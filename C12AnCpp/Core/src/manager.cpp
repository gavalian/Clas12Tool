#include "manager.h"
#include <iostream>
#include <memory>
using namespace std;
using namespace core;

manager::manager() {
  _obj = new objContainer();
  _alg = new algContainer();
}

manager::~manager() {
  delete _obj;
  delete _alg;
}

void manager::addAlgorithm( algorithm *a ){
  a->setObjContainer(_obj);
  a->setDataReader(_reader);
  a->setOutMgr( _outmgr );
  _alg->push_back(a);
}


void manager::run() {
  cout << " ======================  RUN " << endl; 

  // initialization of all the algorithms
  for( auto alg : (*_alg) ){  alg->init() ;}

  // loop over entries
  while( _reader->next() ){
    
    // run algorithms over the entry
    for( auto alg : (*_alg) ){ alg->processEvent(); }
  
    // clear the temporary object container
    _obj->clear();
  }

  // at the end of the loop on events call terminate
  for( auto alg : (*_alg) ) alg->terminate() ;

}


// implementation of manager as singleton
manager* manager::_manager = 0;

manager* manager::instance(){
  if( _manager == 0 ){
    _manager = new manager();
  }
  return _manager;
}
