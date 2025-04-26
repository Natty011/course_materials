#include <iostream> //std::ostream
#include <cstring> // strlen, strcpy
#include <cassert> // assert 
#include "simple_string.hpp"
#include "utils.hpp" // BAD_MEM

namespace ilrd
{
//member functions
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

size_t String::Length() const
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

//Globals functions - seif 11
std::ostream& operator<<(std::ostream& os_,const String& str_)
{
    return os_<<str_.Cstr();

}

bool operator==(const String& lhs_, const String& rhs_)
{
    return std::strcmp(lhs_.Cstr(), rhs_.Cstr()) == 0;
}

bool operator==(const String& lhs_, const char* rhs_)
{
    assert(rhs_);
    return std::strcmp(lhs_.Cstr(), rhs_) == 0;
}

bool operator==(const char* lhs_, const String& rhs_)
{
    assert(lhs_);
    return rhs_==lhs_; // need to check in the test!

}

bool operator<(const String& lhs_, const String& rhs_)
{
    return std::strcmp(lhs_.Cstr(), rhs_.Cstr()) < 0;
}

bool operator>(const String& lhs_, const String& rhs_)
{
    return rhs_ < lhs_; // need to check in the test!
}

//Globals functions - seif 12

bool operator<(const String& lhs_, const char* rhs_)
{
    assert(rhs_);
    return strcmp(lhs_.Cstr(), rhs_) < 0;
}
bool operator<(const char* lhs_, const String& rhs_)
{
    assert(lhs_);
    return strcmp(lhs_, rhs_.Cstr()) < 0;
}

bool operator>(const String& lhs_, const char* rhs_)
{
    return rhs_ < lhs_;
}
bool operator>(const char* lhs_, const String& rhs_)
{
    return rhs_ < lhs_;
}

}// namespace ilrd

