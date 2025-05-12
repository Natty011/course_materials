/*ccccc*/
#include <stdio.h>


enum E{ AA, BB, CC, DD};

enum E2{ TT, KK};


enum E2 e2 = AA;

enum E e;

/*int i = e;*/

int main()
{
	++e;
	change(e);
	printf("%d\n", e);
	return 0;
}

int change(enum E e)
{
	return e+1;
}