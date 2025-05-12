
#include <stdio.h>
#include <iostream>

int main()
{
    bool b1 = true;
    bool b2;

    std::cout <<  "sizeof(bool) " <<sizeof(bool) << std::endl;

    
    for(int i = 0; i < 10; ++i)
    {
        printf("b2= %d\n", b2);
        /*std::cout << b1 << " " << b2 << std::endl;*/

        /*bool b3;

        printf("b3= %d\n", b3);*/


    }

    printf("b2 = %d\n", b2);
    printf("b1 = %d\n", b1);
    /*std::cout << b1 << " " << b2 << std::endl;*/

    /*int i = b1;
    i = 7;
    b2 = i;
    printf("%d", b2);*/

}

/*
bool b1 = true;
bool b2;
int i = b1;
i = 7;
b2 = i;
printf("%d", b2);


bool b1 = true;
bool b2;

int i = b1;
i = 7;
b2 = i;
printf("%d\n", b2);

*/

