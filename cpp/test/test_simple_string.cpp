#include <iostream> // std::cin, std::cout 
#include "simple_string.hpp" // ilrd::String


#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"


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
    std::cout << "tmp.Length(): " << tmp.Length() << "\n\n";

    String str1("Ctor_s1");
    String str2(str1); //   CCtor
    String str3("Ctor_s3");

    std::cout <<"str1.Cstr(): " << str1.Cstr() <<"\n" 
              <<"Address of str1.Cstr(): \n" 
              << static_cast<const void*>(str1.Cstr()) <<"\n\n";

    std::cout <<"After CCtor of str2(str1): " << str2.Cstr() <<"\n" 
                <<"Address of str2.Cstr(): \n"<<GREEN 
                << static_cast<const void*>(str2.Cstr()) <<"\n\n"<<RESET;

    std::cout <<"str3.Cstr(): " << str3.Cstr() <<"\n"
                <<"Address of str3.Cstr(): \n" 
                << static_cast<const void*>(str3.Cstr()) <<"\n\n";

    str2 = str3;
    std::cout << "After assignment (str2=str3): " << str2.Cstr() <<"\n"
              <<"Address of str2.Cstr(): \n"<<YELLOW 
              << static_cast<const void*>(str2.Cstr()) <<"\n\n"<<RESET;

    str3 = str3;
    std::cout << "self assignment (str3=str3): " << str3.Cstr() <<"\n"
              <<"Address of str3.Cstr(): \n" 
              << static_cast<const void*>(str3.Cstr()) <<"\n\n";

    //str3.~String();

    //seif 11+12 in exersize 27

    const char* s11 = "hello";
    const char* s22 = "hi";
    const char* s33 = "hello";

    String s1(s11);
    String s2(s22);
    String s3("hello");

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;

    std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
    std::cout << "s1 == s2: " << (s1 == s2) << std::endl;

    std::cout << "s1 == s11: " << (s1 == s11) << std::endl;
    std::cout << "s11 == s1: " << (s11 == s1) << std::endl;

    std::cout << "s1 < s2: " << (s1 < s2) << std::endl;
    std::cout << "s1 > s2: " << (s1 > s2) << std::endl;

    return 0;
}

