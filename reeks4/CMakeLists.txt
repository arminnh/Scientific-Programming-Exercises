cmake_minimum_required(VERSION 2.4)

project(function_approximation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-lgsl -lgslcblas -lm")
set(CMAKE_EXE_LINKER_FLAGS "-lgsl -lgslcblas -lm")

set(SOURCE_FILES main.cpp)
add_executable(function_approximation.bin ${SOURCE_FILES})
target_link_libraries(function_approximation.bin -lgsl -lgslcblas -lm)

file(COPY "./function_approximation.sh" DESTINATION .)
MAKE_DIRECTORY(images)