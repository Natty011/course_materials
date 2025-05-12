#include <cstdio>

struct X
{
public:
	explicit X(); //Init func w/o parameters(default Ctor) // add
    explicit X(int a_);
    void Foo() const;  // void Foo()  const
	int GetA() const { return m_a; } // add
	friend void Foo(const X&); // direct accsess // add



private:
	unsigned char m_a; // int m_a;
};

X::X(): m_a(0)
{

} 

X::X(int a_)
    : m_a(a_)
{
}

void X::Foo() const
{
    printf("%d\n", m_a);

}

void Foo(const X &x_)
{
    //printf("%d\n", x_.GetA()); // add

	printf("%d\n", x_.m_a);
}



int main()
{
    //const X x1(1);
    X x1;

    x1.Foo();
   	printf("%d\n", x1.GetA()); //add
	Foo(x1);

    return 0;
}
