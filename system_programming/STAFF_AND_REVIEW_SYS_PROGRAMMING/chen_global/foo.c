#include <stdio.h>
#include "foo.h"

int x = 10;

void PrintGlobalVariableAddress(void)
{
	printf("AddressOfExtern_x = %p\n", (void*)&x);
}
