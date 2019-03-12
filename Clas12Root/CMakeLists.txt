ROOT_GENERATE_DICTIONARY(G__Clas12Root  BankHist.h HipoHist.h HipoTreeMaker.h HipoChain.h HipoRootAction.h   HipoROOTOut.h ParticleHist.h HipoSelector.h ParticleTree.h LINKDEF Clas12RootLinkDef.h)

add_library(Clas12Root SHARED BankHist.cpp HipoHist.cpp HipoTreeMaker.cpp HipoChain.cpp HipoRootAction.cpp   HipoROOTOut.cpp ParticleHist.cpp  HipoSelector.cpp ParticleTree.cpp G__Clas12Root.cxx)

target_link_libraries(Clas12Root ${ROOT_LIBRARIES})

#install(TARGETS Clas12Root
#  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

FILE(GLOB ROOT_C12ROOT_PCM ${CMAKE_BINARY_DIR}/Clas12Root/lib*)

install (FILES  ${ROOT_C12ROOT_PCM}    
  DESTINATION "${CMAKE_INSTALL_LIBDIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/src)
