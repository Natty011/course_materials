#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "foo.h"


/*int x = 10;*/
/* int argc, char* argv[], char* epnvp[] */
int main()
{
	void* handle1 = NULL, *handle2 = NULL;
	void (*go_1)(void);
	void (*go_2)(void);
		char *error;
	/* Open the shared library */
	handle1 = dlopen("./libfoo_dynamic.so", RTLD_LAZY);
    
    if (!handle1) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    
    /* Clear any existing error */
    dlerror();
    
 	/* Open the shared library */
	handle2 = dlopen("./libfoo_dynamic_2.so", RTLD_LAZY);
    
    if (!handle2) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    
    /* Clear any existing error */
    dlerror();   
    
    go_1 = dlsym(handle1, "Foo");
	if ((error = dlerror()) != NULL) 
	{
        fprintf(stderr, "%s\n", error);
        dlclose(handle1);
        exit(1);
    }
    
	go_1();
    
    go_2 = dlsym(handle2, "Foo2");
	if ((error = dlerror()) != NULL) 
	{
        fprintf(stderr, "%s\n", error);
        dlclose(handle2);
        exit(1);
    }
    
	go_2();
   
	PrintGlobalVariableAddress();
	
	/*Foo();
	Foo2();*/

	dlclose(handle1);
	dlclose(handle2);
  return 0;
}
/*
void PrintAddress( char* str , void* addr )
{
	printf("%s == %p\n" , str , addr );	
}
*/
