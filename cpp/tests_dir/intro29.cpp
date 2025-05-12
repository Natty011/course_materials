#include <iostream>

class X
{
public:
	explicit X();
	/*explicit*/  X(int a_);
	explicit X(int a_, int b_);

	operator int() const;
	void Print() const;

private:
	int m_a;

};



X::X() : m_a(0) { }
X::X(int a_) : m_a(a_) { }
X::X(int a_, int b_) : m_a(a_ + b_) { }

X::operator int() const
{
	return m_a;
}


void X::Print() const
{
	std::cout << "X::Print() " << m_a << std::endl;
}

void Fifi(X& x_)
{
	std::cout << "Fifi_1() " << x_ << std::endl;
	x_.Print();
}

/*
void Fifi(X x_, X x1_)
{
	std::cout << "Fifi_2() " << x_ << std::endl;
	std::cout << "Fifi_2() " << x1_ << std::endl;

	x_.Print();
	x1_.Print();

}
*/
/*
void Print(Meter m)
{
	std::cout << "X::Print() " << m_meters << std::endl;

}

*/


int main()
{
	X x1(7);
	X x2(20);

	Fifi(x1); // (1)
	//Fifi(X(20)); // (2)
	Fifi(20); // (2.2) seif k
	//Fifi(X{20}); // (2.1) seif k from C++11

	//Fifi(x2); // (2.3) seif k

	//Fifi(9);  // (3)
	//Fifi(3, 7); // (4)

	//Fifi(X(3, 7)); // (4)

	//Fifi(x2); // (1)
	//Fifi(x1 * 3); // (5.5)

	return x1 * 3; //(5)
}


