#ifndef ILRD_HRD39_SIMPLE_STRING_HPP // ILRD_HRD39_SIMPLE_STRING_HPP 
#define ILRD_HRD39_SIMPLE_STRING_HPP // ILRD_HRD39_SIMPLE_STRING_HPP 

#include <cstddef> /* size_t */
#include <iostream> // std::ostream

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
    static char* AllocateNewString(const char* input_);
};

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

} // namespace ilrd


#endif // ILRD_HRD39_SIMPLE_STRING_HPP 
