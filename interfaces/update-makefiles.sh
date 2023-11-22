#!/bin/bash

source $ANDROID_BUILD_TOP/system/tools/hidl/update-makefiles-helper.sh

do_makefiles_update \
  "vendor.goodix:device/oneplus/guacamoleb/interfaces/goodix"

do_makefiles_update \
  "vendor.oneplus:device/oneplus/guacamoleb/interfaces/oneplus"
