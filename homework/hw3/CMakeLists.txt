cmake_minimum_required(VERSION 3.9)

project( 3dSensing_ICP )

###############
# packages #
###############

#find_package( nanoflann )
find_package( OpenCV REQUIRED )
find_package(Eigen3 REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

###############
# executables #
###############

add_executable( 3dSensing_ICP src/main.cpp )
target_link_libraries( 3dSensing_ICP Eigen3::Eigen )
target_link_libraries( 3dSensing_ICP ${OpenCV_LIBS} )