# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
APP_STL := c++_shared

APP_CPPFLAGS += -std=c++11
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -frtti

APP_ABI := armeabi-v7a arm64-v8a

APP_MODULES := Diamond
