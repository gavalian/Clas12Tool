#ifndef RECTRACK_H
#define RECTRACK_H
#include <stdint.h>

#include "object.h"

namespace clas12 {

  class recTrack : public core::object {
    public:
       int16_t  NDF;
       int16_t  NDF_nomm;
       float       chi2;
       float    chi2_nomm;
       int8_t   detector;
       int16_t    index;
       int16_t   pindex;
       float    px_nomm;
       float    py_nomm;
       float    pz_nomm;
       int8_t         q;
       int8_t    sector;
       int16_t   status;
       float    vx_nomm;
       float    vy_nomm;
       float    vz_nomm;

       float   getP();     
       float   getPT();    
       float   getPhi();   
       float   getTheta(); 
  };
};

#endif 

