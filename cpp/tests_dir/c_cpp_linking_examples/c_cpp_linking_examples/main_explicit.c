#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *handle = dlopen("./libcpp.so", RTLD_LAZY);
    if (!handle) { puts("dlopen failed"); return 1; }

    void (*Foo)(void) = dlsym(handle, "Foo");
    int (*Bar)(int) = dlsym(handle, "Bar");

    Foo();
    printf("Bar(5): %d\n", Bar(5));

    dlclose(handle);
    return 0;
}
