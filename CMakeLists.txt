#
# Copyright 2016 Ahnaf Siddiqui
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.2.0)
project(Diamond)


# Flags
set(CMAKE_CXX_FLAGS -std=c++11)


# Header includes
include_directories(
	include
	include/backend
	extern/DiamondUtils/include
	extern/Quantum2D/include
	extern/SDL2/include
	extern/SDL2_image/include
	extern/SDL2_mixer/include
)


# Libraries
if(APPLE)
	find_library(SDL_2 SDL2)
	find_library(SDL_2_IMAGE SDL2_image)
	find_library(SDL_2_MIXER SDL2_mixer)
	set(LINK_LIBS libQuantum2D.a ${SDL_2} ${SDL_2_IMAGE} ${SDL_2_MIXER} -stdlib=libc++)
	link_directories(extern/Quantum2D/lib)
else()
	# Windows
	# TODO: linux!
	set(LINK_LIBS Quantum2D.lib SDL2.lib SDL2_image.lib SDL2_mixer.lib)
	if(CMAKE_VS_PLATFORM_NAME STREQUAL x64)
		link_directories(extern/Quantum2D/lib/x64 extern/SDL2/lib/x64 extern/SDL2_image/lib/x64 extern/SDL2_mixer/lib/x64)
	else()
		link_directories(extern/Quantum2D/lib/x86 extern/SDL2/lib/x86 extern/SDL2_image/lib/x86 extern/SDL2_mixer/lib/x86)
	endif()
endif()


# Get source files
file(GLOB_RECURSE SOURCES src/*.cpp)


# Build Diamond library
add_library(Diamond STATIC ${SOURCES})
target_link_libraries(Diamond ${LINK_LIBS})
install(TARGETS Diamond DESTINATION lib)


# Build subdirectories
add_subdirectory(demo)
# TODO: rebuild the gtest library with clang, then this will work on mac
# add_subdirectory(test)
