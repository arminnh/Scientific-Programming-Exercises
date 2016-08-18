cmake_minimum_required(VERSION 2.4)

project(data_fit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-lgsl -lgslcblas -lm")
set(CMAKE_EXE_LINKER_FLAGS "-lgsl -lgslcblas -lm")

set(SOURCE_FILES main.cpp)
add_executable(data_fit ${SOURCE_FILES})
target_link_libraries(data_fit -lgsl -lgslcblas -lm)

file(COPY "./createImages.sh" DESTINATION .)
MAKE_DIRECTORY(images)

#gcc -Wall -I/usr/include/include -c gsltest.c
#gcc -o gsltest -L/usr/include/lib gsltest.o -lgsl -lgslcblas -lm
