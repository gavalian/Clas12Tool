
ROOT_GENERATE_DICTIONARY(G__Hipo4  reader.h bank.h LINKDEF HipoLinkDef.h)

add_library(Hipo4 SHARED utils.cpp dictionary.cpp  event.cpp record.cpp recordbuilder.cpp reader.cpp bank.cpp  G__Hipo4.cxx)
target_link_libraries(Hipo4 ${ROOT_LIBRARIES})

install(TARGETS Hipo4
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

FILE(GLOB ROOT_HIPO_PCM ${CMAKE_BINARY_DIR}/Hipo4/*pcm)

install (FILES ${ROOT_HIPO_PCM}   
         DESTINATION "${CMAKE_INSTALL_LIBDIR}")
