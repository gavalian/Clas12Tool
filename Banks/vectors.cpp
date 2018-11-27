/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "vectors.h"


namespace clas12 {

  void       vector3::translate(double x, double y, double z){
    cX += x; cY += y; cZ += z;
  }

  void       vector3::rotateX(double angle)
  {
    double s = sin(angle);
    double c = cos(angle);
    double yy = cY;
    cY = c*yy - s*cZ;
    cZ = s*yy + c*cZ;
  }
  void       vector3::rotateY(double angle)
{
  double s = sin(angle);
  double c = cos(angle);
  double zz = cZ;
  cZ = c*zz - s*cX;
  cX = s*zz + c*cX;
}
//------------------------------------------------------
void       vector3::rotateZ(double angle)
{
  double s = sin(angle);
  double c = cos(angle);
  double xx = cX;
  cX = c*xx - s*cY;
  cY = s*xx + c*cY;
}

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
