#include "libc.h"
#include <stdio.h>

int g_counter = 0;

void Hello(void)
{
    puts("Hello from C!");
}

int Add(int a, int b)
{
    static int s = 0;
    ++g_counter;
    return a + b + s++;
}
