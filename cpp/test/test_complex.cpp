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

	std::cout << "z1: " << z1 << "\n";
	std::cout << "z2: " << z2 << "\n";
	std::cout << "z3: " << z3 << "\n";

	z2= z3; //assignment op
	std::cout << "z2: " << z2 << "\n";
	// gettters
	std::cout << "z1.GetReal(): " << z1.GetReal() <<"\n"
			  << "z1.GetImag(): " << z1.GetImag() << "\n";
	
	//eqaul operator
	std::cout << "z1==z2: " << (z1==z2) << "\n";
	std::cout << "z3==z2: " << (z3==z2) << "\n";
	std::cout << "z3==z2: " << std::boolalpha << (z3==z2) << std::noboolalpha << "\n";

	//un-eqaul operator
	std::cout << "z1!=z2: " << (z1!=z2) << "\n";
	std::cout << "z3!=z2: " << (z3!=z2) << "\n";
	std::cout << "z3!=z2: " << std::boolalpha << (z3!=z2) << "\n";
	std::cout << "z1!=z2: " << std::boolalpha << (z1!=z2) << std::noboolalpha << "\n";

	//setters
	z2.SetReal(4.5);
	z2.SetImag(3.5);
	std::cout << "z2: " << z2 << "\n";

	//Abs
	std::cout << "z1.Abs(): " << z1.Abs() <<"\n";
	std::cout << "z2.Abs(): " << z2.Abs() <<"\n";
	std::cout << "z3.Abs(): " << z3.Abs() <<"\n";

	//operator+=  ---- operator-=
	std::cout << "z1+=z2: " << (z1+= z2) << "\n";
	std::cout << "z1-=z2: " << (z1-= z2) << "\n";

	//operator*=  ---- operator/= --> work
	std::cout << "z1*=z2: " << (z1*= z2) << "\n";
	std::cout << "z1/=z2: " << (z1/= z2) << "\n";

	

	return 0;

}
