
add_executable (particleDraw particleDraw.cpp)
target_link_libraries(particleDraw ${ROOT_LIBRARIES})

add_executable (particleTree particleTree.cpp)
target_link_libraries(particleTree ${ROOT_LIBRARIES})


install (TARGETS particleDraw particleTree DESTINATION ${CMAKE_INSTALL_BINDIR})
