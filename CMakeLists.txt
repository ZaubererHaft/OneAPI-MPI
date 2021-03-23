cmake_minimum_required(VERSION 3.19)

project(MPI_TUTORIAL)

#we dont need this for INTEL MPI
#find_package(MPI REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_CXX_COMPILER mpiicpc)

add_executable(HelloWorld src/HelloWorld.cpp)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13")
    target_link_options(HelloWorld PUBLIC "-fsycl" "-lOpenCL" "-cxx=dpcpp")
else()
    SET(CMAKE_EXE_LINKER_FLAGS  "-fsycl -lOpenCL -cxx=dpcpp")
endif()

target_compile_options(HelloWorld PUBLIC "-Wall" "-Wextra" "-pedantic" "-std=c++17" "-cxx=dpcpp")
