/******* seif a ********/
output:

natty@natty:~/test$ run_gd98 intro20.cpp 
intro20.cpp: In member function ‘X& X::operator=(const X&)’:
intro20.cpp:51:1: warning: no return statement in function returning non-void [-Wreturn-type]
   50 |         " does not change m_b:" << m_b << std::endl;
  +++ |+ return *this;
   51 | }
      | ^
this:0x7ffe8fbb1858 X default Ctor. m_a:3 m_b:4
this:0x7ffe8fbb1860 X int int Ctor. m_a:7 m_b:8
this:0x58f6929722c0 X copy Ctor. m_a:7 m_b:8
this:0x7ffe8fbb1868 X int int Ctor. m_a:9 m_b:10
this:0x7ffe8fbb1870 X copy Ctor. m_a:3 m_b:4
this:0x7ffe8fbb1858 X assignment operator. m_a:9 does not change m_b:4
this:0x58f6929722c0 X Dtor. m_a:7 m_b:8
this:0x7ffe8fbb1870 X Dtor. m_a:3 m_b:4
this:0x7ffe8fbb1868 X Dtor. m_a:9 m_b:10
this:0x7ffe8fbb1860 X Dtor. m_a:7 m_b:8
this:0x7ffe8fbb1858 X Dtor. m_a:9 m_b:4


/*------Question 21 -------------------*/
/********seif a ***********/


------Question 21 -------------------
this:0x58459a20a2e8 X default Ctor. m_a:3 m_b:4
this:0x58459a20a2f8 X default Ctor. m_a:3 m_b:4
this:0x58459a20a308 X default Ctor. m_a:3 m_b:4
this:0x58459a20a318 X default Ctor. m_a:3 m_b:4
this:0x58459a20a328 X default Ctor. m_a:3 m_b:4
this:0x58459a20a338 X default Ctor. m_a:3 m_b:4
this:0x58459a20a348 X default Ctor. m_a:3 m_b:4
this:0x58459a20a358 X default Ctor. m_a:3 m_b:4
this:0x58459a20a368 X default Ctor. m_a:3 m_b:4
this:0x58459a20a378 X default Ctor. m_a:3 m_b:4
-----Dtor of q_21 ----------------
this:0x58459a20a378 X Dtor. m_a:3 m_b:4
this:0x58459a20a368 X Dtor. m_a:3 m_b:4
this:0x58459a20a358 X Dtor. m_a:3 m_b:4
this:0x58459a20a348 X Dtor. m_a:3 m_b:4
this:0x58459a20a338 X Dtor. m_a:3 m_b:4
this:0x58459a20a328 X Dtor. m_a:3 m_b:4
this:0x58459a20a318 X Dtor. m_a:3 m_b:4
this:0x58459a20a308 X Dtor. m_a:3 m_b:4
this:0x58459a20a2f8 X Dtor. m_a:3 m_b:4
this:0x58459a20a2e8 X Dtor. m_a:3 m_b:4
-----Dtor of q_20 ----------------
this:0x58459a20a2c0 X Dtor. m_a:7 m_b:8
this:0x7ffdbf2b9520 X Dtor. m_a:3 m_b:4
this:0x7ffdbf2b9510 X Dtor. m_a:9 m_b:10
this:0x7ffdbf2b9500 X Dtor. m_a:7 m_b:8
this:0x7ffdbf2b94f0 X Dtor. m_a:9 m_b:4
natty@natty:~/test$ 



/****** seif b ******************/

-------------------------------------------
------Question 21 -------------------
this:0x55fadc4372e8 X default Ctor. m_a:3 m_b:4
this:0x55fadc4372f8 X default Ctor. m_a:3 m_b:4
this:0x55fadc437308 X default Ctor. m_a:3 m_b:4
this:0x55fadc437318 X default Ctor. m_a:3 m_b:4
this:0x55fadc437328 X default Ctor. m_a:3 m_b:4
this:0x55fadc437338 X default Ctor. m_a:3 m_b:4
this:0x55fadc437348 X default Ctor. m_a:3 m_b:4
this:0x55fadc437358 X default Ctor. m_a:3 m_b:4
this:0x55fadc437368 X default Ctor. m_a:3 m_b:4
this:0x55fadc437378 X default Ctor. m_a:3 m_b:4
-----Dtor of q_21 ----------------
this:0x55fadc4372e8 X Dtor. m_a:3 m_b:4
munmap_chunk(): invalid pointer
Aborted (core dumped)


/***************quustion 22 ****************/
/******** seif b *******************/

natty@natty:~/test$ nm intro20.out
000000000000038c r __abi_tag
0000000000004018 B __bss_start
0000000000004150 b completed.0
                 U __cxa_atexit@GLIBC_2.2.5
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
00000000000011d0 t deregister_tm_clones
0000000000001240 t __do_global_dtors_aux
0000000000003d40 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000004010 V DW.ref.__gxx_personality_v0
0000000000003d48 d _DYNAMIC
0000000000004018 D _edata
0000000000004158 B _end
0000000000001e3c T _fini
0000000000001280 t frame_dummy
0000000000003d30 d __frame_dummy_init_array_entry
0000000000002578 r __FRAME_END__
0000000000003f58 d _GLOBAL_OFFSET_TABLE_
0000000000001d6e t _GLOBAL__sub_I__ZN1XC2Ev
                 w __gmon_start__
