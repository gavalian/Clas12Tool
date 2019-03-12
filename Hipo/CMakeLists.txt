
ROOT_GENERATE_DICTIONARY(G__Hipo utils.h dictionary.h node.h event.h record.h reader.h bank.h  LINKDEF HipoLinkDef.h)

add_library(Hipo SHARED utils.cpp dictionary.cpp node.cpp event.cpp record.cpp reader.cpp bank.cpp G__Hipo.cxx)
target_link_libraries(Hipo ${ROOT_LIBRARIES})

#install(TARGETS Hipo
#  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

FILE(GLOB ROOT_HIPO_PCM ${CMAKE_BINARY_DIR}/Hipo/lib*)

install (FILES ${ROOT_HIPO_PCM}   
         DESTINATION "${CMAKE_INSTALL_LIBDIR}")
