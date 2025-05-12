#include "libc.h"

#include <iostream>

int main()
{
    Hello();

    std::cout<<"Add Result: "<< Add(2, 3) <<std::endl;
    std::cout<<"g_counter: "<< g_counter <<std::endl;
    return 0;
}
