#include "libcpp.hpp"
#include <iostream>

int global_var = 100;

void Foo(void)
{
    std::cout << "Foo from C++" << std::endl;
}

int Bar(int x)
{
    static int static_local_var = 0;
    return x + global_var + static_local_var++;
}
