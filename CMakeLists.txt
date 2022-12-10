#
# Copyright (C) 2016 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "ASacs.c IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Build one shared lib. When we build, we set the bin to $user/tmp, and
# remove it after build complete, so only the distribution place could be
# used for application linking.

cmake_minimum_required(VERSION 3.13)

project(nativelib)
set(CMAKE_VERBOSE_MAKEFILE on)

add_library(loop STATIC src/lib/nfiq/loop.c)
target_include_directories(loop PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(znorm STATIC src/lib/nfiq/znorm.c)
target_include_directories(znorm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(ridges STATIC src/lib/nfiq/ridges.c)
target_include_directories(ridges PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(ssxstats STATIC src/lib/nfiq/ssxstats.c)
target_include_directories(ssxstats PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(acs STATIC src/lib/nfiq/acs.c)
target_include_directories(acs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(remove STATIC src/lib/nfiq/remove.c)
target_include_directories(remove PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(runmlp STATIC src/lib/nfiq/runmlp.c)
target_include_directories(runmlp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(memalloc STATIC src/lib/nfiq/memalloc.c)
target_include_directories(memalloc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(syserr STATIC src/lib/nfiq/syserr.c)
target_include_directories(syserr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(chaincod STATIC src/lib/nfiq/chaincod.c)
target_include_directories(chaincod PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(shape STATIC src/lib/nfiq/shape.c)
target_include_directories(shape PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(link STATIC src/lib/nfiq/link.c)
target_include_directories(link PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(matchpat STATIC src/lib/nfiq/matchpat.c)
target_include_directories(matchpat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(binar STATIC src/lib/nfiq/binar.c)
target_include_directories(binar PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(morph STATIC src/lib/nfiq/morph.c)
target_include_directories(morph PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(sort STATIC src/lib/nfiq/sort.c)
target_include_directories(sort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(dft STATIC src/lib/nfiq/dft.c)
target_include_directories(dft PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(globals STATIC src/lib/nfiq/globals.c)
target_include_directories(globals PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(util STATIC src/lib/nfiq/util.c)
target_include_directories(util PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(fatalerr STATIC src/lib/nfiq/fatalerr.c)
target_include_directories(fatalerr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(contour STATIC src/lib/nfiq/contour.c)
target_include_directories(contour PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(line STATIC src/lib/nfiq/line.c)
target_include_directories(line PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(imgutil STATIC src/lib/nfiq/imgutil.c)
target_include_directories(imgutil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(free STATIC src/lib/nfiq/free.c)
target_include_directories(free PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(init STATIC src/lib/nfiq/init.c)
target_include_directories(init PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(block STATIC src/lib/nfiq/block.c)
target_include_directories(block PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(mlpcla STATIC src/lib/nfiq/mlpcla.c)
target_include_directories(mlpcla PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(maps STATIC src/lib/nfiq/maps.c)
target_include_directories(maps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(log STATIC src/lib/nfiq/log.c)
target_include_directories(log PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(quality STATIC src/lib/nfiq/quality.c)
target_include_directories(quality PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(detect STATIC src/lib/nfiq/detect.c)
target_include_directories(detect PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(sgemv STATIC src/lib/nfiq/sgemv.c)
target_include_directories(sgemv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(getmin STATIC src/lib/nfiq/getmin.c)
target_include_directories(getmin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)


add_library(minutia STATIC src/lib/nfiq/minutia.c)
target_include_directories(minutia PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(xytreps STATIC src/lib/nfiq/xytreps.c)
target_include_directories(xytreps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(sscal STATIC src/lib/nfiq/sscal.c)
target_include_directories(sscal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(saxpy STATIC src/lib/nfiq/saxpy.c)
target_include_directories(saxpy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(snrm2 STATIC src/lib/nfiq/snrm2.c)
target_include_directories(snrm2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(sdot STATIC src/lib/nfiq/sdot.c)
target_include_directories(sdot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(lsame STATIC src/lib/nfiq/lsame.c)
target_include_directories(lsame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)


add_library(xerbla STATIC src/lib/nfiq/xerbla.c)
target_include_directories(xerbla PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(nfiqgbls STATIC src/lib/nfiq/nfiqgbls.c)
target_include_directories(nfiqgbls PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(nfiq STATIC src/lib/nfiq/nfiq.c)
target_include_directories(nfiq PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(nativelib STATIC native_lib.c)
target_include_directories(nativelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_compile_options(loop PUBLIC -fPIC)

#TARGET LINK SECTION
target_link_libraries(quality maps)

target_link_libraries(link log loop imgutil)

target_link_libraries(chaincod globals)

target_link_libraries(shape contour sort)

target_link_libraries(loop minutia chaincod shape)

target_link_libraries(remove minutia link)

target_link_libraries(minutia maps matchpat contour line loop)

target_link_libraries(contour util globals)

target_link_libraries(imgutil line contour)

target_link_libraries(getmin detect quality)

target_link_libraries(dft sort)

target_link_libraries(matchpat globals)

target_link_libraries(binar imgutil)

target_link_libraries(ridges log sort imgutil line contour minutia)

target_link_libraries(detect log init free imgutil maps binar minutia remove ridges)

target_link_libraries(maps block log init free dft morph util)

target_link_libraries(znorm ssxstats)

target_link_libraries(sgemv lsame xerbla)

target_link_libraries(mlpcla sgemv sscal saxpy sdot snrm2)

target_link_libraries(runmlp memalloc fatalerr acs mlpcla)

target_link_libraries(memalloc syserr)

target_link_libraries(nfiq znorm nfiqgbls minutia getmin runmlp)

target_link_libraries(nativelib nfiq)

