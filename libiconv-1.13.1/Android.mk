LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libiconv
LOCAL_MODULE_TAGS := eng

LOCAL_CFLAGS := \
	-Wno-multichar \
	-DANDROID \
	-DLIBDIR="c" \
	-DBUILDING_LIBICONV \
	-DIN_LIBRARY

LOCAL_SRC_FILES := \
	libcharset/lib/localcharset.c \
	lib/iconv.c \
	lib/relocatable.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/libcharset \
	$(LOCAL_PATH)/lib \
	$(LOCAL_PATH)/libcharset/include \
	$(LOCAL_PATH)/srclib

LOCAL_PRELINK_MODULE := false

ifneq ($(findstring MBB_FEATURE_EUAP, $(APP_DEFINE)),)
LOCAL_MODULE_PATH := $(TARGET_OUT_APPS_SHARED_LIBRARIES)
endif

include $(BUILD_SHARED_LIBRARY)

