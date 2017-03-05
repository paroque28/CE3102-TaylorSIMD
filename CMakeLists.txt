cmake_minimum_required(VERSION 3.6)
project(Proyecto1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/function.h  src/ln_profe.h src/test.h)
add_executable(Proyecto1 ${SOURCE_FILES})