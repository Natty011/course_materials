#include <iostream>
#include "libcpp.hpp"

using namespace std;

int g_var = 20;

void Foo(void)
{
    cout<<"Foo from c++\n";
}

int Bar(int x)
{
    static int s_local_var = 15;

    return x + g_var + s_local_var;
}