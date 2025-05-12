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

	// operator<< stdout
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
	std::cout << "z1*= z2: " << (z1*= z2) << "\n";
	std::cout << "z1/= z2: " << (z1/= z2) << "\n";

	//operator+,  operator-=
	std::cout << "z1 + z2: " << (z1 + z2) << "\n";
	std::cout << "z1 - z2: " << (z1 - z2) << "\n";

	//operator*=  ---- operator/= --> work
	std::cout << "z1 * z2: " << (z1 * z2) << "\n";
	std::cout << "z1 / z2: " << (z1 / z2) << "\n";

	//operator>> stdin
	Complex z4;
	Complex z5;

	std::cout << "Entert First number: like ( 3 4 OR (3, 4)): ";

	std::cin >> z4 ;
	
	if (!std::cin)
    {
        std::cerr << "Error: first format unvalid" << std::endl;
        return 1;
    }
	std::cout << "Enter second number: like ( -2 1.5 OR (-2, 1.5)): ";

	std::cin >> z5 ;
	
	if (!std::cin)
    {
        std::cerr << "Error: Second format unvalid" << std::endl;
        return 1;
    }

	std::cout << "first num: " << z4 << "\n";
	std::cout << "second num: " << z5 << "\n";

	Complex sum = z4 + z5;
    Complex diff = z4 - z5;
    Complex prod = z4 * z5;
    Complex quot;

    try
    {
        quot =  z4 / z5;
    }
    catch (...)
    {
        std::cerr << "Error: divison by zero!" << std::endl;
    }

    std::cout << "\nsum: " << sum << std::endl;
    std::cout << "diff: " << diff << std::endl;
    std::cout << "prod: " << prod << std::endl;
    std::cout << "quat: " << quot << std::endl;

    std::cout << "\neqaul checking: " 
              << (z4 == z5 ? "equal" : "non-eqaul") 
              << std::endl;

	return 0;

}
