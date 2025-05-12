

#include <iostream>
using namespace std;

int main()
{
	float* f = NULL;

	delete f;

	f = new float[15];

	delete[] f;

	return 0;
}