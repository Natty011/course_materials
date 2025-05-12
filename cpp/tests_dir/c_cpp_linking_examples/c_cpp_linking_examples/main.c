#include "libcpp.hpp"
#include <stdio.h>

int main()
{
    Foo();
    printf("Bar returned: %d\n", Bar(5));
    printf("global_var: %d\n", global_var);
    return 0;
}
