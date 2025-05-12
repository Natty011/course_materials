/******* seif a**********/
nm intro16.out with calling to functions:
natty@natty:~/test$ nm intro16.out 
000000000000038c r __abi_tag
0000000000004010 B __bss_start
0000000000004150 b completed.0
                 U __cxa_atexit@GLIBC_2.2.5
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
0000000000001190 t deregister_tm_clones
0000000000001200 t __do_global_dtors_aux
0000000000003d60 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003d68 d _DYNAMIC
0000000000004010 D _edata
0000000000004158 B _end
0000000000001484 T _fini
0000000000001240 t frame_dummy
0000000000003d50 d __frame_dummy_init_array_entry
00000000000021f4 r __FRAME_END__
0000000000003f68 d _GLOBAL_OFFSET_TABLE_
00000000000013c6 t _GLOBAL__sub_I_main
                 w __gmon_start__
0000000000002020 r __GNU_EH_FRAME_HDR
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
0000000000001249 T main
00000000000011c0 t register_tm_clones
                 U __stack_chk_fail@GLIBC_2.4
0000000000001160 T _start
0000000000004010 D __TMC_END__
000000000000145b W _Z3MaxIcET_S0_S0_
00000000000013ff W _Z3MaxIdET_S0_S0_
00000000000013df W _Z3MaxIiET_S0_S0_
0000000000001435 W _Z3MaxIPiET_S1_S1_
0000000000001370 t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSolsEd@GLIBCXX_3.4
                 U _ZNSolsEi@GLIBCXX_3.4
                 U _ZNSolsEPFRSoS_E@GLIBCXX_3.4
                 U _ZNSolsEPKv@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4
0000000000004040 B _ZSt4cout@GLIBCXX_3.4
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GLIBCXX_3.4
0000000000004151 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@GLIBCXX_3.4
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@GLIBCXX_3.4

natty@natty:~/test$ nm intro16.out | grep Max
000000000000145b W _Z3MaxIcET_S0_S0_
00000000000013ff W _Z3MaxIdET_S0_S0_
00000000000013df W _Z3MaxIiET_S0_S0_
0000000000001435 W _Z3MaxIPiET_S1_S1_
natty@natty:~/test$ 

/**********************************************************/
without calling to functions:

natty@natty:~/test$ nm intro16.out 
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
0000000000001230 T _fini
0000000000001180 t frame_dummy
0000000000003d88 d __frame_dummy_init_array_entry
0000000000002130 r __FRAME_END__
0000000000003fa0 d _GLOBAL_OFFSET_TABLE_
0000000000001215 t _GLOBAL__sub_I_main
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
00000000000011bf t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4
0000000000004011 b _ZStL8__ioinit


natty@natty:~/test$ nm intro16.out | grep Max
natty@natty:~/test$ 


/******* seif b**********/
add:
	std::cout << Max<float>(5.1f, 4.9f ) << std::endl;
	std::cout << Max<std::string>("Hello", "World" ) << std::endl;

natty@natty:~/test$ nm intro16.out | grep Max
0000000000001720 W _Z3MaxIcET_S0_S0_
00000000000016c4 W _Z3MaxIdET_S0_S0_
0000000000001747 W _Z3MaxIfET_S0_S0_
00000000000016a4 W _Z3MaxIiET_S0_S0_
0000000000001772 W _Z3MaxINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_S6_S6_
00000000000016fa W _Z3MaxIPiET_S1_S1_


if the operator <operator> doesn't exist:

natty@natty:~/test$ run_gd98 intro16.cpp 
intro16.cpp: In function ‘int main()’:
intro16.cpp:20:31: error: no matching function for call to ‘Max<void>(int [12], int*)’
   20 |         std::cout << Max<void>(arr, arr + 8 ) << std::endl;
      |                      ~~~~~~~~~^~~~~~~~~~~~~~~
