CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
project(Eigen_test C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package( Eigen3 REQUIRED )

add_executable(hello_world main_hello.cpp)
target_link_libraries(hello_world 
  Eigen3::Eigen
)