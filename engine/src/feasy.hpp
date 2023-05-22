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

    // template <typename T>
    // using Ref = std::shared_ptr<T>;
    // template <typename T, typename... Args>
    // __forceinline std::shared_ptr<T> createRef(Args &&...args)
    // {
    //     return std::make_shared<T>(std::forward<Args>(args)...);
    // }
}