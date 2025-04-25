#ifndef ILRD_HRD39_SIMPLE_STRING_HPP // ILRD_HRD39_SIMPLE_STRING_HPP 
#define ILRD_HRD39_SIMPLE_STRING_HPP // ILRD_HRD39_SIMPLE_STRING_HPP 

#include <cstddef> /* size_t */

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

} // namespace ilrd

#endif // ILRD_HRD39_SIMPLE_STRING_HPP 