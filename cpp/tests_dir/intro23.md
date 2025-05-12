/*********question 23 ************************/
/*********seif a **************************/
struct X
{
	//explicit X(); //Init func w/o parameters(default Ctor)
	explicit X(int a_, int b_ = 8); //Regular Ctor
	~X(); //Dtor
	X(const X& other_); // CCtor
	//X& operator=(const X& other_);//Assignment operator//only in c++11 = delete/default;
	//X& operator=(const X& other_);//Assignment operator

	int &m_a;
	int m_b; //const int m_b;
	X* xp;
};


natty@natty:~/test$ run_gd98 intro20.cpp 
intro20.cpp: In member function ‘X& X::operator=(const X&)’:
intro20.cpp:3:8: error: non-static reference member ‘int& X::m_a’, cannot use default assignment operator
    3 | struct X
      |        ^
intro20.cpp: In member function ‘Y& Y::operator=(const Y&)’:
intro20.cpp:17:8: note: synthesized method ‘X& X::operator=(const X&)’ first required here
   17 | struct Y
      |        ^
intro20.cpp: In function ‘int main()’:
intro20.cpp:162:12: note: synthesized method ‘Y& Y::operator=(const Y&)’ first required here
  162 |         y3=y1;
      |            ^~
/************************************************************/


struct X
{
	//explicit X(); //Init func w/o parameters(default Ctor)
	explicit X(int a_, int b_ = 8); //Regular Ctor
	~X(); //Dtor
	X(const X& other_); // CCtor
	//X& operator=(const X& other_);//Assignment operator//only in c++11 = delete/default;
	//X& operator=(const X& other_);//Assignment operator

	int m_a;
	const int m_b; //const int m_b;
	X* xp;
};

natty@natty:~/test$ run_gd98 intro20.cpp 
intro20.cpp: In member function ‘X& X::operator=(const X&)’:
intro20.cpp:3:8: error: non-static const member ‘const int X::m_b’, cannot use default assignment operator
    3 | struct X
      |        ^
intro20.cpp: In member function ‘Y& Y::operator=(const Y&)’:
intro20.cpp:17:8: note: synthesized method ‘X& X::operator=(const X&)’ first required here
   17 | struct Y
      |        ^
intro20.cpp: In function ‘int main()’:
intro20.cpp:162:12: note: synthesized method ‘Y& Y::operator=(const Y&)’ first required here
  162 |         y3=y1;
      |          




      /**************************************************/

      מה ניתן להסיק מהדוגמאות שהבאת ומהשגיאות שקיבלתי? השתמשתי בדוגמאות שלך..

קוד:
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



פלט:
natty@natty:~/test$ run_g
run_gc    run_gc11  run_gc98  run_gd    run_gd11  run_gd98  
natty@natty:~/test$ run_gd11 intro23.cpp
intro23.cpp: In function ‘int main()’:
intro23.cpp:20:11: error: use of deleted function ‘B::B()’
   20 |         B b;
      |           ^
intro23.cpp:8:8: note: ‘B::B()’ is implicitly deleted because the default definition would be ill-formed:
    8 | struct B
      |        ^
intro23.cpp:8:8: error: uninitialized reference member in ‘struct B’
intro23.cpp:10:10: note: ‘int& B::r’ should be initialized
   10 |     int& r;
      |          ^
intro23.cpp:20:11: warning: unused variable ‘b’ [-Wunused-variable]
   20 |         B b;
      |           ^
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp: In function ‘int main()’:
intro23.cpp:20:11: error: uninitialized reference member in ‘struct B’
   20 |         B b;
      |           ^
intro23.cpp:10:10: note: ‘int& B::r’ should be initialized
   10 |     int& r;
      |          ^
intro23.cpp:20:11: warning: unused variable ‘b’ [-Wunused-variable]
   20 |         B b;
      |           ^
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp:18:44: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |                                            ^~~~~~
natty@natty:~/test$ run_gd11 intro23.cpp
intro23.cpp: In function ‘int main()’:
intro23.cpp:41:14: error: use of deleted function ‘C& C::operator=(const C&)’
   41 |         c1 = c2;
      |              ^~
intro23.cpp:21:8: note: ‘C& C::operator=(const C&)’ is implicitly deleted because the default definition would be ill-formed:
   21 | struct C
      |        ^
