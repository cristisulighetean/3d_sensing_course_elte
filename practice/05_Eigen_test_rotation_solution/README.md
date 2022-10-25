# vcpkg
1. dowload vcpkg: https://github.com/microsoft/vcpkg/tags
2. extract it
3. run bootstrap-vcpkg.bat
4. use vckpg install command to install various packages (*)
5. use vcpkg in cmake:
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE:FILEPATH=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
```

## to install Eigen (*)
```bash
vcpkg install eigen3:x64-windows
# note: E.g. there's linux version, too
```

## Eigen CMakeLists.txt example
```bash
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
```