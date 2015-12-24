#
# Copyright 2015 Ahnaf Siddiqui
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
	include/backend
	include/modules
	extern/DiamondUtils/include
	extern/Quantum2D/include
	extern/SDL2-2.0.3/include
	extern/SDL2_image-2.0.0/include
	extern/SDL2_mixer-2.0.0/include
)


# Libraries
if(APPLE)
	find_library(SDL_2 SDL2)
	find_library(SDL_2_IMAGE SDL2_image)
	find_library(SDL_2_MIXER SDL2_mixer)
	set(LINK_LIBS libQuantum2D.a ${SDL_2} ${SDL_2_IMAGE} ${SDL_2_MIXER})
else()
	# TODO: windows and linux sdl libs
	set(LINK_LIBS libQuantum2D.a)
endif()

link_directories(extern/Quantum2D/lib)


# Get source files
file(GLOB_RECURSE SOURCES src/*.cpp)


# Build Diamond library
add_library(Diamond SHARED ${SOURCES})
target_link_libraries(Diamond ${LINK_LIBS})
install(TARGETS Diamond DESTINATION lib)


# Build subdirectories
add_subdirectory(demo)