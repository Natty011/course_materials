#include <iostream>

void foo(int, int i = 10, float = 20);

int main()
{
	float ff = 67.7;
	foo(3);
	foo(6, 5);
	foo(4, 7, 8.7);
	foo(4, 7, ff);
	//foo(3 , , ff);
	std::cout << "Goodbye, World!" << std::endl;
	return 0;
}

void foo(int j, int i , float f)
{
	std::cout << "j = " << j <<  std::endl;

	std::cout << "i = " << i <<std::endl << "f = " << f<< std::endl;

}
