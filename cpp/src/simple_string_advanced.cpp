#include <iostream> //std::ostream
#include <cstring> // std::strcmp
#include <cassert> //assert

#include "simple_string_advanced.hpp"


namespace ilrd
{

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
