#include <iostream> // std::cin, std::cout 
#include "simple_string.hpp" // ilrd::String

using ilrd::String;

void Foo(String s_)
{
    std::cout << "In Foo:: s_Cstr():" << s_.Cstr() << "\n";
}

String Bla()
{
    return String("efg");
}

int main()
{

    Foo(String("abc"));
    String tmp = Bla();
    std::cout << "tmp.Cstr(): " << tmp.Cstr() << "\n";

    String str1("Ctor_s1");
    String str2(str1); //   CCtor
    String str3("Ctor_s3");

    std::cout <<"str1: " << str1.Cstr() <<"\n";
    std::cout <<"str2: " << str2.Cstr() <<"\n";
    std::cout <<"str3: " << str3.Cstr() <<"\n";

    str2 = str3;
    std::cout << "After assignment (str2=str3): " << str2.Cstr() <<"\n";

    str3 = str3;
    std::cout << "self assignment (str3=str3): " << str3.Cstr() <<"\n";


    return 0;
}