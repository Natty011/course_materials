#include <iostream>
using namespace std;

struct X
{
    explicit X(int); //Ctor gets int
    ~X();

    void Foo(); //member func( non const- can change the feilds of the object)
    void Bar() const; // const member function - doesn't change the object fiels

    int m_a;
    int *m_p; //pointer to dynamic object/s
	//const int *m_p; 
};

//Ctor - allocate dynamiclly and save variables
X::X(int a_) : m_a(a_), m_p(new int(a_)) {}

// Dtor- release the dynamic alloction
X::~X()
{ 
	delete m_p; 
	m_p = 0; 
}

// member function - change the state of the object
void X::Foo() 
{ 
	++m_a;
	//std::cout << *m_p << std::endl;
	--(*m_p);
}

// const member function - promise not to change the objects' fields
void X::Bar() const
{
	cout << "this:" << this << endl;

    std::cout << m_a << std::endl;
    std::cout << *m_p << std::endl;
    std::cout << m_p << std::endl;

    //m_a = 0;    // ---1--- not legal
    //m_p = 0;    // ---2--- not legal
    //*m_p = 0;   // ---3--- legal but danger
    //Foo();      // ---5--- can't call to non const function
}

void Fifi(const X& x_)
{
    //x_.Foo();   // ---4---  forbiden cause Foo is non const function
    x_.Bar();  // allowed cause bar defined as const function
}

int main()
{
    X x1(1);
	//X x3=x1;
    X x2(2);

    x1.Foo();
    Fifi(x1);
	x1.Bar();
	//x2.Bar();
	//x2.Foo();

	x1=x2;

	cout << "&x1:" << &x1 << endl;
	cout << "x1.m_p:" << x1.m_p << endl;

	cout << "&x2:" << &x2 << endl;
	cout << "x2.m_p:" << x2.m_p << endl;


    return 0;
}
