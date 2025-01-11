#pragma once

#ifdef AYR_BUILD_DLL
    #define AYR_API __declspec(dllexport)
#else
    #define AYR_API __declspec(dllimport)
#endif