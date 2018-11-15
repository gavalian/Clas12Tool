#include "combineParticles.h"

using namespace tools;

#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
using namespace std;

// core includes 
#include "objVector.h"
#include "object.h"

combineParticles::combineParticles( string n, string o ) : _name(n), _opt(o){ } 

void combineParticles::init() { 

  // trim input
  _opt.erase(remove( _opt.begin(), _opt.end(), ' '), _opt.end());
  cout << _opt << endl;

  char delim = '+';
  _sign = 1;
  if( _opt.find(delim) != string::npos ){ }
  else { 
    delim = '-';
    _sign = -1;
    if( _opt.find(delim) != string::npos ){ }
    else{
      _sign = -99;
      cerr << " [WARNING] combineParticles malformed option\n";
      return;
    } 
  }

  vector<string> substrs;
  stringstream ss(_opt);
  string item;
  while(getline(ss,item,delim)){
    substrs.push_back(item);
  }
  if( substrs.size() > 1 ){
    _p1 = substrs[0];
    _p2 = substrs[1];
  }
  else{
    cerr << " [WARNING] combineParticles: too few particles\n";
    _sign = -99;
  }

}


void combineParticles::processEvent(){

  // check if there were no errors in the inputs: sign must be either +1 or -1
  if( abs( _sign ) != 1 ) return;

  // get input particles
  core::objVector *vp1 = (core::objVector*) getObject(_p1);
  if( ! vp1 ) return;

  core::objVector *vp2 = ( _p1 == _p2 ) ? vp1 : (core::objVector*) getObject(_p2);
  if( ! vp2 ) return;
  // make candidates
  shared_ptr<core::objVector> cands = make_shared<core::objVector>();

  for( unsigned int ip1=0; ip1 < vp1->size(); ip1++ ){
    root::particle *p1 = (root::particle*) (*vp1)[ip1].get();
    
    unsigned int start2 = ( _p1 == _p2 ) ? ip1+1 : 0;
    for( unsigned int ip2 = start2 ; ip2 < vp2->size(); ip2++ ){
      root::particle *p2 = (root::particle*) (*vp2)[ip2].get();

      // actual combine
      root::particle p = (_sign==1) ? *p1 + *p2 : *p1 - *p2 ;

      // push the candidate in the vector
      unique_ptr<root::particle> p3 = make_unique<root::particle>(p);
      cands->push_back( move(p3) ); 
      
    }
  }

  bookObject( _name, cands );
}

