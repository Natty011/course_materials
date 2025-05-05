#include <stdio.h>
#include <stdlib.h>
#include "foo.h"

/*int x = 10;*/
/* int argc, char* argv[], char* epnvp[] */
int main()
{

	PrintGlobalVariableAddress(  );
	
	Foo();
	
	Foo2();

  return 0;
}
/*
void PrintAddress( char* str , void* addr )
{
	printf("%s == %p\n" , str , addr );	
}
*/
