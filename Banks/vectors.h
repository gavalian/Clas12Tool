/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   particle.h
 * Author: gavalian
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef VECTORS_H
#define VECTORS_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include "bank.h"


namespace clas12 {

  class vector3 {

  private:
    double cX;
    double cY;
    double cZ;

  public:

   vector3 (){}
   vector3 (double x, double y, double z){ cX = x; cY = y; cZ = z;}
  ~vector3 (){}

    void  setXYZ(double x, double y, double z){cX=x;cY=y;cZ=z;}

    double x() const { return cX;}
    double y() const { return cY;}
    double z() const { return cZ;}

    double mag() { return sqrt(mag2());}
    double mag2(){ return (cX*cX + cY*cY + cZ*cZ);}
    const  vector3 &operator=(const vector3 &vec);
    inline vector3 & operator += (const vector3 &);
    inline vector3 & operator -= (const vector3 &);
  };

  vector3  operator+(const vector3 &a, const vector3 &b);
  vector3  operator-(const vector3 &a, const vector3 &b);
  vector3  operator*(double a, const vector3 &b);
  vector3  operator*(const vector3 &b,double a);

  inline vector3& vector3::operator += (const vector3 & p)
  {  cX += p.cX;   cY += p.cY;  cZ += p.cZ;   return *this; }

  inline vector3& vector3::operator -= (const vector3 & p)
  {  cX -= p.cX;   cY -= p.cY;  cZ -= p.cZ;   return *this; }

  class vector4  {
  private:

    vector3  fVect;
    double    fE;

  public:

  vector4 () {fVect.setXYZ(0.0,0.0, 0.0); fE = 0.0;}
  vector4 (double _px, double _py, double _pz, double _e){
     fVect.setXYZ(_px,_py, _pz); fE = _e;
  }
  
  vector4 (vector3 v, double energy) { fVect = v; fE = energy;};

  ~vector4(){}

  void setXYZM(double _px, double _py, double _pz, double _m){
     fVect.setXYZ(_px,_py, _pz);
     fE = sqrt(fVect.mag2()+_m*_m);
  }

  double m2(){ return (fE*fE - fVect.mag2());}
  double m();
  double    e() const {return fE;};
  double    t() const {return fE;};
  vector3  vect()  const {return fVect;};

  inline vector4 & operator = (const vector4 &);
  inline vector4   operator +  (const vector4 &) const;
  inline vector4   operator -  (const vector4 &) const;
  inline vector4 & operator += (const vector4 &);
  inline vector4 & operator -= (const vector4 &);
};


inline vector4 &vector4::operator = (const vector4 & q)
{
  fVect = q.vect();
  fE = q.t();
  return *this;
}

inline vector4 vector4::operator + (const vector4 & q) const {
  return vector4(fVect+q.vect(), fE+q.t());
}
inline vector4 &vector4::operator += (const vector4 & q) {   fVect += q.vect();  fE += q.t()
;   return *this;
}
inline vector4 vector4::operator - (const vector4 & q) const {
return vector4(fVect-q.vect(), fE-q.t());
}
inline vector4 &vector4::operator -= (const vector4 & q) {
  fVect -= q.vect();   fE -= q.t();  return *this;
}
}

#endif /* UTILS_H */
