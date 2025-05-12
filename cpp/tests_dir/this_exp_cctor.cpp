#include <iostream>

class X
{
public:
    X(int a = 0) : m_a(a)
    {
        std::cout << "[Ctor] this: " << this << " | m_a: " << m_a << std::endl;
    }

    // Copy Constructor
    X(const X& other_) : m_a(other_.m_a)
    {
        std::cout << "[CopyCtor] this: " << this 
                  << " | from: " << &other_ 
                  << " | copied m_a: " << m_a << std::endl;
    }

    // Assignment Operator
    X& operator=(const X& other_)
    {
        std::cout << "[Assign] this: " << this 
                  << " | from: " << &other_ 
                  << " | copied m_a: " << other_.m_a << std::endl;

        m_a = other_.m_a;
        return *this;
    }

    ~X()
    {
        std::cout << "[Dtor] this: " << this << " | m_a: " << m_a << std::endl;
    }

private:
    int m_a;
};

int main()
{
    std::cout << "== Create x1 ==" << std::endl;
    X x1(10);

    std::cout << "\n== Copy x1 into x2 (copy constructor) ==" << std::endl;
    X x2 = x1;  // Copy Constructor

    std::cout << "\n== Create x3 ==" << std::endl;
    X x3(30);

    std::cout << "\n== Assign x1 into x3 (assignment operator) ==" << std::endl;
    x3 = x1;    // Assignment Operator

    return 0;
}
