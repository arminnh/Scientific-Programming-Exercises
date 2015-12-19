project(sys_lineq)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-lgsl -lgslcblas -lm")
set(CMAKE_EXE_LINKER_FLAGS "-lgsl -lgslcblas -lm")

set(SOURCE_FILES main.cpp functions.cpp)
add_executable(sys_lineq ${SOURCE_FILES})
target_link_libraries(sys_lineq -lgsl -lgslcblas -lm)