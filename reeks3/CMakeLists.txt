project(data_smoothing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-lgsl -lgslcblas -lm")
set(CMAKE_EXE_LINKER_FLAGS "-lgsl -lgslcblas -lm")

set(SOURCE_FILES main.cpp)
add_executable(data_smoothing ${SOURCE_FILES})
target_link_libraries(data_smoothing -lgsl -lgslcblas -lm)

file(COPY "./createImages.sh" DESTINATION .)
MAKE_DIRECTORY(images)