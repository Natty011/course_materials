#include <iostream>
#include <dlfcn.h>

int main()
{
    void *handle = dlopen("./libc.so", RTLD_LAZY);
    if (!handle) { std::cerr << "Error"; return 1; }

    typedef void (*hello_t)(void);
    typedef int (*add_t)(int, int);

    hello_t Hello = (hello_t)dlsym(handle, "Hello");
    add_t Add = (add_t)dlsym(handle, "Add");

    Hello();
    std::cout << "Add: " << Add(1, 2) << std::endl;
    dlclose(handle);
    return 0;
}
