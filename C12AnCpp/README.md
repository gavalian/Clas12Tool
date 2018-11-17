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

# Installation

## Prerequisits

+ This code is written in C++14. Check if your compiler is compatible, if not..  why are you living in the past?, install a newer compiler!! :)
For exemple, g++-5 or newer

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

for faster compilation, add `-j` and the number of core you want to use.



# analysis algorithm
See in Examples test.cpp