intro23.cpp:21:8: error: use of deleted function ‘NoAssign& NoAssign::operator=(const NoAssign&)’
intro23.cpp:18:15: note: declared here
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |               ^~~~~~~~
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp:18:44: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |                                            ^~~~~~
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp:18:44: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |                                            ^~~~~~
intro23.cpp: In function ‘int main()’:
intro23.cpp:50:11: error: no matching function for call to ‘D::D()’
   50 |         D d1;
      |           ^~
intro23.cpp:30:5: note: candidate: ‘D::D(const D&)’
   30 |     D(const D&) {}  // ← copy ctor
      |     ^
intro23.cpp:30:5: note:   candidate expects 1 argument, 0 provided
intro23.cpp:51:21: error: ‘move’ is not a member of ‘std’
   51 |         D d2 = std::move(d1);
      |                     ^~~~
intro23.cpp:51:21: note: ‘std::move’ is only available from C++11 onwards
intro23.cpp:51:11: warning: unused variable ‘d2’ [-Wunused-variable]
   51 |         D d2 = std::move(d1);
      |           ^~
natty@natty:~/test$ run_gd11 intro23.cpp
intro23.cpp: In function ‘int main()’:
intro23.cpp:50:11: error: no matching function for call to ‘D::D()’
   50 |         D d1;
      |           ^~
intro23.cpp:30:5: note: candidate: ‘D::D(const D&)’
   30 |     D(const D&) {}  // ← copy ctor
      |     ^
intro23.cpp:30:5: note:   candidate expects 1 argument, 0 provided
natty@natty:~/test$ run_gd11 intro23.cpp
intro23.cpp: In function ‘int main()’:
intro23.cpp:65:11: error: use of deleted function ‘F::F()’
   65 |         F f1, f2;
      |           ^~
intro23.cpp:39:8: note: ‘F::F()’ is implicitly deleted because the default definition would be ill-formed:
   39 | struct F
      |        ^
intro23.cpp:39:8: error: no matching function for call to ‘E::E()’
intro23.cpp:36:5: note: candidate: ‘E::E(const E&)’ (deleted)
   36 |     E(const E&) = delete;
      |     ^
intro23.cpp:36:5: note:   candidate expects 1 argument, 0 provided
intro23.cpp:65:15: error: use of deleted function ‘F::F()’
   65 |         F f1, f2;
      |               ^~
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp:18:44: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |                                            ^~~~~~
intro23.cpp:36:19: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   36 |     E(const E&) = delete;
      |                   ^~~~~~
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp:18:44: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |                                            ^~~~~~
intro23.cpp:36:19: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   36 |     E(const E&) = delete;
      |                   ^~~~~~
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp:18:44: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |                                            ^~~~~~
intro23.cpp:36:19: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   36 |     E(const E&) = delete;
      |                   ^~~~~~
intro23.cpp:47:11: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   47 |     G() = delete;
      |           ^~~~~~
intro23.cpp: In function ‘int main()’:
intro23.cpp:74:11: warning: unused variable ‘g’ [-Wunused-variable]
   74 |         G g;
      |           ^
natty@natty:~/test$ run_gd11 intro23.cpp
intro23.cpp: In function ‘int main()’:
intro23.cpp:74:11: error: use of deleted function ‘G::G()’
   74 |         G g;
      |           ^
intro23.cpp:47:5: note: declared here
   47 |     G() = delete;
      |     ^
intro23.cpp:74:11: warning: unused variable ‘g’ [-Wunused-variable]
   74 |         G g;
      |           ^
natty@natty:~/test$ run_gd98 intro23.cpp
intro23.cpp:18:44: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |                                            ^~~~~~
intro23.cpp:36:19: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   36 |     E(const E&) = delete;
      |                   ^~~~~~
intro23.cpp:47:11: error: defaulted and deleted functions only available with ‘-std=c++11’ or ‘-std=gnu++11’
   47 |     G() = delete;
      |           ^~~~~~
intro23.cpp: In function ‘int main()’:
intro23.cpp:56:11: error: uninitialized const member in ‘struct A’
   56 |         A a;
      |           ^
intro23.cpp:5:15: note: ‘const int A::x’ should be initialized
    5 |     const int x;
      |               ^
