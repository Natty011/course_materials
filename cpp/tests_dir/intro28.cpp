#include <iostream>
using namespace std;

class X;
// operator+  : Global function, return 7 no matter what are the arguments
int operator+(const X& x1_, const X& x2_)
{
	return 7;
}

//ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
	bool operator==(const X& o_) const { return m_a == o_.m_a; }
	//int GetA() const { return m_a; }
	// Java style inline – not allowed in our coding standard

private:
	// Global function (not methode) that need access to m_a,
	// therefore define as friend
	friend ostream& operator<<(ostream& os_, const X& x_); //friend 
	int m_a;

};


int main()
{
	X x1;
	X x2;

	cout<< " x1+x2:" << x1 + x2 <<
		   " x1==x2:" << (x1 == x2) <<
		   " x1:" << x1 <<
		   " x2:" << x2 <<endl; // <<" x1:" << x1 <<endl

//cout << " x1+x2:" << x1 + x2 << " x1==x2:" << (x1 == x2) << " x1:" << x1 << " x2:" << x2 << endl;
	return 0;
}

ostream& operator<<(ostream& os_, const X& x_)
{
	return os_ << x_.m_a;
}

/*
ostream& operator<<(ostream& os_, const X& x_)
{
	return os_ << x_.GetA();
}
*/	
