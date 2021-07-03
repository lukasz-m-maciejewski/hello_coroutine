cmake_minimum_required(VERSION 3.15)
project(hello_coroutine CXX)

find_package(PkgConfig REQUIRED)

add_executable(hello main_hello.cpp)
target_compile_features(hello PUBLIC cxx_std_20)
target_compile_options(hello PUBLIC -fcoroutines)
