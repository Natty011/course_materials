#include <iostream>


#include <iostream>

class X
{
public:
    X(int a = 0) : m_a(a) {}

    // אופרטור השמה
    X& operator=(const X& other_)
    {
        std::cout << "[Assign] this: " << this 
                  << " | other_: " << &other_
                  << " | copying m_a: " << other_.m_a << std::endl;

        m_a = other_.m_a;

        return *this;
    }

    void Print(const char* name) const
    {
        std::cout << name << " (address: " << this << ", m_a: " << m_a << ")" << std::endl;
    }

private:
    int m_a;
};

int main()
{
    X x1(1), x2(2), x3(3);

    std::cout << "== Before assignment ==" << std::endl;
    x1.Print("x1");
    x2.Print("x2");
    x3.Print("x3");

    std::cout << "\n== Assignment: x1 = x2 = x3 ==" << std::endl;
    x1 = x2 = x3;

    std::cout << "\n== After assignment ==" << std::endl;
    x1.Print("x1");
    x2.Print("x2");
    x3.Print("x3");

    return 0;
}
