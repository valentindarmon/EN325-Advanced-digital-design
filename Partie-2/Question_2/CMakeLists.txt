cmake_minimum_required(VERSION 3.0)

project(main)

SET (CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE Release)

SET (CMAKE_CXX_FLAGS "")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/intel/mkl/include -Wall")

#SET (CMAKE_EXE_LINKER_FLAGS "-pthread -lm")

# Generate the source files list
file (GLOB_RECURSE source_files src/*)

# Add includes
include_directories (src)

# Object
add_library (dec-obj OBJECT ${source_files})

add_executable(main $<TARGET_OBJECTS:dec-obj>)
