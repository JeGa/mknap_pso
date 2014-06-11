cmake_minimum_required(VERSION 2.8)
project(mknap_pso)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

file(GLOB_RECURSE mknap_pso_SOURCES "src/*.cpp")
file(GLOB_RECURSE mknap_pso_HEADERS "src/*.h")

set(mknap_pso_INCLUDE_DIRS "")
foreach (_headerFile ${mknap_pso_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND mknap_pso_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES mknap_pso_INCLUDE_DIRS)

include_directories(${mknap_pso_INCLUDE_DIRS})
include_directories("include")

add_executable(mknap_pso ${mknap_pso_SOURCES})