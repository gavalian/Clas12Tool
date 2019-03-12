cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(clas12hiporoot)

set(CMAKE_INSTALL_BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_INSTALL_MANDIR ${CMAKE_CURRENT_SOURCE_DIR}/man)
set(CMAKE_CXX_FLAGS "-fPIC -O3")


# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Proof)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

#hipo expects lz4 includes to be in lib...
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
#set(ADD_COMPILER_FLAGS_PREPEND "-O3")
set(CMAKE_C_FLAGS "-O3 ${CMAKE_C_FLAGS}")
set(LZ4_BUNDLED_MODE OFF)
set(BUILD_SHARED_LIBS ON)
set(BUILD_STATIC_LIBS OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Lz4/contrib/cmake_unofficial)
set(LZ4_LIBRARY lz4)
set(LZ4_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Lz4/lib)
include_directories(${LZ4_INCLUDE_DIR})
add_definitions(-D__LZ4__)

#after Lz4 change include to include
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Hipo)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Hipo)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Clas12Banks)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Clas12Banks)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Clas12Root)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Clas12Root)

