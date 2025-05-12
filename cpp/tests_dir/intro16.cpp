#include <iostream>
#include "intro16.hpp"

/*
template <typename T>
T Max(T a, T b);  // רק הצהרה – אין צורך לבדוק תחביר של גוף
*/
int main()
{
	int arr[12];
	//arr[8] = 5;
	//Max(3, 5);
	std::cout<<Max<int>(3, 5) << " \n" ;
	std::cout<<Max(3, (int)5.5) << " \n" ;

	std::cout<< Max<double>(3.7, 12.9) << " \n";
	std::cout << Max<int*>(arr, arr + 8) << std::endl;
	std::cout << Max('a', 'b' ) << std::endl;
	/*std::cout << Max<float>(5.1f, 4.9f ) << std::endl;
	std::cout << Max<std::string>("Hello", "World" ) << std::endl;*/
	/*std::cout << Max<void>(arr, arr + 8 ) << std::endl;*/

	return 0;
}

