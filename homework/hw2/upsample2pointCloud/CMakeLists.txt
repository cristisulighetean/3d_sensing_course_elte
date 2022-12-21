cmake_minimum_required(VERSION 3.9)

project( upsample2pointCloud )

###############
# packages #
###############

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

###############
# executables #
###############

add_executable( upsample2pointCloud src/main.cpp )
target_link_libraries( upsample2pointCloud ${OpenCV_LIBS} )