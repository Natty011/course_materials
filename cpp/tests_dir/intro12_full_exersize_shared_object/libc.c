#include <stdio.h>
#include "libc.h"

int g_counter = 20;

void Hello(void)
{
    puts("Hello from C!");
}

int Add(int a, int b)
{
    static int s = 15;

    return a + b + s;
}