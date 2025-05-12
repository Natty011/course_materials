/******* question 29 ***********/
/********seif a: **************/

natty@natty:~/test$ run_gd98 intro29.cpp
intro29.cpp: In member function ‘X::operator int() const’:
intro29.cpp:25:16: error: ‘m_num’ was not declared in this scope
   25 |         return m_num;
      |                ^~~~~
intro29.cpp: At global scope:
intro29.cpp:28:6: error: no declaration matches ‘void X::Print()’
   28 | void X::Print()
      |      ^
intro29.cpp:11:14: note: candidate is: ‘void X::Print() const’
   11 |         void Print() const;
      |              ^~~~~
intro29.cpp:3:7: note: ‘class X’ defined here
    3 | class X
      |       ^

/********seif c: **************/
