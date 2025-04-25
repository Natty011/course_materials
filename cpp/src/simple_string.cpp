#include <cstring> // strlen, strcpy
#include <cassert> // assert 

#include "simple_string.hpp"
#include "utils.hpp" // BAD_MEM

namespace ilrd
{

// Ctor
String::String(const char* str_): m_str(AllocateNewString(str_))
{}

// Dtor
String::~String()
{
    delete[] m_str;
    DEBUG_ONLY(m_str= BAD_MEM(char));
}

//CCtor
String::String(const String& other_): m_str(AllocateNewString(other_.m_str))
{}

// Assignment operator
String& String::operator=(const String& other_)
{
    char* freshStr = AllocateNewString(other_.m_str);
    delete[] m_str;
    m_str = freshStr;

    return *this;
}


const String::Length() const
{
    return std::strlen(m_str);
}

const char* String::Cstr() const
{
    return m_str;
}

char* String::AllocateNewString(const char* input_)
{
    assert(input_);

    size_t size = std::strlen(input_) + 1;
    char* ret = new char[size];
    std::memcpy(ret, input_, size);

    return ret;
}

}// namespace ilrd
