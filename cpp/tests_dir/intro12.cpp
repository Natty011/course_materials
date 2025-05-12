#include <iostream>
/*
void Foo();

void Foo(int i);

void Foo(char c);
*/

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

int main()
{
	int i = 7;
	char c = 97;
	unsigned char uc = 120;

	/*float f  = 1.5;*/
	Foo();
	Foo(i);
	Foo(c);
	Foo(uc);
	/*Foo(*uc);*/
	/*Foo(NULL);*/
	/*Foo(f);*/

	std::cout << "Goodbye, World!" << std::endl;
	return 0;
}
