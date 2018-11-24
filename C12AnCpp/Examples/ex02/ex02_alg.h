#pragma once 

#include "Core/algorithm.h"

class ex02_alg : public core::algorithm {

  public:
    virtual void init();
    virtual void terminate();
    virtual void processEvent();
};
