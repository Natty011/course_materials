#ifndef ILRD_HRD39_SIMPLE_STRING_ADVANCED_HPP // ILRD_HRD39_SIMPLE_STRING_ADVANCED_HPP
#define ILRD_HRD39_SIMPLE_STRING_ADVANCED_HPP // ILRD_HRD39_SIMPLE_STRING_ADVANCED_HPP

#include <iostream> //std::ostream
#include "simple_string.hpp" // ilrd::String

namespace ilrd
{

//seif 11
std::ostream& operator<<(std::ostream& os_,const String& str_);

bool operator==(const String& lhs_, const String& rhs_);
bool operator==(const String& lhs_, const char* rhs_);
bool operator==(const char* lhs_, const String& rhs_);

bool operator<(const String& lhs_, const String& rhs_);
bool operator>(const String& lhs_, const String& rhs_);

//seif 12
bool operator<(const String& lhs_, const char* rhs_);
bool operator<(const char* lhs_, const String& rhs_);

bool operator>(const String& lhs_, const char* rhs_);
bool operator>(const char* lhs_, const String& rhs_);

}// namespace ilrd

#endif // ILRD_HRD39_SIMPLE_STRING_ADVANCED_HPP
