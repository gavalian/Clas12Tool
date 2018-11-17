#include "Lund/lundReader.h"
using namespace lund;

#include <memory>
#include <sstream>

lundReader::lundReader( std::string name ){
  _file.open( name );
  _ev = std::make_unique<lundEv>();
}

void lundReader::close() {
  _file.close();
}

void* lundReader::next(){
  // clear previos particles
  _ev->parts.clear();

  std::string line;
  // read header
  if( ! std::getline( _file, line ) ) { return NULL; }
  std::stringstream strs(line);
  std::string word;
  for( unsigned int i=0;i<_ev->header.size();i++){
    strs >> word;
    _ev->header[i] = std::stof( word );
  }
  
  // get N lines 
  for( int i=0; i < (int) _ev->header[0]; i++ ){
    std::getline( _file, line );
    std::stringstream ss(line);
    std::array<float,14> ar;
    for( unsigned int j=0;j<ar.size();j++){
      ss >> word;
      ar[j] = std::stof( word );
    }
    _ev->parts.push_back( ar );
  }
  return _ev.get();
}

