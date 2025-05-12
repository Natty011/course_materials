#include <iostream> // std::cin, std::cout, std::cout
#include <complex.hpp> //nlrd::Complex

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

using nlrd::Complex;

int main()
{
	Complex z1(2, 3); //ctor
	Complex z2(z1); //cctor
	Complex z3(2.5, 2.5); //ctor

	std::cout << z1 << "\n";
	std::cout << z2 << "\n";
	std::cout << z3 << "\n";


	return 0;
}
