
#include <stdio.h>

int Foo();


int main()
{
    int x = 4 ;
    Foo();
    printf("x = %d\n" , x);
    return 0; 

}


int Foo()
{
    int x = 3 ;
    return x;
}