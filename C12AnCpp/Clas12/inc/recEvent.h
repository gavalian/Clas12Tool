#pragma once

#include <stdint.h>

#include "Core/object.h"
namespace clas12 {

  class recEvent : public core::object {
    public:
      int32_t   NRUN   ;
      int32_t   NEVENT ;
      float     EVNTime;
      int8_t    TYPE   ;
      int16_t   EvCAT  ;
      int16_t   NPGP   ;
      int64_t   TRG    ;
      float     BCG    ;
      double    LT     ;
      float     STTime ;
      float     RFTime ;
      int8_t    Helic  ;
      float     PTIME  ;
  };
}

