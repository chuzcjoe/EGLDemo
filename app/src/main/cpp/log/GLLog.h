//
// Created by ByteDance on 3/2/24.
//

#pragma once
#include <android/log.h>

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG, "NATIVELOG", FORMAT, ##__VA_ARGS__)
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "NATIVELOG", FORMAT, ##__VA_ARGS__)
