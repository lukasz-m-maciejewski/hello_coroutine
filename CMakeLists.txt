cmake_minimum_required(VERSION 3.15)
project(hello_coroutine CXX)

find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(hello main_hello.cpp)
target_compile_features(hello PUBLIC cxx_std_20)
target_compile_options(hello PUBLIC -fcoroutines)

add_executable(minimal_coroutine_example minimal_coroutine_example.cpp)
target_compile_features(minimal_coroutine_example PUBLIC cxx_std_20)
target_compile_options(minimal_coroutine_example PUBLIC -fcoroutines)

add_executable(await_exploration await_exploration.cpp)
target_compile_features(await_exploration PUBLIC cxx_std_20)
target_compile_options(await_exploration PUBLIC -fcoroutines)