intro23.cpp:59:11: error: uninitialized reference member in ‘struct B’
   59 |         B b;
      |           ^
intro23.cpp:10:10: note: ‘int& B::r’ should be initialized
   10 |     int& r;
      |          ^
intro23.cpp:66:11: error: no matching function for call to ‘D::D()’
   66 |         D d1;
      |           ^~
intro23.cpp:30:5: note: candidate: ‘D::D(const D&)’
   30 |     D(const D&) {}  // ← copy ctor
      |     ^
intro23.cpp:30:5: note:   candidate expects 1 argument, 0 provided
intro23.cpp:67:21: error: ‘move’ is not a member of ‘std’
   67 |         D d2 = std::move(d1);
      |                     ^~~~
intro23.cpp:67:21: note: ‘std::move’ is only available from C++11 onwards
intro23.cpp:56:11: warning: unused variable ‘a’ [-Wunused-variable]
   56 |         A a;
      |           ^
intro23.cpp:59:11: warning: unused variable ‘b’ [-Wunused-variable]
   59 |         B b;
      |           ^
intro23.cpp:67:11: warning: unused variable ‘d2’ [-Wunused-variable]
   67 |         D d2 = std::move(d1);
      |           ^~
intro23.cpp:74:11: warning: unused variable ‘g’ [-Wunused-variable]
   74 |         G g;
      |      


      /****************************************************************/

 natty@natty:~/test$ run_gd11 intro23.cpp
intro23.cpp: In function ‘int main()’:
intro23.cpp:56:11: error: use of deleted function ‘A::A()’
   56 |         A a;
      |           ^
intro23.cpp:3:8: note: ‘A::A()’ is implicitly deleted because the default definition would be ill-formed:
    3 | struct A
      |        ^
intro23.cpp:3:8: error: uninitialized const member in ‘struct A’
intro23.cpp:5:15: note: ‘const int A::x’ should be initialized
    5 |     const int x;
      |               ^
intro23.cpp:59:11: error: use of deleted function ‘B::B()’
   59 |         B b;
      |           ^
intro23.cpp:8:8: note: ‘B::B()’ is implicitly deleted because the default definition would be ill-formed:
    8 | struct B
      |        ^
intro23.cpp:8:8: error: uninitialized reference member in ‘struct B’
intro23.cpp:10:10: note: ‘int& B::r’ should be initialized
   10 |     int& r;
      |          ^
intro23.cpp:63:14: error: use of deleted function ‘C& C::operator=(const C&)’
   63 |         c1 = c2;
      |              ^~
intro23.cpp:21:8: note: ‘C& C::operator=(const C&)’ is implicitly deleted because the default definition would be ill-formed:
   21 | struct C
      |        ^
intro23.cpp:21:8: error: use of deleted function ‘NoAssign& NoAssign::operator=(const NoAssign&)’
intro23.cpp:18:15: note: declared here
   18 |     NoAssign& operator=(const NoAssign&) = delete;
      |               ^~~~~~~~
intro23.cpp:66:11: error: no matching function for call to ‘D::D()’
   66 |         D d1;
      |           ^~
intro23.cpp:30:5: note: candidate: ‘D::D(const D&)’
   30 |     D(const D&) {}  // ← copy ctor
      |     ^
intro23.cpp:30:5: note:   candidate expects 1 argument, 0 provided
intro23.cpp:70:11: error: use of deleted function ‘F::F()’
   70 |         F f1, f2;
      |           ^~
intro23.cpp:39:8: note: ‘F::F()’ is implicitly deleted because the default definition would be ill-formed:
   39 | struct F
      |        ^
intro23.cpp:39:8: error: no matching function for call to ‘E::E()’
intro23.cpp:36:5: note: candidate: ‘E::E(const E&)’ (deleted)
   36 |     E(const E&) = delete;
      |     ^
intro23.cpp:36:5: note:   candidate expects 1 argument, 0 provided
intro23.cpp:70:15: error: use of deleted function ‘F::F()’
   70 |         F f1, f2;
      |               ^~
intro23.cpp:74:11: error: use of deleted function ‘G::G()’
   74 |         G g;
      |           ^
intro23.cpp:47:5: note: declared here
   47 |     G() = delete;
      |     ^
