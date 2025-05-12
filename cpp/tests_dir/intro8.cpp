
#include <iostream>

int main() {
    int age;
    std::cout << "Enter your age: ";
    std::cin >> age;

    if (age < 0) {
        std::cerr << "Invalid age!\n";
    } else {
        std::cout << "You are " << age << " years old.\n";
    }

    return 0;
}

/*
#include <iostream>

int main()
{
	int i = 200;
	std::cout << "Hello, World!, i = " << i << std::endl;

	std::cin >> i ;

	std::cerr << "error: Goodby World, i = " << i << std::endl;

	return 0;
}
*/