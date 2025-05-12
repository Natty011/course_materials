#include <iostream>

struct A
{
    const int x;
};

struct B
{
    int& r;
};


struct NoAssign
{
    NoAssign() {}
    NoAssign(const NoAssign&) {}
    NoAssign& operator=(const NoAssign&) = delete;
};

struct C
{
    NoAssign na;
};



struct D
{
    D(const D&) {}  // ← copy ctor
};


struct E
{
    E(const E&) = delete;
};

struct F
{
    E e;
};


struct G
{
    G() = delete;
};

struct X
{
    int& r;        // default ctor
    const int c;   // ין default ctor
    std::string s; // copy ctor ו־operator=

    // X() = default;     // לא יעבוד בגלל r ו־c
    // X& operator=(const X&) = default; // כן יעבוד אם r ו־c מאותחלים
};


int main()
{
	// הקומפיילר לא יכול לייצר ctor בלי לדעת ערך ל־x
	 // ❌ שגיאה: no matching constructor
	A a; 

	// ❌ שגיאה: reference must be bound
	B b;  

 // ❌ שגיאה בקומפילציה
	C c1, c2;
	c1 = c2; 

	// ❌ no move ctor
	D d1;
	D d2 = std::move(d1);  

	// ❌ שגיאה: can't copy assign F
	F f1, f2;
	f1 = f2;
	
	// ❌ שגיאה: constructor is deleted
	G g;  


	return 0;
}
