#include <iostream>
#include <typeinfo>

template<typename T>
void foo(T t)
{
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}

template<>
void foo<int>(int t)
{
	std::cout << t << " template Specialized foo (for int param)\n";

}
/*
void foo(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}
*/


int main()
{
    foo(4.2); // call with double
	// thare is no regulal function just templates functions(general + specilized)
    foo(5); // call with Specialized int ( implicit)
    foo<int>(5); // explicit call to template function with int

    return 0;
}
