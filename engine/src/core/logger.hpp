#pragma once

#include "feasy.hpp"
#include <cstdio>

namespace feasy
{
    namespace log
    {
        void initialize()
        {
                }

        template <typename... Args>
        void fatal(const char *msg, ...) { printf(msg, std::forward<Args>(args)...); }
        template <typename... Args>
        void error(const char *msg, ...) { printf(msg, std::forward<Args>(args)...); }
        template <typename... Args>
        void warn(const char *msg, ...) { printf(msg, std::forward<Args>(args)...); }
        template <typename... Args>
        void info(const char *msg, ...) { printf(msg, std::forward<Args>(args)...); }
        template <typename... Args>
        void debug(const char *msg, ...) { printf(msg, std::forward<Args>(args)...); }
        template <typename... Args>
        void trace(const char *msg, ...) { printf(msg, std::forward<Args>(args)...); }
    }
}