intro23.cpp:56:11: warning: unused variable ‘a’ [-Wunused-variable]
   56 |         A a;
      |           ^
intro23.cpp:59:11: warning: unused variable ‘b’ [-Wunused-variable]
   59 |         B b;
      |           ^
intro23.cpp:74:11: warning: unused variable ‘g’ [-Wunused-variable]
   74 |         G g;
      |           ^

 /***********************************************************************/     
 /***********************seif  d and e ******************************/     
#include <iostream>

struct Test
{
    int a;
    const int b;     // ← שדה קבוע
    int& r;          // ← רפרנס

    Test(int& ref) : a(1), b(2), r(ref) {}
};

int main()
{
	Test t1;
	// ← ינסה ליצור copy ctor!

	Test t2 = t1;  

	return 0;
}


natty@natty:~/test$ run_gd98 intro23_d_e.cpp
intro23_d_e.cpp: In function ‘int main()’:
intro23_d_e.cpp:14:14: error: no matching function for call to ‘Test::Test()’
   14 |         Test t1;
      |              ^~
intro23_d_e.cpp:9:5: note: candidate: ‘Test::Test(int&)’
    9 |     Test(int& ref) : a(1), b(2), r(ref) {}
      |     ^~~~
intro23_d_e.cpp:9:5: note:   candidate expects 1 argument, 0 provided
intro23_d_e.cpp:3:8: note: candidate: ‘Test::Test(const Test&)’
    3 | struct Test
      |        ^~~~
intro23_d_e.cpp:3:8: note:   candidate expects 1 argument, 0 provided


/***********************************************/
natty@natty:~/test$ labp intro23_d_e
natty@natty:~/test$ run_gd98 intro23_d_e.cpp
natty@natty:~/test$ nm intro23_d_e.out
000000000000038c r __abi_tag
0000000000004010 B __bss_start
0000000000004010 b completed.0
                 U __cxa_atexit@GLIBC_2.2.5
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
00000000000010b0 t deregister_tm_clones
0000000000001120 t __do_global_dtors_aux
0000000000003da0 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003da8 d _DYNAMIC
0000000000004010 D _edata
0000000000004018 B _end
00000000000011e8 T _fini
0000000000001160 t frame_dummy
0000000000003d90 d __frame_dummy_init_array_entry
0000000000002130 r __FRAME_END__
0000000000003fa8 d _GLOBAL_OFFSET_TABLE_
00000000000011ce t _GLOBAL__sub_I_main
                 w __gmon_start__
0000000000002004 r __GNU_EH_FRAME_HDR
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
0000000000001169 T main
00000000000010e0 t register_tm_clones
0000000000001080 T _start
0000000000004010 D __TMC_END__
0000000000001178 t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4
0000000000004011 b _ZStL8__ioinit
natty@natty:~/test$ gd98 -c intro23_d_e.cpp -o intro23_d_e.o
natty@natty:~/test$ nm intro23_d_e.o
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000065 t _GLOBAL__sub_I_main
0000000000000000 T main
000000000000000f t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
0000000000000000 b _ZStL8__ioinit
natty@natty:~/test$ nm -C intro23_d_e.o
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000065 t _GLOBAL__sub_I_main
0000000000000000 T main
000000000000000f t __static_initialization_and_destruction_0(int, int)
                 U std::ios_base::Init::Init()
                 U std::ios_base::Init::~Init()
0000000000000000 b std::__ioinit
natty@natty:~/test$ nm -C intro23_d_e.out
000000000000038c r __abi_tag
0000000000004010 B __bss_start
0000000000004010 b completed.0
                 U __cxa_atexit@GLIBC_2.2.5
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
00000000000010b0 t deregister_tm_clones
0000000000001120 t __do_global_dtors_aux
0000000000003da0 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003da8 d _DYNAMIC
0000000000004010 D _edata
0000000000004018 B _end
00000000000011e8 T _fini
0000000000001160 t frame_dummy
0000000000003d90 d __frame_dummy_init_array_entry
0000000000002130 r __FRAME_END__
0000000000003fa8 d _GLOBAL_OFFSET_TABLE_
00000000000011ce t _GLOBAL__sub_I_main
                 w __gmon_start__