00000000000022b8 r __GNU_EH_FRAME_HDR
                 U __gxx_personality_v0@CXXABI_1.3
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
000000000000160f T main
                 U puts@GLIBC_2.2.5
0000000000001200 t register_tm_clones
                 U __stack_chk_fail@GLIBC_2.4
00000000000011a0 T _start
0000000000004018 D __TMC_END__
                 U _Unwind_Resume@GCC_3.0
0000000000001d18 t _Z41__static_initialization_and_destruction_0ii
                 U _ZdlPv@GLIBCXX_3.4
00000000000014ba T _ZN1XaSERKS_
0000000000001340 T _ZN1XC1Eii
00000000000013fa T _ZN1XC1ERKS_
000000000000128a T _ZN1XC1Ev
0000000000001340 T _ZN1XC2Eii
00000000000013fa T _ZN1XC2ERKS_
000000000000128a T _ZN1XC2Ev
000000000000156e T _ZN1XD1Ev
000000000000156e T _ZN1XD2Ev
0000000000001e00 W _ZN1YaSERKS_
0000000000001dc8 W _ZN1YC1ERKS_
0000000000001d88 W _ZN1YC1Ev
0000000000001dc8 W _ZN1YC2ERKS_
0000000000001d88 W _ZN1YC2Ev
0000000000001da8 W _ZN1YD1Ev
0000000000001da8 W _ZN1YD2Ev
                 U _ZNSolsEi@GLIBCXX_3.4
                 U _ZNSolsEPFRSoS_E@GLIBCXX_3.4
                 U _ZNSolsEPKv@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4
                 U _Znwm@GLIBCXX_3.4
0000000000004040 B _ZSt4cout@GLIBCXX_3.4
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GLIBCXX_3.4
0000000000004151 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@GLIBCXX_3.4
natty@natty:~/test$ 

/**************************************************************/

natty@natty:~/test$ nm  -C intro20.out
000000000000038c r __abi_tag
0000000000004018 B __bss_start
0000000000004150 b completed.0
                 U __cxa_atexit@GLIBC_2.2.5
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
00000000000011d0 t deregister_tm_clones
0000000000001240 t __do_global_dtors_aux
0000000000003d40 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000004010 V DW.ref.__gxx_personality_v0
0000000000003d48 d _DYNAMIC
0000000000004018 D _edata
0000000000004158 B _end
0000000000001e3c T _fini
0000000000001280 t frame_dummy
0000000000003d30 d __frame_dummy_init_array_entry
0000000000002578 r __FRAME_END__
0000000000003f58 d _GLOBAL_OFFSET_TABLE_
0000000000001d6e t _GLOBAL__sub_I__ZN1XC2Ev
                 w __gmon_start__
00000000000022b8 r __GNU_EH_FRAME_HDR
                 U __gxx_personality_v0@CXXABI_1.3
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
000000000000160f T main
                 U puts@GLIBC_2.2.5
0000000000001200 t register_tm_clones
                 U __stack_chk_fail@GLIBC_2.4
00000000000011a0 T _start
0000000000004018 D __TMC_END__
                 U _Unwind_Resume@GCC_3.0
0000000000001d18 t __static_initialization_and_destruction_0(int, int)
                 U operator delete(void*)@GLIBCXX_3.4
00000000000014ba T X::operator=(X const&)
0000000000001340 T X::X(int, int)
00000000000013fa T X::X(X const&)
000000000000128a T X::X()
0000000000001340 T X::X(int, int)
00000000000013fa T X::X(X const&)
000000000000128a T X::X()
000000000000156e T X::~X()
000000000000156e T X::~X()
0000000000001e00 W Y::operator=(Y const&)
0000000000001dc8 W Y::Y(Y const&)
0000000000001d88 W Y::Y()
0000000000001dc8 W Y::Y(Y const&)
0000000000001d88 W Y::Y()
0000000000001da8 W Y::~Y()
0000000000001da8 W Y::~Y()
                 U std::ostream::operator<<(int)@GLIBCXX_3.4
                 U std::ostream::operator<<(std::ostream& (*)(std::ostream&))@GLIBCXX_3.4
                 U std::ostream::operator<<(void const*)@GLIBCXX_3.4
                 U std::ios_base::Init::Init()@GLIBCXX_3.4
                 U std::ios_base::Init::~Init()@GLIBCXX_3.4
                 U operator new(unsigned long)@GLIBCXX_3.4
0000000000004040 B std::cout@GLIBCXX_3.4
                 U std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)@GLIBCXX_3.4
0000000000004151 b std::__ioinit
                 U std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@GLIBCXX_3.4



/******************************************************************/

