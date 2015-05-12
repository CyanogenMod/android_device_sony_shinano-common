# Copyright (C) 2013 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# inherit from msm8974-common
$(call inherit-product, device/sony/msm8974-common/msm8974.mk)

COMMON_PATH := device/sony/shinano-common

DEVICE_PACKAGE_OVERLAYS += $(COMMON_PATH)/overlay

# Permissions
PRODUCT_COPY_FILES += \
    external/ant-wireless/antradio-library/com.dsi.ant.antradio_library.xml:system/etc/permissions/com.dsi.ant.antradio_library.xml \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepcounter.xml:system/etc/permissions/android.hardware.sensor.stepcounter.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepdetector.xml:system/etc/permissions/android.hardware.sensor.stepdetector.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml

# Init
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/rootdir/fstab.qcom:root/fstab.qcom \
    $(COMMON_PATH)/rootdir/init.qcom.rc:root/init.qcom.rc \
    $(COMMON_PATH)/rootdir/init.recovery.qcom.rc:root/init.recovery.qcom.rc \
    $(COMMON_PATH)/rootdir/ueventd.qcom.rc:root/ueventd.qcom.rc

# Recovery
PRODUCT_PACKAGES += \
    extract_elf_ramdisk

# Sbin
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/rootdir/sbin/tad_static:system/bin/tad_static

# ANT+
PRODUCT_PACKAGES += \
    AntHalService \
    com.dsi.ant.antradio_library \
    libantradio

# Audio
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/audio/audio_platform_info.xml:system/etc/audio_platform_info.xml

PRODUCT_PACKAGES += \
    tfa9890_amp

# Bluetooth
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/bluetooth/bt_vendor.conf:system/etc/bluetooth/bt_vendor.conf

# Filesystem management tools
PRODUCT_PACKAGES += \
    e2fsck

# GPS
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/gps/flp.conf:system/etc/flp.conf \
    $(COMMON_PATH)/gps/gps.conf:system/etc/gps.conf \
    $(COMMON_PATH)/gps/izat.conf:system/etc/izat.conf \
    $(COMMON_PATH)/gps/sap.conf:system/etc/sap.conf

PRODUCT_PACKAGES += \
    com.qualcomm.location \
    gps.msm8974

# IPC Security Config
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/rootdir/system/etc/sec_config:system/etc/sec_config

# Keystore
PRODUCT_PACKAGES += \
    keystore.msm8974

# Keylayout
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/rootdir/system/usr/keylayout/gpio-keys.kl:system/usr/keylayout/gpio-keys.kl \
    $(COMMON_PATH)/rootdir/system/usr/keylayout/mhl-rcp.kl:system/usr/keylayout/mhl-rcp.kl \
    $(COMMON_PATH)/rootdir/system/usr/keylayout/msm8974-taiko-mtp-snd-card_Button_Jack.kl:system/usr/keylayout/msm8974-taiko-mtp-snd-card_Button_Jack.kl

# NFC
PRODUCT_PACKAGES += \
    NfcNci \
    Tag \
    com.android.nfc_extras \
    nfc_nci.pn54x.default

PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/rootdir/system/etc/nfcee_access.xml:system/etc/nfcee_access.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:system/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/native/data/etc/com.android.nfc_extras.xml:system/etc/permissions/com.android.nfc_extras.xml

# Off mode charger
PRODUCT_PACKAGES += \
    charger_res_images

# USB
PRODUCT_PACKAGES += \
    com.android.future.usb.accessory

# Set default USB interface
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    persist.sys.usb.config=mtp

# Audio offload
PRODUCT_PROPERTY_OVERRIDES += \
    audio.offload.buffer.size.kb=32 \
    audio.offload.gapless.enabled=false \
    audio.offload.multiple.enabled=false \
    audio.offload.pcm.enable=enable \
    av.offload.enable=enable \
    av.streaming.offload.enable=enable

# Enable AAC 5.1 output
PRODUCT_PROPERTY_OVERRIDES += \
    media.aac_51_output_enabled=true

# Voice Call
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qc.sdk.audio.fluencetype=none \
    persist.audio.dualmic.config=endfire \
    persist.audio.fluence.voicecall=true \
    persist.audio.fluence.voicerec=false \
    persist.audio.fluence.speaker=true

# aDSP
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qualcomm.sensors.qmd=false \
    debug.qualcomm.sns.hal=w \
    ro.qc.sdk.sensors.gestures=false \
    ro.qc.sensors.max_accel_rate=false \
    ro.qc.sensors.max_gyro_rate=false \
    ro.qc.sensors.max_mag_rate=false \
    ro.qc.sensors.smgr_mag_cal_en=true \
    ro.qualcomm.sensors.pedometer=false \
    ro.qualcomm.sensors.pam=false \
    ro.qualcomm.sensors.scrn_ortn=false \
    ro.qualcomm.sensors.smd=sony \
    ro.qc.sensors.step_detector=true \
    ro.qc.sensors.step_counter=true \
    ro.qualcomm.sensors.georv=true \
    ro.qc.sensors.max_geomag_rotvec=50

# GPS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.gps.qc_nlp_in_use=0 \
    ro.gps.agps_provider=1 \
    ro.qc.sdk.izat.premium_enabled=1 \
    ro.qc.sdk.izat.service_mask=0x0

# HDMI
PRODUCT_PROPERTY_OVERRIDES += \
    persist.demo.hdmirotationlock=false

# Time
PRODUCT_PROPERTY_OVERRIDES += \
    persist.timed.enable=true

# Touchscreen
PRODUCT_PROPERTY_OVERRIDES += \
    ro.input.noresample=1

# WFD
PRODUCT_PROPERTY_OVERRIDES += \
    persist.debug.wfd.enable=1 \
    persist.sys.wfd.virtual=0

# BCM Wifi
$(call inherit-product-if-exists, hardware/broadcom/wlan/bcmdhd/config/config-bcm.mk)

# HWUI memory limits
$(call inherit-product, frameworks/native/build/phone-xxhdpi-2048-hwui-memory.mk)

# Include non-opensource parts
$(call inherit-product, vendor/sony/shinano-common/shinano-common-vendor.mk)
