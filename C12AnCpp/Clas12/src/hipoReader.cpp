#include "hipoReader.h"

using namespace clas12;

#include <fstream>
#include <iostream>

hipoReader::hipoReader( std::string name ){

  // check if a single hipo file or a list of files
  if( name.find(".hipo") != std::string::npos ){
    _filelist.push_back( name );
  }
  else{
    // read all the lines in the text file and add them
    std::ifstream inf( name );
    std::string f;
    while( inf >> f ){
      if( f.find(".hipo") == std::string::npos ){
        // no hipo name, skipping
        std::cerr << " warning, file " << f <<" does not end in .hipo. Skipping it\n";
      }
      else{
        _filelist.push_back(f);
      }
    }
    inf.close();
  }
  _reader = new hipo::reader();
  _ifile = 0;
}

void hipoReader::open(){
  _filename = _filelist[_ifile].c_str();
  std::cout << " *** hipoReader: Opening file: " << _filename << std::endl;
  _reader->open(_filename);
}

void hipoReader::close(){
  //_reader->close();
}

void* hipoReader::next() {
  if( _reader->next() == false ){

    // check if there are other files to read
    if ( (_ifile+1) < _filelist.size() ){

      // switch file
      _ifile++;
      open();
      if( _reader->next() == false) return NULL;
    }
    else return NULL;
  }
  return _reader;
}

