natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 gc -c -fPIC foo.c -o foo.o
natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 ar rcs libfoo.a foo.o
natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 gc -c -fPIC foo_dynamic.c -o foo_dynamic.o
natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 gc -c -fPIC foo_dynamic_2.c -o foo_dynamic_2.o
natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 gc -shared -o libfoo_dynamic.so foo_dynamic.o libfoo.a
natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 gc -shared -o libfoo_dynamic_2.so foo_dynamic_2.o libfoo.a
natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 gcc main.c -L. -lfoo -o exe
natty@natty:~/Desktop/git_back_up/git/system_programming/chen_global$
 ./exe
AddressOfExtern_x = 0x77fbbf6d4030
AddressOfExtern_x = 0x77fbbf6cf030
AddressOfExtern_x = 0x5f83d5217010

