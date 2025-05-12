#include <stdio.h>
#include <dlfcn.h>

int main()
{
	void (*Foo)(void) = NULL;
	int (*Bar)(int) = NULL;
    int *g_ptr = NULL;

	void *handle = dlopen("./libcpp.so", RTLD_LAZY);

	if(!handle)
	{
		puts("dlopen failed");
		return 1;
	}

	Foo = dlsym(handle, "Foo");
	if(!Foo)
	{
		puts("Foo failed");
		return 1;
	}

	Foo();

	Bar = dlsym(handle, "Bar");
	if(!Bar)
	{
		puts("Bar failed");
		return 1;
	}

	printf("Bar return: %d\n", Bar(5));

	g_ptr = (int*)dlsym(handle, "g_var");
	if(!g_ptr)
	{
		puts("g_ptr failed");
		return 1;
	}
	
    printf("global_var: %d\n", *g_ptr);


    dlclose(handle);

	return 0;
}
