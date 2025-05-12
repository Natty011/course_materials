/********** question 25 seif d ****************/

natty@natty:~/test$ run_gd98 intro25.cpp
2
0
0x6173ff765eb0
natty@natty:~/test$ run_gd98 intro25.cpp
intro25.cpp: In member function ‘void X::Bar() const’:
intro25.cpp:40:9: error: assignment of member ‘X::m_a’ in read-only object
   40 |     m_a = 0;    // ---1--- not legal
      |     ~~~~^~~
natty@natty:~/test$ run_gd98 intro25.cpp
intro25.cpp: In member function ‘void X::Bar() const’:
intro25.cpp:41:9: error: assignment of member ‘X::m_p’ in read-only object
   41 |     m_p = 0;    // ---2--- not legal
      |     ~~~~^~~
natty@natty:~/test$ run_gd98 intro25.cpp
2
0
0x5d69c6cdbeb0
natty@natty:~/test$ run_gd98 intro25.cpp
2
0
0x5e2f4a097eb0
natty@natty:~/test$ run_gc98 intro25.cpp
2
0
0x573702281eb0
natty@natty:~/test$ run_gd98 intro25.cpp
2
0
0x5d56d32e1eb0
natty@natty:~/test$ vlg ./intro25.cpp
valgrind: ./intro25.cpp: Permission denied
natty@natty:~/test$ vlg ./intro25.out
==69963== Memcheck, a memory error detector
==69963== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==69963== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==69963== Command: ./intro25.out
==69963== 
2
0
0x4de1c80
==69963== 
==69963== HEAP SUMMARY:
==69963==     in use at exit: 0 bytes in 0 blocks
==69963==   total heap usage: 3 allocs, 3 frees, 73,732 bytes allocated
==69963== 
==69963== All heap blocks were freed -- no leaks are possible
==69963== 
==69963== For lists of detected and suppressed errors, rerun with: -s
==69963== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
natty@natty:~/test$ run_gd98 intro25.cpp
intro25.cpp: In member function ‘void X::Foo()’:
intro25.cpp:30:12: error: decrement of read-only location ‘*((X*)this)->X::m_p’
   30 |         --(*m_p);
      |           ~^~~~~
intro25.cpp: In member function ‘void X::Bar() const’:
intro25.cpp:42:10: error: assignment of read-only location ‘*(const int*)((const X*)this)->X::m_p’
   42 |     *m_p = 0;   // ---3--- not legal
      |     ~~~~~^~~
natty@natty:~/test$ run_gd98 intro25.cpp
intro25.cpp: In member function ‘void X::Bar() const’:
intro25.cpp:44:8: error: passing ‘const X’ as ‘this’ argument discards qualifiers [-fpermissive]
   44 |     Foo();      // ---5--- can't call to non const function
      |     ~~~^~
intro25.cpp:27:6: note:   in call to ‘void X::Foo()’
   27 | void X::Foo()
      |      ^
natty@natty:~/test$ run_gd98 intro25.cpp
2
0
0x5b42b0e4beb0
natty@natty:~/test$ run_gd98 intro25.cpp
intro25.cpp: In function ‘void Fifi(const X&)’:
intro25.cpp:49:11: error: passing ‘const X’ as ‘this’ argument discards qualifiers [-fpermissive]
   49 |     x_.Foo();   // ---4---  forbiden cause Foo is non const function
      |     ~~~~~~^~
intro25.cpp:27:6: note:   in call to ‘void X::Foo()’
   27 | void X::Foo()
      |      ^
natty@natty:~/test$ run_gd98 intro25.cpp
intro25.cpp: In function ‘void Fifi(const X&)’:
intro25.cpp:49:11: error: passing ‘const X’ as ‘this’ argument discards qualifiers [-fpermissive]
   49 |     x_.Foo();   // ---4---  forbiden cause Foo is non const function
      |     ~~~~~~^~
intro25.cpp:27:6: note:   in call to ‘void X::Foo()’
   27 | void X::Foo()
      |      ^
natty@natty:~/test$ 