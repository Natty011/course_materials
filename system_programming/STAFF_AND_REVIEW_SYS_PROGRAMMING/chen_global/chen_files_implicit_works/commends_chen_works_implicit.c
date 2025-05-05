natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gc -c -fPIC foo.c -o foo.o
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 ar rcs libfoo.a foo.o
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gc -c -fPIC foo_dynamic_2.c -o foo_dynamic_2.o

natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gc -c -fPIC foo_dynamic.c -o foo_dynamic.o
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gc -shared -o libfoo_dynamic.so foo_dynamic.o libfoo.a
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gc -shared -o libfoo_dynamic_2.so foo_dynamic_2.o libfoo.a


natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$ 
gcc main.c -Wl,-rpath=. -L. -lfoo_dynamic -lfoo_dynamic_2 -o exe
main.c: In function ‘main’:
main.c:12:9: warning: implicit declaration of function ‘Foo’ [-Wimplicit-function-declaration]
   12 |         Foo();
      |         ^~~
main.c:14:9: warning: implicit declaration of function ‘Foo2’ [-Wimplicit-function-declaration]
   14 |         Foo2();
      |         ^~~~
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 ./exe
AddressOfExtern_x = 0x79378435d030
AddressOfExtern_x = 0x79378435d030
AddressOfExtern_x = 0x79378435d030



/********************************************************************************************************************************************/
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gc -shared -o libfoo_dynamic.so foo_dynamic.o libfoo.a
/usr/bin/ld: cannot find foo_dynamic.o: No such file or directory
collect2: error: ld returned 1 exit status
/********************************************************************************************************************************************/



natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gcc main.c -Wl,-rpath=. -L. -lfoo_dynamic -lfoo_dynamic_2 -o exe
main.c: In function ‘main’:
main.c:12:9: warning: implicit declaration of function ‘Foo’ [-Wimplicit-function-declaration]
   12 |         Foo();
      |         ^~~
main.c:14:9: warning: implicit declaration of function ‘Foo2’ [-Wimplicit-function-declaration]
   14 |         Foo2();
      |         ^~~~
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$ 
./exe
AddressOfExtern_x = 0x79378435d030
AddressOfExtern_x = 0x79378435d030
AddressOfExtern_x = 0x79378435d030



natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$ 
gcc main.c -Wl,-rpath=. -L. -lfoo_dynamic -o exe
main.c: In function ‘main’:
main.c:11:9: warning: implicit declaration of function ‘Foo’ [-Wimplicit-function-declaration]
   11 |         Foo();
      |         ^~~
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 ./exe
AddressOfExtern_x = 0x7d54188d2030
AddressOfExtern_x = 0x7d54188d2030



natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gcc main.c -Wl,-rpath=. -L. -lfoo_dynamic -lfoodynamic_2 -o exe
 
 
main.c: In function ‘main’:
main.c:11:9: warning: implicit declaration of function ‘Foo’ [-Wimplicit-function-declaration]
   11 |         Foo();
      |         ^~~
main.c:12:9: warning: implicit declaration of function ‘Foo2’ [-Wimplicit-function-declaration]
   12 |         Foo2();
      |         ^~~~
/usr/bin/ld: cannot find -lfoodynamic_2: No such file or directory
collect2: error: ld returned 1 exit status

natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 gcc main.c -Wl,-rpath=. -L. -lfoo_dynamic_2 -o exe
 
 
main.c: In function ‘main’:
main.c:14:9: warning: implicit declaration of function ‘Foo2’ [-Wimplicit-function-declaration]
   14 |         Foo2();
      |         ^~~~
natty@natty:~/Desktop/git_back_up/git/system_programming/global_variable/chen_files$
 ./exe
AddressOfExtern_x = 0x7314636eb030
AddressOfExtern_x = 0x7314636eb030

