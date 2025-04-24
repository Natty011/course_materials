#ifndef __SIMPLE_STRING_HPP__ /*__SIMPLE_STRING_HPP__ */
#define __SIMPLE_STRING_HPP__ /*__SIMPLE_STRING_HPP__ */

#include <cstddef> /* size_t */

class String
{
    public:
    explicit String(const char* s_ = ""); //  Ctor
    String(const String& s_); //CCtor
    ~String(); //Dtor
    

}





#endif /* __SIMPLE_STRING_HPP__ */