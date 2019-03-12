ROOT_GENERATE_DICTIONARY(G__Clas12Banks3  vectors.h header.h particle.h mcparticle.h detector.h scaler.h vtp.h particle_detector.h scintillator.h tracker.h traj.h forwardtagger.h cherenkov.h calorimeter.h covmatrix.h region_particle.h region_ft.h region_fdet.h region_cdet.h clas12reader.h  LINKDEF Clas12LinkDef.h)

add_library(Clas12Banks3 SHARED vectors.cpp header.cpp particle.cpp mcparticle.cpp detector.cpp scaler.cpp vtp.cpp particle_detector.cpp scintillator.cpp tracker.cpp traj.cpp forwardtagger.cpp cherenkov.cpp calorimeter.cpp covmatrix.cpp region_particle.cpp region_ft.cpp region_fdet.cpp region_cdet.cpp clas12reader.cpp   G__Clas12Banks3.cxx)

target_link_libraries(Clas12Banks3 ${ROOT_LIBRARIES})

FILE(GLOB ROOT_CLAS12_PCM ${CMAKE_BINARY_DIR}/Clas12Banks3/lib*)

install (FILES  ${ROOT_CLAS12_PCM}     
         DESTINATION "${CMAKE_INSTALL_LIBDIR}")
