#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*function declaration*/
char* PrintHello();
/*function definition*/
/*- Converting hexa caracther to char and prints them */
/*- Return: allocation of a char pointer to "Hello World" string */
char* PrintHello()
{
    	int i =0;
	char hello_hex[15] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20,
	                      0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22, 0x00};
	char* strings;
	assert(!strings);
	strings = malloc(15*sizeof(char));
	if(strings == NULL)
	{
	    puts("Failed to allocate memory");
        exit(EXIT_FAILURE);
	}
	
	for (i =0; i < 15; ++i)
	 {
	     strings[i] = hello_hex[i];
	 }
	
	puts(hello_hex);
	return strings;
}

int main()
{

	char* p1;
	assert(!p1);
	p1 =PrintHello();
	free(p1);
	p1 = NULL;
	return 0;
}

