
#include <stdio.h>
#include <iostream>

enum E {AA, BB, CC, DD}; /*typedef */
enum E2 {TT, KK};
/*
enum E {AA, BB, CC, DD};
enum E2 {TT, KK};
enum E e = 2;
enum E2 e2 = AA;   ✘ שגיאה ב־C++
++e;
int i = e; */


int main()
{
     E a = E(10); 
     /*enum E e = 2;*/
     E ee;
     E ff;

     int temp = 5;
     std::cout <<  "(float)temp= " <<(float)temp << std::endl;
     printf("(float)temp=%f\n", (float)temp);


     std::cout <<  "(a)= " <<a << std::endl;
     std::cout <<  "sizeof(E) " <<sizeof(E) << std::endl;
     std::cout <<  "(ee)= " <<ee << std::endl;
     std::cout <<  "ff =" <<ff << std::endl;

    printf("e=%d\n", a);

    std::cout<<"a="<<a<<std::endl;

    /*std::cout<<i<<std::endl;*/


     /*printf("%d = d\n", i);*/

/*
    enum E2 e2 = E2(AA); 
    int i = e;
   */ 
    /*enum E2 e2 = AA;*/ // ✘ שגיאה ב־C++ 

   /* E2 e22 = KK;*/
    /*++e;*/
   /* ++i;*/

  

    return 0;
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

int main()
{
    bool b1 = true;
    bool b2;
    std::cout << b1 << " " << b2 << std::endl;
}
*/
