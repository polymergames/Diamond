# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
APP_STL := gnustl_shared

APP_CPPFLAGS += -std=c++11
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -frtti

APP_ABI := armeabi armeabi-v7a

APP_MODULES := Diamond