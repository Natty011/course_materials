#include <stdio.h>
#include "libcpp.hpp"

int main()
{
    Foo();
    printf("Bar return: %d\n", Bar(5));
    printf("global_var: %d\n", g_var);
    
    return 0;
}