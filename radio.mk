# LTE, GSM/WCDMA
PRODUCT_PROPERTY_OVERRIDES += \
    ro.telephony.default_network=9 \
    telephony.lteOnCdmaDevice=0 \
    persist.radio.apm_sim_not_pwdn=1 \
    persist.radio.add_power_save=1 \
    persist.radio.dont_use_dsd=false \
    persist.radio.eons.enabled=false \
    persist.radio.oem_socket=false

# Ril sends only one RIL_UNSOL_CALL_RING, so set call_ring.multiple to false
PRODUCT_PROPERTY_OVERRIDES += \
    ro.telephony.call_ring.multiple=0

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    rild.libpath=/system/vendor/lib/libril-qc-qmi-1.so
