#include "feasy_string.hpp"

using namespace feasy;

#include <cstring>

String::String()
    : m_data(nullptr), m_length(0)
{
}

String::String(const char *str)
    : m_data(nullptr), m_length(0)
{
    if (str)
    {
        m_length = strlen(str);
        m_data = new char[m_length + 1];
        strcpy(m_data, str);
    }
}

String::String(const String &other)
    : m_data(nullptr), m_length(other.m_length)
{
    if (other.m_data)
    {
        m_data = new char[m_length + 1];
        strcpy(m_data, other.m_data);
    }
}

String &String::operator=(const String &other)
{
    if (this != &other)
    {
        delete[] m_data;
        m_length = other.m_length;
        if (other.m_data)
        {
            m_data = new char[m_length + 1];
            strcpy(m_data, other.m_data);
        }
        else
        {
            m_data = nullptr;
        }
    }
    return *this;
}

String::String(String &&other) noexcept
    : m_data(other.m_data), m_length(other.m_length)
{
    other.m_data = nullptr;
    other.m_length = 0;
}

String &String::operator=(String &&other) noexcept
{
    if (this != &other)
    {
        delete[] m_data;
        m_data = other.m_data;
        m_length = other.m_length;
        other.m_data = nullptr;
        other.m_length = 0;
    }
    return *this;
}

String::~String()
{
    delete[] m_data;
}

const char *String::c_str() const
{
    return m_data;
}

String &String::operator=(const char *str)
{
    delete[] m_data;
    if (str)
    {
        m_length = strlen(str);
        m_data = new char[m_length + 1];
        strcpy(m_data, str);
    }
    else
    {
        m_data = nullptr;
        m_length = 0;
    }
    return *this;
}

String String::operator+(const String &other) const
{
    size_t newLength = m_length + other.m_length;
    char *newData = new char[newLength + 1];

    if (m_data)
    {
        strcpy(newData, m_data);
    }
    if (other.m_data)
    {
        strcat(newData, other.m_data);
    }

    String result(newData);
    delete[] newData;
    return result;
}

String &String::operator+=(const String &other)
{
    size_t newLength = m_length + other.m_length;
    char *newData = new char[newLength + 1];

    if (m_data)
    {
        strcpy(newData, m_data);
    }
    if (other.m_data)
    {
        strcat(newData, other.m_data);
    }

    delete[] m_data;
    m_data = newData;
    m_length = newLength;
    return *this;
}
