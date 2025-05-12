#include <stdio.h>

const int i = 3;

int main()
{
    /*const int i = 3;*/
    int *ip = (int*)&i;
    *ip = 5;
    /*int arr[i];*/

    printf("%d  ---c compile---- %d\n", i, *ip);
    return 0;
}