intro16.cpp:4:3: note: candidate: ‘template<class T> T Max(T, T)’
    4 | T Max(T t1, T t2)
      |   ^~~
intro16.cpp:4:3: note:   template argument deduction/substitution failed:
intro16.cpp: In substitution of ‘template<class T> T Max(T, T) [with T = void]’:
intro16.cpp:20:24:   required from here
intro16.cpp:4:3: error: invalid parameter type ‘void’
intro16.cpp:4:3: error: in declaration ‘T Max(T, T)’
natty@natty:~/test$ 


/*********** seif c **************************************/

natty@natty:~/test$ nm intro16.out | grep Max
0000000000001720 W _Z3MaxIcET_S0_S0_
00000000000016c4 W _Z3MaxIdET_S0_S0_
0000000000001747 W _Z3MaxIfET_S0_S0_
00000000000016a4 W _Z3MaxIiET_S0_S0_
0000000000001772 W _Z3MaxINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_S6_S6_
00000000000016fa W _Z3MaxIPiET_S1_S1_

/*********************************/
natty@natty:~/test$ nm intro16c.out | grep Max
0000000000001720 W _Z3MaxIcET_S0_S0_
00000000000016c4 W _Z3MaxIdET_S0_S0_
0000000000001747 W _Z3MaxIfET_S0_S0_
00000000000016a4 W _Z3MaxIiET_S0_S0_
0000000000001772 W _Z3MaxINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_S6_S6_
00000000000016fa W _Z3MaxIPiET_S1_S1_

if didn't call to template functions: won't include the symbols

natty@natty:~/test$ nm intro16c.out | grep Max
natty@natty:~/test$ 


/*********** seif e **************************************/


natty@natty:~/test$ run_gd98 intro16.cpp 
intro16.cpp: In function ‘int main()’:
intro16.cpp:9:9: error: ‘x’ was not declared in this scope
    9 |         x =5;
      |         ^
intro16.cpp:7:13: warning: unused variable ‘arr’ [-Wunused-variable]
    7 |         int arr[12];
      |             ^~~
natty@natty:~/test$ run_gd98 intro16.cpp 
intro16.cpp: In function ‘int main()’:
intro16.cpp:9:9: error: ‘x’ was not declared in this scope
    9 |         x =5;
      |         ^
intro16.cpp:7:13: warning: unused variable ‘arr’ [-Wunused-variable]
    7 |         int arr[12];
      |             


/*********** seif e.3 **************************************/

      natty@natty:~/test$ run_gd98 intro16.cpp 
In file included from intro16.cpp:2:
intro16.hpp: In function ‘T Max(T, T)’:
intro16.hpp:9:5: error: ‘x’ was not declared in this scope
    9 |     x =5;
      |     ^
intro16.cpp: In function ‘int main()’:
intro16.cpp:7:13: warning: unused variable ‘arr’ [-Wunused-variable]
    7 |         int arr[12];


/**********************************************/
no compiled:
std::cout<<Max(3, 5.5) << " \n" ;

    natty@natty:~/test$ run_gd98 intro16.cpp 
intro16.cpp: In function ‘int main()’:
intro16.cpp:14:23: error: no matching function for call to ‘Max(int, double)’
   14 |         std::cout<<Max(3, 5.5) << " \n" ;
      |                    ~~~^~~~~~~~
In file included from intro16.cpp:2:
intro16.hpp:6:3: note: candidate: ‘template<class T> T Max(T, T)’
    6 | T Max(T t1, T t2)
      |   ^~~
intro16.hpp:6:3: note:   template argument deduction/substitution failed:
intro16.cpp:14:23: note:   deduced conflicting types for parameter ‘T’ (‘int’ and ‘double’)
   14 |         std::cout<<Max(3, 5.5) << " \n" ;
      |  

 	
compiled: explicit conversion:      
std::cout<<Max(3, (int)5.5) << " \n" ;
     