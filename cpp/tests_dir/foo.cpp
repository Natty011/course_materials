#include <iostream>

void Foo()
{
	std::cout << "Foo, w/o args!" << std::endl;

}

void Foo(int i)
 {
	std::cout << "Foo, with int i = " << i << std::endl;

 }
void Foo(char c)
 {
	std::cout << "Foo, with char c = " << c << std::endl;

 }

/*g++ -fPIC -shared foo.cpp -o libfoo.so*/
