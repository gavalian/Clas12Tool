
ROOT_GENERATE_DICTIONARY(G__Hipo3 utils.h dictionary.h node.h event.h record.h reader.h bank.h  LINKDEF HipoLinkDef.h)

add_library(Hipo3 SHARED utils.cpp dictionary.cpp node.cpp event.cpp record.cpp reader.cpp bank.cpp G__Hipo3.cxx)
target_link_libraries(Hipo3 ${ROOT_LIBRARIES})

#install(TARGETS Hipo
#  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

FILE(GLOB ROOT_HIPO_PCM ${CMAKE_BINARY_DIR}/Hipo3/lib*)

install (FILES ${ROOT_HIPO_PCM}   
         DESTINATION "${CMAKE_INSTALL_LIBDIR}")
