

cmake_minimum_required(VERSION 3.7)
# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

project(SDLStructured)
include_directories(src)

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
	message(FATAL_ERROR "zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(${ZLIB_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 library not found")
endif(NOT SDL2_FOUND)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
if(NOT SDL2_IMAGE_FOUND)
	message(FATAL_ERROR "SDL2_image library not found")
endif(NOT SDL2_IMAGE_FOUND)
include_directories(${SDL_IMAGE_INCLUDE_DIRS})

find_package(SDL2_mixer REQUIRED)
if(NOT SDL_MIXER_FOUND)
	message(FATAL_ERROR "SDL2_mixer library not found")
endif(NOT SDL_MIXER_FOUND)
include_directories(${SDL_MIXER_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)

if(NOT SDL2_TTF_FOUND)
	message(FATAL_ERROR "SDL2_ttf library not found")
endif(NOT SDL2_TTF_FOUND)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES  src/*.cpp)

add_executable(SDLStructured main.cpp ${SOURCES})

target_link_libraries(
  SDLStructured
  ${ZLIB_LIBRARIES}
  ${SDL2_LIBRARY}
  ${SDL2_MIXER_LIBRARIES}
  ${SDL2_IMAGE_LIBRARY}
  ${SDL2_TTF_LIBRARIES}
  )

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

# Define output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDLTest_TARGET_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDLTest_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDLTest_LIB_DIR})