#pragma once

#include <openvr_driver.h>

#include <string>
#include "driver/Server.hpp"

#ifdef _WIN32
    #define DLL_EXPORT extern "C" __declspec( dllexport )
    #pragma message("DLL_EXPORT defined as __declspec(dllexport)")
#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)
    #define DLL_EXPORT extern "C" __attribute__((visibility("default")))
    #pragma message("DLL_EXPORT defined as __attribute__((visibility('default')))")
#endif

DLL_EXPORT void* HmdDriverFactory(const char *pInterfaceName, int *pReturnCode);
