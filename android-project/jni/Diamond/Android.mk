#
#	Copyright 2015 Ahnaf Siddiqui
#
#	Licensed under the Apache License, Version 2.0 (the "License");
#	you may not use this file except in compliance with the License.
#	You may obtain a copy of the License at
#
#	http://www.apache.org/licenses/LICENSE-2.0
#
#	Unless required by applicable law or agreed to in writing, software
#	distributed under the License is distributed on an "AS IS" BASIS,
#	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#	See the License for the specific language governing permissions and
#	limitations under the License.
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Diamond

FILE_SRC_LIST := $(wildcard $(LOCAL_PATH)/src/audio/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/game/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/graphics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/input/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/physics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/util/*.cpp)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include \
	$(LOCAL_PATH)/../../../include/backend \
	$(LOCAL_PATH)/../../../extern/DiamondUtils/include \
	$(LOCAL_PATH)/../../../extern/Quantum2D/include \
	$(LOCAL_PATH)/../../../extern/SDL2_ttf/include \
	$(LOCAL_PATH)/../../../extern/SDL2_image/include \
	$(LOCAL_PATH)/../../../extern/SDL2_mixer/include \
	$(LOCAL_PATH)/../../../extern/SDL2/include

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/../../../src/audio/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/game/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/graphics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/input/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/physics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/util/*.cpp))

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

LOCAL_STATIC_LIBRARIES := Quantum2D

# rtti to enable RunTime Type Information (ex. for Entity.getComponent<T>())
LOCAL_CPP_FEATURES := rtti

include $(BUILD_STATIC_LIBRARY)
