```
   ___________  ___        _____        
  / ___<  /_  |/ _ | ___  / ___/__  ___ 
 / /__ / / __// __ |/ _ \/ /__/ _ \/ _ \
 \___//_/____/_/ |_/_//_/\___/ .__/ .__/
                           /_/  /_/    
 Yet another analysis framework for CLAS12 data, but in C++
```


# C12AnCpp
C++ based analysis framework for CLAS12 data

The current implementation allows the user to analyse **CLAS12 DST** data in hipo or **LUND** files. 

The goal of this framework it to make easy for the user to extract information from the data and to save ntuples or histograms. The current implementation allows the user to save ROOT TTree and TH1F or CSV histograms and ntuples.

The main feature of this framework are:

+ High modularity: new features can be easily added and modifications to will have only a limited local impact
+ Promotion of **collaborative work**: users can contribute with new features (tools or algorithms) that can be easily included and used in others' analyses. 

# Installation

## Prerequisites

+ This code is written in C++14. Check if your compiler is compatible, if not..  why are you living in the past?, install a newer compiler!! :)
For example, g++-5 or newer

+ ROOT6 is required. If not installed, [here](https://root.cern.ch/)

+ You should have already cloned/installed Clas12Tool. If not, [here](https://github.com/gavalian/Clas12Tool)

## Set up the environment

+ Edit the path to Clas12Tool in `setEnv.sh`

```bash
export CLAS12TOOL=/YOUR/PATH/GOES/HERE/Clas12Tool
```

+ Source the environment

```bash
source setEnv.sh
```

It is strongly suggested that you automatically source the environment. The following line allows you to add it to the `.bashrc`

```bash
echo "source `pwd`/setEnv.sh" >> $HOME/.bashrc
```

+ Compile. If you want debug information, export the variable `DEBUG="-g"`

``` bash
make
```

for faster compilation, add `-j` and the number of cores you want to use.

# User analysis **algorithms**

User analyses are indeed algorithms.

An algorithm should inherit from `core::algorithm` and it should implement (at least) three methods:
```c++
void init(); // called once at the beginning of the execution

void processEvent(); // this method will contain the _actual_ code of analysis

void terminate(); // called once at the end of the execution
```

As an example:

```c++
// ex01_alg.h
#include "Core/algorithm.h"

class test : public core::algorithm {

  public:
    virtual void init();
    virtual void terminate();
    virtual void processEvent();
};
```

```c++
// ex01_alg.cpp
#include "ex01_alg.h"

#include "Root/particle.h"
#include "Core/objVector.h"
#include "Core/tuple.h"

void ex01_alg::init(){
}

void ex01_alg::terminate(){
}

void ex01_alg::processEvent(){

  core::objVector *electrons = (core::objVector*) getObject("electrons");
  if( ! electrons ){ 
    return; 
  }

  // get a ntuple
  core::tuple *tpl = this->ntuple("etpl");

  // get a histogram
  core::hist *h = this->histo("he",500,0, 12);

  for( unsigned int i=0; i < electrons->size(); i++ ){

    root::particle *p1 = (root::particle*) (*electrons)[i].get();

    tpl->column( "P", p1->P() );
    tpl->column( "Theta", p1->Theta() );
    tpl->column( "Phi", p1->Phi() );
    tpl->column( "PID", p1->getPid() );

    tpl->fill();
    h->fill( p1->P() );
  }
}

```

For more detailed examples, browse inside the Examples folder

# Tools

Tools can be:

+ Implementations of specific tasks that have to be done over an object. Typical use: filling ntuples with specific variables.
+ Algorithms that are of common interest
