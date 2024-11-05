#include <stdio.h>

/*function declaration*/
void PrintHello();
/*function definition*/
void PrintHello()
{
int index = 0;
    char str[] = { 0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22};
    
 
    for( ; str[index] ; ++index)
    {
        printf("%c",str[index]);
    }
    printf("\n");
    return;
}
/*
int main()
{
    PrintHello();
    return 0;
}*/
