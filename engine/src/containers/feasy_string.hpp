#pragma once

#include "feasy.hpp"

namespace feasy
{
    struct _StringImpl;

    class FEASY_API String
    {
    public:
        explicit String();
        String(const char *str);
        String(const String &other);
        String &operator=(const String &other);
        String(String &&other) noexcept;
        String &operator=(String &&other) noexcept;

        virtual ~String();

        const char *c_str() const;

        String &operator=(const char *str);
        String operator+(const String &other) const;
        String &operator+=(const String &other);

    private:
        _StringImpl *m_string;
    };
}