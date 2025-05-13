#include <iostream>

class X
{
public:
    X() { std::cout << "Default ctor\n"; }
    X(const X&) { std::cout << "Copy ctor\n"; }
    X(X&&) noexcept { std::cout << "Move ctor\n"; }
    ~X() { std::cout << "Dtor\n"; }
};

X MakeX()
{
    X x;
    return x; // <- כאן נראה אם יש NRVO או העתקה
}

X MakeXTemporary()
{
    return X(); // <- כאן RVO מתבצע בקלות
}

int main()
{
    std::cout << "--- NRVO Test ---\n";
    X x1 = MakeX();

    std::cout << "\n--- RVO Test ---\n";
    X x2 = MakeXTemporary();

    return 0;
}
