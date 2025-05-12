#include <iostream>
#include <stdio.h>
struct X
{
	//explicit X(); //Init func w/o parameters(default Ctor)
	explicit X(int a_, int b_ = 8); //Regular Ctor
	~X(); //Dtor
	X(const X& other_); // CCtor
	//X& operator=(const X& other_);//Assignment operator//only in c++11 = delete/default;
	//X& operator=(const X& other_);//Assignment operator

	int m_a; // int& m_a;
	const int m_b; //const int m_b;
	X* xp;
};

struct Y
{

	X m_x;
	int m_i;
	Y() : m_x(5, 6), m_i(0) {}

	Y& operator=(const Y& other)
    {
        // not to copy m_b
		m_x.m_a=other.m_x.m_a; 
		const_cast<int&>(m_x.m_b)=other.m_x.m_b; //UNDEFINED
        m_i = other.m_i;
        return *this;
    }
};



//Implemetation of default Ctor.
// the code after the collon called Initialization list
/*
X::X(): m_a(3), m_b(4)
{
//m_a = 3;
//m_b = 4;
std::cout << "this:" << this <<
	" X default Ctor. m_a:" << m_a <<
	" m_b:" << m_b << std::endl;

}
*/
// Implementation of the second Ctor( Regular Ctor )
X::X(int a_, int b_): m_a(a_), m_b(b_) 
{
	std::cout << "this:" << this <<
	" X int int Ctor. m_a:" << m_a <<
	" m_b:" << m_b << std::endl;
}

//Implementation of the copy Ctor
X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b)
{
	std::cout << "this:" << this <<
	" X copy Ctor. m_a:" << m_a <<
	" m_b:" << m_b << std::endl;
}
//Implementation of Assignment operator
/*
X& X::operator=(const X& other_)
{
	m_a= other_.m_a;
	// m_b= other_.m_b;
	std::cout << "this:" << this <<
	" X assignment operator. m_a:" << m_a <<
	" does not change m_b:" << m_b << std::endl;

	return *this;
}
	*/

//Implementation of Dtor
X::~X()
{
	//delete[] xp;

	std::cout << "this:" << this <<
	" X Dtor. m_a:" << m_a <<
	" m_b:" << m_b << std::endl;
}

int main()
{
	/*
	X x1; //Default Ctor
	std::cout << "x1.m_a:" << x1.m_a <<
		"x1.m_b: " << x1.m_b
	 	<<" x1 address = " << &x1 << std::endl;
	puts("-------------------------------------------");

	*/
	X x2(7); //Ctor with 1 param

	std::cout << "x2.m_a:   " <<
	 	x2.m_a <<  "x2.m_b: "<<x2.m_b <<" x2 address = " << &x2 << std::endl;
	puts("-------------------------------------------");

	X *px = new X(x2); // copy Ctor (heap)

	std::cout << "px->m_a: " <<
	px->m_a << "px->m_b: "  <<px->m_b <<", px address = " << px << std::endl;

	puts("-------------------------------------------");

	X x3(9, 10); //Ctor with 2 params

	std::cout << "x3.m_a:   " <<
	 	x3.m_a <<  "x3.m_b: "<<x3.m_b <<" x3 address = " << &x3 << std::endl;
	puts("-------------------------------------------");

	/*X x4(x1); // Copy Ctor

	std::cout << "x4.m_a:   " <<
	 	x4.m_a <<  "x4.m_b: "<<x4.m_b <<" x4 address = " << &x4 << std::endl;
		*/
	puts("-------------------------------------------");

	/*
	x1 = x3; //Assignment operator

	puts("---------Assignment operator  x1 = x3 ------------------");

	std::cout << "x1.m_a: value = " << x3.m_a << ", address = " << &x3 << std::endl;

	std::cout << "x1.m_a:" << x1.m_a <<
		"x1.m_b: " << x1.m_b
	 	<<" x1 address = " << &x1 << std::endl;
	puts("-------------------------------------------");
	puts("------Question 21 -------------------");
	*/
	//X* xp= new X[10];

	puts("-----Dtor of q_21 ----------------");

	//delete xp[]; // delete[] xp;
	puts("-----Dtor of q_20 ----------------");

	delete px; px = 0; //Destructor
	
	puts("-----------------------------------------------------");
	puts("-----------------------------------------------------");

	puts("-----------------Question 22 -------------------------");

	puts("----------------Y y1;---------------------------");

	Y y1;

	//puts("-----------------	y1.m_x.m_a -------------------------");

	y1.m_x.m_a = 250;

	//puts("-----------------Y y2(y1); -------------------------");

	Y y2(y1);
	Y y3;

	y3=y1;

	
	return 0;
}


