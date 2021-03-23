cmake_minimum_required(VERSION 3.13)

project(MPI_TUTORIAL)

#we dont need this for INTEL MPI
#find_package(MPI REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_CXX_COMPILER mpiicpc)

set(LINK_FLAGS "-fsycl" "-lOpenCL" "-cxx=dpcpp")
set(COMPILE_FLAGS "-Wall" "-Wextra" "-pedantic" "-std=c++17" "-cxx=dpcpp")

add_executable(HelloWorld src/HelloWorld.cpp)
add_executable(SendReceive src/SendReceive.cpp)
add_executable(Chain src/Chain.cpp)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13")
    target_link_options(HelloWorld PUBLIC ${LINK_FLAGS})
    target_link_options(SendReceive PUBLIC ${LINK_FLAGS})
    target_link_options(Chain PUBLIC ${LINK_FLAGS})
else()
    SET(CMAKE_EXE_LINKER_FLAGS ${LINK_FLAGS})
endif()

target_compile_options(HelloWorld PUBLIC ${COMPILE_FLAGS})
target_compile_options(SendReceive PUBLIC ${COMPILE_FLAGS})
target_compile_options(Chain PUBLIC ${COMPILE_FLAGS})

