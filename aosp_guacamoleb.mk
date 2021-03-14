#
# Copyright (C) 2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from guacamoleb device
$(call inherit-product, device/oneplus/guacamoleb/device.mk)

# Inherit some common PE stuff.
$(call inherit-product, vendor/aosp/config/common_full_phone.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := aosp_guacamoleb
PRODUCT_DEVICE := guacamoleb
PRODUCT_BRAND := OnePlus
PRODUCT_MODEL := OnePlus 7
PRODUCT_MANUFACTURER := OnePlus

PRODUCT_AAPT_CONFIG := xxhdpi
PRODUCT_AAPT_PREF_CONFIG := xxhdpi
PRODUCT_CHARACTERISTICS := nosdcard

# Boot animation
TARGET_SCREEN_HEIGHT := 2340
TARGET_SCREEN_WIDTH := 1080
TARGET_GAPPS_ARCH := arm64
TARGET_BOOT_ANIMATION_RES := 1080
TARGET_USES_CUSTOM_AVB_KEY := true

# Wifi
TARGET_INCLUDE_WIFI_EXT := true

#ARCore
TARGET_INCLUDE_STOCK_ARCORE := true

#Recorder
TARGET_SUPPORTS_GOOGLE_RECORDER := true

BUILD_FINGERPRINT := OnePlus/OnePlus7/OnePlus7:11/RKQ1.201022.002/2101121150:user/release-keys
PRODUCT_BUILD_PROP_OVERRIDES += \
    TARGET_DEVICE=guacamoleb \
    PRODUCT_NAME=guacamoleb \
    PRIVATE_BUILD_DESC="OnePlus7-user 11 RKQ1.201022.002 2101121150 release-keys"

PRODUCT_GMS_CLIENTID_BASE := android-oneplus

