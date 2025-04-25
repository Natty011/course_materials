#include <iostream> // std::cin, std::cout 
#include "simple_string.hpp"


using ilrd::String;

void Foo(String s_)
{
    std::cout << "In Foo:: s_Cstr() =" << s_.Cstr() << "\n";
}

String Bla()
{
    return "efg";
}

int main()
{
    Foo("abc");
    String tmp = Bla();
    std::cout << tmp.Cstr() << "\n";

    return 0;
}