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

namespace feasy
{
    // define datatypes
    using i8 = signed char;
    using i16 = signed short;
    using i32 = signed int;
    using i64 = signed long long;
    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long long;
    using b8 = bool;
    using f32 = float;
    using f64 = double;

    class Logger;

}

// #include "core/logger.hpp"

// #define STATIC_ASSERT(condition) static_assert(condition, #condition)

// #define ASSERT(condition)                                                                                \
//     do                                                                                                   \
//     {                                                                                                    \
//         if (!(condition))                                                                                \
//         {                                                                                                \
//             logger::instance->log(LogLevel::ERROR, "Assertion failed: " #condition, __FILE__, __LINE__); \
//             std::terminate();                                                                            \
//         }                                                                                                \
//     } while (false)
