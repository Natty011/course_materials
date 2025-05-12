/*C++*/
#include <iostream>
using namespace std;

//const int i;

enum E{ AA, BB, CC, DD};

enum E2{ TT, KK};

enum E2 non_init;


//int i = e;

int main()
{
	enum E e;
	++e;
	cout << e << endl;

	return 0;
}