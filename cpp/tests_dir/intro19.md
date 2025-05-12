/******* seif a ********/

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
	Foo(x);
	//Bar(x);

	return 0;
}

output:


natty@natty:~/test$ run_gd98 intro19.cpp 
Foo: value = 5, address = 0x7ffc43d16f00

natty@natty:~/test$ run_gd98 intro19.cpp 
intro19.cpp: In function ‘int main()’:
intro19.cpp:17:13: error: cannot bind non-const lvalue reference of type ‘double&’ to a value of type ‘int’
   17 |         Bar(x);
      |             ^
intro19.cpp:8:18: note:   initializing argument 1 of ‘void Bar(double&)’
    8 | void Bar(double& d)
      |          ~~~~~~~~^

/******* seif b ********/

int main()
{
	int x = 5;
	Foo(x);
	Bar(*reinterpret_cast<double*>(&x));

	//Bar((double&)x);

	return 0;
}

output:

natty@natty:~/test$ run_gd98 intro19.cpp 
Foo: value = 5, address = 0x7ffe3d010450
Bar: value = 2.47033e-323, address = 0x7ffe3d01044c

/******* seif c - d ********/

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

output:

natty@natty:~/test$ run_gd98 intro19.cpp 
x: value = 5, address = 0x7ffc3310e9fc //same
Foo: value = 5, address = 0x7ffc3310ea00
Bar: value = 2.47033e-323, address = 0x7ffc3310e9fc //same
