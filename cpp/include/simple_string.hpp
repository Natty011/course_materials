#ifndef __SIMPLE_STRING_HPP__ /*__SIMPLE_STRING_HPP__ */
#define __SIMPLE_STRING_HPP__ /*__SIMPLE_STRING_HPP__ */

#include <cstddef> /* size_t */

class String
{
    public:
    explicit String(const char* str_ = ""); //  Ctor
    String(const String& other_); //CCtor
    ~String(); //Dtor
    String& operator=(const String& other_); // Assignment operator

}





#endif /* __SIMPLE_STRING_HPP__ */