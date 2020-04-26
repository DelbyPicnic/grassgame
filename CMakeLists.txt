cmake_minimum_required(VERSION 3.9)

# Set compiler flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(APPLE)
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
  set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
endif()

# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GrassGame)

### Setup Directories ###
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Add External Deps ###
# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")



file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####
file(GLOB_RECURSE SOURCE_FILES engine/src/*.cpp engine/src/*.hpp)
add_library(engine_lib STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(engine_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/src/" PUBLIC SYSTEM ${B2D_INCS})
target_link_libraries(engine_lib maths_lib ecm_lib level_loader_lib sfml-graphics sfml-audio)


## Maths lib
add_library(maths_lib INTERFACE)
target_sources(maths_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/maths/maths.hpp")
target_include_directories(maths_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/maths" INTERFACE ${SFML_INCS})

## ECM lib
file(GLOB_RECURSE SOURCE_FILES engine/ecm/*.cpp engine/ecm/*.hpp)
add_library(ecm_lib STATIC ${SOURCE_FILES})
target_include_directories(ecm_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/ecm" )
target_link_libraries(ecm_lib PRIVATE maths_lib)

# Tile Loader
file(GLOB_RECURSE SOURCE_FILES engine/level_loader/*.cpp engine/level_loader/*.hpp)
add_library(level_loader_lib STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(level_loader_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/level_loader" )
target_link_libraries(level_loader_lib maths_lib sfml-graphics)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
file(GLOB_RECURSE CMPNTS src/components/*.cpp src/components/*.hpp)
file(GLOB_RECURSE SCENES src/scenes/*.cpp src/scenes/*.hpp)
add_executable(GrassGame ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
target_include_directories(GrassGame SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(GrassGame engine_lib)
set(EXECUTABLES ${EXECUTABLES} GrassGame)