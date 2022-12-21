cmake_minimum_required(VERSION 3.9)

project( data_fusion )

###############
# packages #
###############

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS})

###############
# executables #
###############

add_executable( data_fusion src/main.cpp )
target_link_libraries( data_fusion ${OpenCV_LIBS} )