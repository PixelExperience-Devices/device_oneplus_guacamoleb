/*
   Copyright (c) 2015, The Linux Foundation. All rights reserved.
   Copyright (C) 2016 The CyanogenMod Project.
   Copyright (C) 2019 The LineageOS Project.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fstream>
#include <unistd.h>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::base::SetProperty;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;
    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}
void property_override_dual(char const system_prop[],
    char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{
    property_override_dual("ro.build.type", "ro.vendor.build.type", "user");
    property_override("ro.boot.verifiedbootstate", "green");

    int prj_version = stoi(android::base::GetProperty("ro.boot.prj_version", ""));
    int rf_version = stoi(android::base::GetProperty("ro.boot.rf_version", ""));
    switch (rf_version){
      case 1:
        /* China*/
        property_override_dual("ro.product.model", "ro.product.vendor.model", "GM1900");
        property_override("ro.rf_version", "TDD_FDD_Ch_All");
        break;
      case 3:
        /* India*/
        property_override_dual("ro.product.model", "ro.product.vendor.model", "GM1901");
        property_override("ro.rf_version", "TDD_FDD_In_All");
        break;
      case 4:
        /* Europe */
        property_override_dual("ro.product.model", "ro.product.vendor.model", "GM1903");
        property_override("ro.rf_version", "TDD_FDD_Eu_All");
        break;
      case 5:
        /* Global / US Unlocked */
        property_override_dual("ro.product.model", "ro.product.vendor.model", "GM1907");
        property_override("ro.rf_version", "TDD_FDD_Am_All");
        break;
      default:
        /* Generic */
        property_override_dual("ro.product.model", "ro.product.vendor.model", "GM1907");
        property_override("ro.rf_version", "TDD_FDD_Am_All");
        break;
    }

    property_override("vendor.boot.prj_version", std::to_string(prj_version).c_str());
    property_override_dual("vendor.rf.version", "vendor.boot.rf_version", std::to_string(rf_version).c_str());
}
