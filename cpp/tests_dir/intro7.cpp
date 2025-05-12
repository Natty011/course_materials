

// נכון עם new/delete
MyClass* a = new MyClass();
delete a;

// נכון עם malloc/free – אבל רק אם אין constructor
int* b = (int*)malloc(sizeof(int));
*b = 42;
free(b);





#include <iostream>
#include <cstdlib>  // בשביל malloc ו־free

class MyClass
{
public:
    MyClass()  { std::cout << "Constructor called\n"; }
    ~MyClass() { std::cout << "Destructor called\n"; }
};

int main()
{
    // הקצאה ב־malloc ושחרור ב־delete - ❌ טעות
    MyClass* p1 = (MyClass*)malloc(sizeof(MyClass));  // רק זיכרון, אין constructor
    delete p1;  // ❌ destructor יופעל על אובייקט שלא נבנה – UB

    // הקצאה ב־new ושחרור ב־free - ❌ טעות
    MyClass* p2 = new MyClass();  // ✔ constructor יופעל
    free(p2);  // ❌ לא נקרא destructor – זליגת לוגיקה!

    return 0;
}

/*
#include <stdio.h>
#include <iostream>

int main()
{
	float *f = new float(12.0);
	std::cout << "f = " << f << std::endl;
	std::cout << "*f = " << *f << std::endl;

	f = new float[15];

	for(int i = 0; i < 15 ; ++i)
	{
		std::cout << "f +i = " << f + i<< std::endl;
		std::cout << "*f +i = " << *(f + i) << std::endl;
	}
	
	return 0;
}
*/