0000000000002004 r __GNU_EH_FRAME_HDR
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
0000000000001169 T main
00000000000010e0 t register_tm_clones
0000000000001080 T _start
0000000000004010 D __TMC_END__
0000000000001178 t __static_initialization_and_destruction_0(int, int)
                 U std::ios_base::Init::Init()@GLIBCXX_3.4
                 U std::ios_base::Init::~Init()@GLIBCXX_3.4
0000000000004011 b std::__ioinit
natty@natty:~/test$ run_gd98 intro23_d_e.cpp
intro23_d_e.cpp: In function ‘int main()’:
intro23_d_e.cpp:14:19: error: ‘t1’ was not declared in this scope; did you mean ‘t2’?
   14 |         Test t2 = t1;  // ← ינסה ליצור copy ctor!
      |                   ^~
      |                   t2
intro23_d_e.cpp:14:14: warning: unused variable ‘t2’ [-Wunused-variable]
   14 |         Test t2 = t1;  // ← ינסה ליצור copy ctor!
      |              ^~
natty@natty:~/test$ run_gd98 intro23_d_e.cpp
intro23_d_e.cpp: In function ‘int main()’:
intro23_d_e.cpp:14:14: error: no matching function for call to ‘Test::Test()’
   14 |         Test t1;
      |              ^~
intro23_d_e.cpp:9:5: note: candidate: ‘Test::Test(int&)’
    9 |     Test(int& ref) : a(1), b(2), r(ref) {}
      |     ^~~~
intro23_d_e.cpp:9:5: note:   candidate expects 1 argument, 0 provided
intro23_d_e.cpp:3:8: note: candidate: ‘Test::Test(const Test&)’
    3 | struct Test
      |        ^~~~
intro23_d_e.cpp:3:8: note:   candidate expects 1 argument, 0 provided

/*****************************************************************/

#include <iostream>

struct Test
{
    int a;
    const int b;     // ← שדה קבוע
    int& r;          // ← רפרנס

    Test(int& ref) : a(1), b(2), r(ref) {}
};

int main()
{
	

    int x = 5;
    Test t(x); // ← שימוש ממשי בקונסטרקטור


	/*
	Test t1;
	// ← ינסה ליצור copy ctor!

	Test t2 = t1; 
	
	*/

	return 0;
}


natty@natty:~/test$ run_gd98 intro23_d_e.cpp
natty@natty:~/test$ gd98 -c intro23_d_e.cpp -o intro23_d_e.o
natty@natty:~/test$ nm -C intro23_d_e.o
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
00000000000000a6 t _GLOBAL__sub_I_main
0000000000000000 T main
                 U __stack_chk_fail
0000000000000050 t __static_initialization_and_destruction_0(int, int)
0000000000000000 W Test::Test(int&)
0000000000000000 W Test::Test(int&)
0000000000000000 n Test::Test(int&)
                 U std::ios_base::Init::Init()
                 U std::ios_base::Init::~Init()
0000000000000000 b std::__ioinit
natty@natty:~/test$ nm -C intro23_d_e.out
000000000000038c r __abi_tag
0000000000004010 B __bss_start
0000000000004010 b completed.0
                 U __cxa_atexit@GLIBC_2.2.5
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
00000000000010d0 t deregister_tm_clones
0000000000001140 t __do_global_dtors_aux
0000000000003d98 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003da0 d _DYNAMIC
0000000000004010 D _edata
0000000000004018 B _end
000000000000127c T _fini
0000000000001180 t frame_dummy
0000000000003d88 d __frame_dummy_init_array_entry
0000000000002158 r __FRAME_END__
0000000000003fa0 d _GLOBAL_OFFSET_TABLE_
000000000000122f t _GLOBAL__sub_I_main
                 w __gmon_start__
0000000000002004 r __GNU_EH_FRAME_HDR
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
0000000000001189 T main
0000000000001100 t register_tm_clones
                 U __stack_chk_fail@GLIBC_2.4
00000000000010a0 T _start
0000000000004010 D __TMC_END__
00000000000011d9 t __static_initialization_and_destruction_0(int, int)
0000000000001248 W Test::Test(int&)
0000000000001248 W Test::Test(int&)
                 U std::ios_base::Init::Init()@GLIBCXX_3.4
                 U std::ios_base::Init::~Init()@GLIBCXX_3.4
0000000000004011 b std::__ioinit
natty@natty:~/test$ 