# -DCMAKE_BUILD_TYPE=Debug or Release

cmake_minimum_required(VERSION 3.13)

project(nativelib)
set(CMAKE_VERBOSE_MAKEFILE on)
add_definitions(-D__NBISLE__)
add_definitions(-Dmsimd128)

FILE(GLOB_RECURSE SRC_FILES "src/**/*.c" "native_lib.c")
FILE(GLOB_RECURSE INCL_FILES "include/**/*.h")

ADD_LIBRARY(${PROJECT_NAME}_objects STATIC ${SRC_FILES} ${INCL_FILES} )
INCLUDE_DIRECTORIES(include/nfiq include/imgtools include/commonbis include/pcasys include/bozorth include/mindtct)

# run locally (contains errors)
# add_executable(main ${SRC_FILES})
# INCLUDE_DIRECTORIES(main PUBLIC include/nfiq include/imgtools include/commonbis include/pcasys include/bozorth include/mindtct)
# target_link_libraries(main ${PROJECT_NAME}_objects m )