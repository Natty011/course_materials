// File: inline_test.cpp
#include <iostream>

inline int Square(int x)
{
    return x * x;
}

int main()
{
    int x;
    std::cin >> x;
    int result = Square(x);
    return result;
}
