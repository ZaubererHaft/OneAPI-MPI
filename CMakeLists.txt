cmake_minimum_required(VERSION 3.19)
set( CMAKE_VERBOSE_MAKEFILE on )

project(TEST)
set(CMAKE_CXX_COMPILER dpcpp)

find_package(MPI REQUIRED)

add_executable(TEST src/main.cpp)

target_include_directories(TEST PUBLIC ${MPI_CXX_INCLUDE_DIRS})
SET(CMAKE_EXE_LINKER_FLAGS  "-L'/opt/intel/oneapi/mpi/2021.1.1/lib/release' -L'/opt/intel/oneapi/mpi/2021.1.1/lib' -Xlinker --enable-new-dtags -Xlinker -rpath -Xlinker '/opt/intel/oneapi/mpi/2021.1.1/lib/release' -Xlinker -rpath -Xlinker '/opt/intel/oneapi/mpi/2021.1.1/lib' -lmpicxx -lmpifort -lmpi -ldl -lrt -lpthread")
target_compile_definitions(TEST PUBLIC ${MPI_CXX_COMPILE_DEFINITIONS})
target_compile_options(TEST PUBLIC -std=c++17 -Wall ${MPI_CXX_COMPILE_FLAGS})
