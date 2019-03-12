if(USE_HIPO3)
  add_executable (particleDraw3 particleDraw3.cpp)
  target_link_libraries(particleDraw3 ${ROOT_LIBRARIES})

  add_executable (particleTree3 particleTree3.cpp)
  target_link_libraries(particleTree3 ${ROOT_LIBRARIES})
  install (TARGETS particleDraw3 particleTree3 DESTINATION ${CMAKE_INSTALL_BINDIR})
endif(USE_HIPO3)

if(USE_HIPO4)
  add_executable (particleDraw4 particleDraw4.cpp)
  target_link_libraries(particleDraw4 ${ROOT_LIBRARIES})

  add_executable (particleTree4 particleTree4.cpp)
  target_link_libraries(particleTree4 ${ROOT_LIBRARIES})
  install (TARGETS particleDraw4 particleTree4 DESTINATION ${CMAKE_INSTALL_BINDIR})
endif(USE_HIPO4)