/******** seif e *******************/


natty@natty:~/test$ run_gd98 intro20.cpp 
/usr/bin/ld: /tmp/cc6DDVG6.o: in function `main':
/home/natty/test/intro20.cpp:90: undefined reference to `X::X()'
/usr/bin/ld: /tmp/cc6DDVG6.o: in function `Y::Y()':
/home/natty/test/intro20.cpp:16: undefined reference to `X::X()'
collect2: error: ld returned 1 exit status


/******** seif f, q_22 *******************/

struct Y
{

	X m_x;
	int m_i;
	Y() : m_x(5, 6), m_i(0) {}
};



natty@natty:~/test$ run_gd98 intro20.cpp 
this:0x7ffec137c790 X int int Ctor. m_a:7 m_b:8
x2.m_a:   7x2.m_b: 8 x2 address = 0x7ffec137c790
-------------------------------------------
this:0x6355748312c0 X copy Ctor. m_a:7 m_b:8
px->m_a: 7px->m_b: 8, px address = 0x6355748312c0
-------------------------------------------
this:0x7ffec137c7a0 X int int Ctor. m_a:9 m_b:10
x3.m_a:   9x3.m_b: 10 x3 address = 0x7ffec137c7a0
-------------------------------------------
-------------------------------------------
-----Dtor of q_21 ----------------
-----Dtor of q_20 ----------------
this:0x6355748312c0 X Dtor. m_a:7 m_b:8
-----------------------------------------------------
-----------------------------------------------------
-----------------Question 22 -------------------------
----------------Y y1;---------------------------
this:0x7ffec137c7b0 X int int Ctor. m_a:5 m_b:6
this:0x7ffec137c7d0 X copy Ctor. m_a:250 m_b:6
this:0x7ffec137c7f0 X int int Ctor. m_a:5 m_b:6
this:0x7ffec137c7f0 X assignment operator. m_a:250 does not change m_b:6
this:0x7ffec137c7f0 X Dtor. m_a:250 m_b:6
this:0x7ffec137c7d0 X Dtor. m_a:250 m_b:6
this:0x7ffec137c7b0 X Dtor. m_a:250 m_b:6
this:0x7ffec137c7a0 X Dtor. m_a:9 m_b:10
this:0x7ffec137c790 X Dtor. m_a:7 m_b:8
natty@natty:~/test$ 




struct X
{
	explicit X(); //Init func w/o parameters(default Ctor)
	explicit X(int a_, int b_ = 8); //Regular Ctor
	~X(); //Dtor
	X(const X& other_); // CCtor
	//X& operator=(const X& other_) = delete;//Assignment operator

	int m_a;
	int m_b; //const int m_b;
	X* xp;
};


natty@natty:~/test$ run_gd98 intro20.cpp 
this:0x7ffd5fc1b470 X int int Ctor. m_a:7 m_b:8
x2.m_a:   7x2.m_b: 8 x2 address = 0x7ffd5fc1b470
-------------------------------------------
this:0x5a509e4402c0 X copy Ctor. m_a:7 m_b:8
px->m_a: 7px->m_b: 8, px address = 0x5a509e4402c0
-------------------------------------------
this:0x7ffd5fc1b480 X int int Ctor. m_a:9 m_b:10
x3.m_a:   9x3.m_b: 10 x3 address = 0x7ffd5fc1b480
-------------------------------------------
-------------------------------------------
-----Dtor of q_21 ----------------
-----Dtor of q_20 ----------------
this:0x5a509e4402c0 X Dtor. m_a:7 m_b:8
-----------------------------------------------------
-----------------------------------------------------
-----------------Question 22 -------------------------
----------------Y y1;---------------------------
this:0x7ffd5fc1b490 X int int Ctor. m_a:5 m_b:6
this:0x7ffd5fc1b4b0 X copy Ctor. m_a:250 m_b:6
this:0x7ffd5fc1b4d0 X int int Ctor. m_a:5 m_b:6
this:0x7ffd5fc1b4d0 X Dtor. m_a:250 m_b:6
this:0x7ffd5fc1b4b0 X Dtor. m_a:250 m_b:6
this:0x7ffd5fc1b490 X Dtor. m_a:250 m_b:6
this:0x7ffd5fc1b480 X Dtor. m_a:9 m_b:10
this:0x7ffd5fc1b470 X Dtor. m_a:7 m_b:8




/**********************************************/

struct X
{
	explicit X(); //Init func w/o parameters(default Ctor)
	explicit X(int a_, int b_ = 8); //Regular Ctor
	~X(); //Dtor
	X(const X& other_); // CCtor
	//X& operator=(const X& other_) = delete;//Assignment operator

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
intro20.cpp:16:8: note: synthesized method ‘X& X::operator=(const X&)’ first required here
   16 | struct Y
      |        ^
intro20.cpp: In function ‘int main()’:
intro20.cpp:161:12: note: synthesized method ‘Y& Y::operator=(const Y&)’ first required here
  161 |         y3=y1;
      |            ^~


      