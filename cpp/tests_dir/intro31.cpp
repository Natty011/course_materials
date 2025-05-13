#include <iostream>
#include <chrono>

class Complex
{
public:
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) {}

    // by value
    friend Complex AddByValue(Complex lhs, Complex rhs)
    {
        return Complex(lhs.m_real + rhs.m_real, lhs.m_imag + rhs.m_imag);
    }

    // by const ref
    friend Complex AddByRef(const Complex& lhs, const Complex& rhs)
    {
        return Complex(lhs.m_real + rhs.m_real, lhs.m_imag + rhs.m_imag);
    }

private:
    double m_real;
    double m_imag;
};

int main()
{
    Complex a(1.1, 2.2), b(3.3, 4.4), c;

    constexpr int ITERATIONS = 10000000;

    // --- by value ---
    auto start_val = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ITERATIONS; ++i)
    {
        c = AddByValue(a, b);
    }

    auto end_val = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_val = end_val - start_val;

    std::cout << "By Value: " << duration_val.count() << " sec\n";

    // --- by const ref ---
    auto start_ref = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ITERATIONS; ++i)
    {
        c = AddByRef(a, b);
    }

    auto end_ref = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_ref = end_ref - start_ref;

    std::cout << "By Const Reference: " << duration_ref.count() << " sec\n";

    return 0;
}
