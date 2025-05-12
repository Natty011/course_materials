

#include <iostream>
using namespace std;

void Foo() {
	cout << "wii Foo klumnik" << endl;
}

void Foo(int i) {
	cout << "wii Foo int i" << endl;
	cout << "args is:"<< i << endl;
}

void Foo(char c) {
	cout << "wii Foo char c" << endl;
	cout << "args is:"<< c << endl;
}

double Fifi(char c, double a)
{
	cout << "wii Fifi char c" << endl;
	cout << "args is:"<< a << endl;

	return a;
}