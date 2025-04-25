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

char* String::AllocateNewString(const char* input_)
{
    assert(input_);

    size_t size = std::strlen(input_) + 1;
    char* ret = new char[size];
    std::memcpy(ret, input_, size);

    return ret;
}

}// namespace ilrd





/*
String s1("hello");
*/



/*

namespace ilrd
{

class String
{
public:

    explicit String(const char* str_); //  Ctor
    String(const String& other_); //CCtor
    String& operator=(const String& other_); // Assignment operator
    ~String(); //Dtor

    size_t Length() const; // return the length of the string
    const char* Cstr() const; // return the pointer to the string

private:
    char *m_str;
    static char* AllocateNewString(const char* str_);
};



*/