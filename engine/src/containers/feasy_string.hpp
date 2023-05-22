#pragma once

#include "feasy.hpp"

namespace feasy
{
    // TODO: revent string wrapper to necessary needs
    // atm: wrapping the std::string with some basic overloadings
    class FEASY_API String
    {
    public:
        String();
        String(const char *str);
        String(const String &other);
        String &operator=(const String &other);
        String(String &&other) noexcept;
        String &operator=(String &&other) noexcept;
        ~String();

        const char *c_str() const;

        String &operator=(const char *str);
        String operator+(const String &other) const;
        String &operator+=(const String &other);

    private:
        char *m_data;
        i64 m_length;
    };
}