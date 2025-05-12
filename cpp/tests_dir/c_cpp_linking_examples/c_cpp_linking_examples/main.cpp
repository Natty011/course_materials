extern "C" {
    #include "libc.h"
}
#include <iostream>

int main()
{
    Hello();
    std::cout << "Add result: " << Add(3, 4) << std::endl;
    std::cout << "Counter: " << g_counter << std::endl;
    return 0;
}
