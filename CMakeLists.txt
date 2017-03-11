cmake_minimum_required(VERSION 3.6)
project(Proyecto1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/function.h  src/ln_profe.h src/test.h src/opt.h  src/ref.h src/alloc.h)
add_executable(Proyecto1 ${SOURCE_FILES})

project(meta)
add_executable(meta src/meta.h src/meta.cpp src/alloc.h)