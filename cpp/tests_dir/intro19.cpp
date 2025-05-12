#include <iostream>

void Foo(const double& d)
{
    std::cout << "Foo: value = " << d << ", address = " << &d << std::endl;

}
void Bar(double& d)
{
    std::cout << "Bar: value = " << d << ", address = " << &d << std::endl;
}

int main()
{
	int x = 5;
	std::cout << "x: value = " << x << ", address = " << &x << std::endl;

	Foo(x);
	Bar(*reinterpret_cast<double*>(&x));
	//Bar(x);
	//Bar((double&)x);

	return 0;
}
