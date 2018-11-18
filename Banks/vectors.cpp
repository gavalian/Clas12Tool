/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "vectors.h"


namespace clas12 {



  vector3  operator+(const vector3 &a, const vector3 &b)
  { return vector3(a.x() + b.x(),
  		    a.y() + b.y(),
  		    a.z() + b.z());
  }
  vector3  operator-(const vector3 &a, const vector3 &b)
  { return vector3(a.x() - b.x(),
  		    a.y() - b.y(),
  		    a.z() - b.z());
  }

  const  vector3 &vector3::operator=(const vector3 &vec)
  {
    this->setXYZ(vec.x(),vec.y(),vec.z());
    return *this;
  }
  vector3  operator*(double a, const vector3 &b)
  {
    return vector3(a*b.x(),a*b.y(),a*b.z());
  }
  vector3  operator*(const vector3 &b,double a)
  {
    return vector3(a*b.x(),a*b.y(),a*b.z());
  }



  double vector4::m()
   {
      double ___m2 = m2();
      if(___m2<0) return -sqrt(-___m2);
      return sqrt(___m2);
  }


}
