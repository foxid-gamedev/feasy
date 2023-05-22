#include "feasy_string.hpp"

#include <string>

using namespace feasy;

struct feasy::_StringImpl
{
    std::string str;
};

feasy::String::String()
{
    m_string = new _StringImpl{};
}

feasy::String::String(const char *str)
{
    m_string = new _StringImpl{str};
}

feasy::String::String(const String &other)
{
    m_string = new _StringImpl{other.m_string->str};
}

String &feasy::String::operator=(const String &other)
{
    m_string = new _StringImpl{other.m_string->str};
    return *this;
}

feasy::String::String(String &&other) noexcept
{
    m_string = new _StringImpl{other.m_string->str};
    delete other.m_string;
    other.m_string = nullptr;
}

String &feasy::String::operator=(String &&other) noexcept
{
    if (this != &other)
    {
        delete m_string;
        m_string = other.m_string;
        other.m_string = nullptr;
    }

    return *this;
}

feasy::String::~String()
{
    delete m_string;
    m_string = nullptr;
}

const char *feasy::String::c_str() const
{
    return m_string->str.c_str();
}

String feasy::String::operator+(const String &other) const
{
    String result(*this);
    result += other;
    return result;
}

String &feasy::String::operator+=(const String &other)
{
    m_string->str += other.m_string->str;
    return *this;
}