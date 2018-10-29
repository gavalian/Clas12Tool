#include "hipoReader.h"

using namespace clas12;

hipoReader::hipoReader( const char* name ){
  _filename = name;
  _reader = new hipo::reader();
}

void hipoReader::open(){
  _reader->open(_filename);
}

void hipoReader::close(){
  //_reader->close();
}

//#include <iostream>
void* hipoReader::next() {
  //std::cout << " hiporeader next " << std::endl;
  if( _reader->next() == false ) return NULL;
  return _reader;
}

