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


/*function declaration*/
void TestPrintHello();
/*function definition*/
/*Check PrintHello function using return pointer*/
/*of PrintHello function, and compars it to an expected string */
void TestPrintHello()
{
    int result = 0;
    char* p1;
    char *str2= {"\"Hello World!\""};
    assert(!p1);
    p1 =PrintHello();
    result = strcmp(p1, str2);
    if (result == 0)
    {
	puts("'PrintHello()' Function works great");
    }
    else
    {
	puts("'PrintHello()' Function failed");
    }
    free(p1);
    p1 = NULL;
    return;
}

int main()
{
    
	TestPrintHello();
	return 0;
}

