
#include <dlfcn.h>
#include <iostream>
using namespace std;

int main()
{
	void(*FooNoArg)();
    void(*FooIntArg)(int);
    void(*FooCharArg)(char);

    void(*PrintIntC)(int);

    double(*FooDoubleChar)(char, double);
	void* handle = dlopen("./libcintro12.so", RTLD_LAZY);


	FooNoArg = (void(*)())dlsym(handle, "_Z3Foov");
	FooIntArg = (void(*)(int))dlsym(handle, "_Z3Fooi");
	FooCharArg = (void(*)(char))dlsym(handle, "_Z3Fooc");
	FooDoubleChar = (double(*)(char, double))dlsym(handle, "_Z4Fificd");

	FooDoubleChar('h', 9.1);
	FooIntArg(10);
	FooCharArg(30);
	FooNoArg();

	PrintIntC(666);

	dlclose(handle);

	return 0;
}