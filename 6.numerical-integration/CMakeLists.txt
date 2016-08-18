cmake_minimum_required(VERSION 2.4)

project(numerical_integration)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-lgsl -lgslcblas -lm")
set(CMAKE_EXE_LINKER_FLAGS "-lgsl -lgslcblas -lm")

set(SOURCE_FILES main.cpp)
add_executable(numint.bin ${SOURCE_FILES})
target_link_libraries(numint.bin -lgsl -lgslcblas -lm)