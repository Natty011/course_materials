#include <cstring> /* strlen, strcpy*/
#include <cassert> /* assert */
#include "simple_string.hpp"

//  Ctor
String::String(const char* str_ = "")
{
    assert(str_);

    char* temp = new char[strlen(str_) + 1];
    strcpy(temp, str_);
    m_str = temp;

}






/*
String s1("hello");
*/



/*

class String
{
    public:

        explicit String(const char* str_ = ""); //  Ctor
        String(const String& other_); //CCtor
        ~String(); //Dtor
        String& operator=(const String& other_); // Assignment operator

        size_t Length() const; // return the length of the string
        const char* Cstr() const; // return the pointer to the string

    private:

    char *m_str;
}



*/