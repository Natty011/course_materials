#include <iostream>
using namespace std;
int x = 14;

namespace A 
{ 
	int x = 2;

	void Foo()
	{
		cout << "A::Foo\n";
		int x = 12;
		std::cout << "A::Foo::x=" << x << "\n";
	}
 }

 //using A::Foo;
 //using namespace A;


void Foo()
 {
	cout << "Global Foo\n";
	//int x = 10;
    //std::cout << x << "\n";
	std::cout << "Global Foo x=" << x << "\n";

 } 

//using namespace A;
//using A::Foo;
int main()
{
	//using A::Foo;
	Foo(); 

	{
		int x = 8;

		using A::Foo;
		//void Foo();
		Foo(); 
		::Foo(); 
		std::cout << "A::x =" << A::x << "\n";
		std::cout << "local x=" << x << "\n";

	}

	return 0;
}



