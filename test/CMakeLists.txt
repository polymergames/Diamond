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

# Header includes
include_directories(
        ../include
        ../include/backend
        googletest/include
)

# Libraries
if(WIN32)
    set(LINK_LIBS gtest.lib Diamond)
    link_directories(googletest/lib/x86)
else()
    set(LINK_LIBS libgtest.a Diamond -stdlib=libc++)
    link_directories(googletest/lib)
endif()


# Get source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Build tests
add_executable(testDiamond ${SOURCES})
target_link_libraries(testDiamond ${LINK_LIBS})
install(TARGETS testDiamond DESTINATION bin)