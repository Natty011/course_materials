#include <iostream>
#include <stdlib.h>
using namespace std;




int main()
{

	int *ptr1 = NULL;

	free(ptr1);
	int* ptr = (int*)malloc(1000*sizeof(int));
	delete ptr;

	
	int* ptr2 = new int[1000];
	free(ptr);
	
	return 0;
}