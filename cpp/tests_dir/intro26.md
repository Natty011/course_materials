/********** question 26 seif a ****************/

natty@natty:~/test$ run_gd98 intro26.cpp 
intro26.cpp: In function ‘void Foo(const X&)’:
intro26.cpp:25:23: error: ‘int X::m_a’ is private within this context
   25 |     printf("%d\n", x_.m_a);
      |                       ^~~
intro26.cpp:10:9: note: declared private here
   10 |     int m_a;
      |         ^~~
intro26.cpp: In function ‘int main()’:
intro26.cpp:30:7: error: no matching function for call to ‘X::X()’
   30 |     X x1;
      |       ^~
intro26.cpp:13:1: note: candidate: ‘X::X(int)’
   13 | X::X(int a_)
      | ^
intro26.cpp:13:1: note:   candidate expects 1 argument, 0 provided
intro26.cpp:3:8: note: candidate: ‘X::X(const X&)’
    3 | struct X
      |        ^
intro26.cpp:3:8: note:   candidate expects 1 argument, 0 provided
intro26.cpp:33:23: error: ‘int X::m_a’ is private within this context
   33 |     printf("%d\n", x1.m_a);
      |                       ^~~
intro26.cpp:10:9: note: declared private here
   10 |     int m_a;
      |         ^~~


      /**************** seif b *******************/

      natty@natty:~/test$ run_gd98 intro26.cpp 
intro26.cpp: In function ‘int main()’:
intro26.cpp:33:7: error: no matching function for call to ‘X::X()’
   33 |     X x1;
      |       ^~
intro26.cpp:13:1: note: candidate: ‘X::X(int)’
   13 | X::X(int a_)
      | ^
intro26.cpp:13:1: note:   candidate expects 1 argument, 0 provided
intro26.cpp:3:8: note: candidate: ‘X::X(const X&)’
    3 | struct X
      |        ^
intro26.cpp:3:8: note:   candidate expects 1 argument, 0 provided

/**************** c ******************************************/

