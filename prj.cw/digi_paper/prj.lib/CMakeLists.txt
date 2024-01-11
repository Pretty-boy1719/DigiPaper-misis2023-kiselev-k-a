add_library(digiPaper digi_paper.cpp include/digiPaper/digi_paper.hpp)
set_property(TARGET digiPaper PROPERTY CXX_STANDART 20)
target_include_directories(digiPaper PUBLIC

  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

find_package(Eigen3)
target_link_libraries(digiPaper Eigen3::Eigen)


install(TARGETS digiPaper)