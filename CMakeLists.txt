cmake_minimum_required(VERSION 3.6)
project(anpiSIMD)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -lpython2.7")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/function.h  src/ln_profe.h src/test.h src/opt.h  src/ref.h src/alloc.h lib/optionparser.h lib/matplotlibcpp.h src/meta.h)
add_executable(anpiSIMD ${SOURCE_FILES})
