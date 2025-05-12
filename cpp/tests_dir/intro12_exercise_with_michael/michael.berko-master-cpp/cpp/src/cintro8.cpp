#include <iostream>
#include <stdlib.h>
using namespace std;


void foo(int z, int i = 3, float f = 4)
{
	float mult = i*f;
	cout << mult << endl;
}

int main()
{

	cout << "default mult: " << endl;
	foo(1);
	cout << "non-default mult: " << endl;	
	foo(1, 15, 0.5);
	return 0;
}