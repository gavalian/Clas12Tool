#include "manager.h"
#include <iostream>
#include <memory>
using namespace std;
using namespace core;

manager::manager() {
  cout << " +++++++++++++++++++++++++++++\n";
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
  _alg->push_back(a);
}


void manager::run() {
 cout << " ======================  RUN " << endl; 
 //void *ev = 0x0;
  for( auto alg : (*_alg) ){  alg->init() ;}
  while( _reader->next() ){
    //cout << " next " << endl;
    //(*_obj)["Event"] = std::make_unique<ev>();
    //cout << (*_alg).size() << "  ... " << endl;
    for( auto alg : (*_alg) ){ alg->processEvent(); }

    // TODO clean objects
    //for( auto o : (*_obj) ) { if( o.second != NULL ){ cout << o.first << endl;  delete (o.second); } }
    _obj->clear();
  }

  // at the end of the loop on events call terminate
  for( auto alg : (*_alg) ) alg->terminate() ;

  // 
}

manager* manager::_manager = 0;

manager* manager::instance(){
  if( _manager == 0 ){
    _manager = new manager();
  }
  return _manager;
}
