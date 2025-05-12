#include <iostream>

struct Test
{
    int a;
    const int b;     // ← שדה קבוע
    int& r;          // ← רפרנס

    Test(int& ref) : a(1), b(2), r(ref) {}
};

struct X
{
    X(); // ← הכרזה בלבד
};

int main()
{
	

    //int x = 5;
    //Test t(x); // ← שימוש ממשי בקונסטרקטור

    X x1;

	/*
	Test t1;
	// ← ינסה ליצור copy ctor!

	Test t2 = t1; 
	
	*/

	return 0;
}
