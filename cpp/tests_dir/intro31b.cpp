#include <iostream>
#include <chrono>
#include "complex.hpp"

constexpr int ITERATIONS = 10000000;

using namespace nlrd;

void DummyByValue(Complex c) // העברה by value
{
    asm volatile("" : : "g"(c) : "memory");
}

void DummyByConstRef(const Complex& c) // העברה by const reference
{
    asm volatile("" : : "g"(c) : "memory");
}

int main()
{
    Complex z1(2.5, 3.5);

    // by value
    auto start_val = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        DummyByValue(z1); // call by value
    }
    auto end_val = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_val = end_val - start_val;
    std::cout << "By Value: " << dur_val.count() << " sec\n";

    // by const reference
    auto start_ref = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        DummyByConstRef(static_cast<const Complex&>(z1)); // call by const ref
    }
    auto end_ref = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_ref = end_ref - start_ref;
    std::cout << "By Const Ref: " << dur_ref.count() << " sec\n";

    return 0;
}
