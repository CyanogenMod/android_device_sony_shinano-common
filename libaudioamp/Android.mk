LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	liblog libutils libcutils libdl

LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_ADDITIONAL_DEPENDENCIES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_SRC_FILES := \
	tfa9890.cpp \
	audio_amplifier.cpp

LOCAL_MODULE := libaudioamp

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
