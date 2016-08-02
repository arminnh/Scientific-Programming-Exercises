cmake_minimum_required(VERSION 2.4)

project(data_smoothing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-lgsl -lgslcblas -lm")
set(CMAKE_EXE_LINKER_FLAGS "-lgsl -lgslcblas -lm")

set(SOURCE_FILES main.cpp)
add_executable(data_smoothing.bin ${SOURCE_FILES})
target_link_libraries(data_smoothing.bin -lgsl -lgslcblas -lm)

file(COPY "./data_smoothing.sh" DESTINATION .)
MAKE_DIRECTORY(images)
MAKE_DIRECTORY(output)
