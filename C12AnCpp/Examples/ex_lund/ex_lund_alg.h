#pragma once 

#include "Core/algorithm.h"

class ex_lund_alg : public core::algorithm {

  public:
    virtual void init();
    virtual void terminate();
    virtual void processEvent();
};
