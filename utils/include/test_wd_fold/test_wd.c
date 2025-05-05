/* file: error_macro.c */
#include <stdio.h>
#include "utils.h"

int Check(int val)
{
    RETURN_IF_BAD(val > 0, -1, "Value too low");
    return 0;
}

int main(void)
{
    return Check(-5);
}

