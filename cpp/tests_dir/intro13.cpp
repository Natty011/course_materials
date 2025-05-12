#include <iostream>
using namespace std;

namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_nothere;

    void Foo()
	{
		cout << "useless::Foo\n";
	}

	namespace wasteoftyme
	{
		void Foo()
		{
			cout << "wasteoftyme::Foo\n";
		}
	} // namespace wasteoftyme
}// namespace useless

namespace stupid
{
    void Foo()
	{
		cout << "stupid::Foo\n";
	}

    void Bar() 
	{
		cout << "stupid::Bar\n";
	}

    void DoNothing(unsigned int i = 0)
	{
		cout << "stupid::DoNothing\n";
		cout << "stupid::DoNothing: unsigned int i= " << i << "\n";

	}
}// namespace stupid

namespace useless
{
    void DoNothing(int i = 0)
	{
		//cout << "useless::DoNothing\n";
		cout << "useless::DoNothing: int i= " << i << "\n";

	}
} // namespace useless


using namespace useless;

void DoStuff()
{
	cout << "Global Scope ---DoStuff()---\n";
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo()
{
	cout << "Global Scope ---Definition : void Foo()---\n";
}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
	cout << "Global Scope ---DoMoreStuff()---\n";
    comeon::Foo();
	::Foo();  // try uncommenting this line, solve the error
    //Foo();  // try uncommenting this line, solve the error
    Bar();     // why doesn't this line create an error?
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
    void DoUselessStuff()
    {
		cout << "useless::DoUselessStuff\n";
/* will call DoNothing of useless
 because DoUselessStuff it is definition of useless */		
        DoNothing(g_wasteful[3] + 1);
    }
}//namespace useless
/*
void Foo()
{
	cout << "Global Scope ---Definition : void Foo()---\n";
}
*/	

int main()
{

	//Foo();  
	DoMoreStuff();
	/*DoStuff();
	/*Foo();*/
	/*DoNothing(7);*/
	return 0;
}


//call Foo(); 1st solution (temporary promotion / qualified )
	//using stupid::Foo;
	
	//2nd sol: ( explicit promotion / fully quialified name)
	//useless::Foo();  
	 			//3rd sol:( remove/choose one of the namespace:
				// using namespace useless/using namespace stupid)



