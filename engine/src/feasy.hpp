#pragma once

#ifdef FEASY_EXPORT
#ifdef _MSC_VER
#define FEASY_API __declspec(dllexport)
#else
#define FEASY_API __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
#define FEASY_API __declspec(dllimport)
#else
#define FEASY_API
#endif
#endif

namespace feasy {
    FEASY_API void foo(int number);
}