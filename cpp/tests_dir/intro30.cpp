#include <iostream>

class X
{
public:
	X() : m_id(++s_cntr) {}
	static void Hello(X& obj_) 
			{
				std::cout << "Hello\n";
				 std::cout << "s_cntr: "<< s_cntr<<"\n" ;
				 //std::cout << "Hello\n"<< "this: "<< this <<"\n" ;
				 std::cout<< "obj_.m_id: "<< obj_.m_id <<"\n" ;
				 std::cout<< "++obj_.m_id: "<< ++obj_.m_id <<"\n" ;


			}

	int GetId()
	{ 
		std::cout << "X::GetId() " << m_id << std::endl; 
		return m_id;
	} 

private:
	int m_id;
	static int s_cntr;
};

//static int s_cntr = 42; //int X::
int X::s_cntr = 0;

int main()
{

	X x1;
	X x2;

	x1.GetId();
	x2.GetId();
	x1.Hello(x1);
	X::Hello(x2);
	x1.Hello(x2);
	
	//X::Hello(x2);

	//X::GetId();

	return 0;
}
