# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Clas12Tool)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
#find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
#include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CLASBanks)
#ROOT_GENERATE_DICTIONARY(G__TEVNTClass TEVNTClass.h LINKDEF TEVNTClassLinkDef.h)

#---Create a shared library with geneated dictionary
#add_library(Event SHARED Event.cxx G__Event.cxx)
#target_link_libraries(Event ${ROOT_LIBRARIES})

#---Create  a main program using the library
#add_executable(Writer Utils/Write_ROOT_Dst.cxx)
#target_link_libraries(Main ClasBanks)

file(GLOB HIPO_LIB "Hipo/*cpp")
add_library(Hipo STATIC ${HIPO_LIB})

add_executable(Write_ROOT_Dst Utils/Write_ROOT_Dst.cxx)

