/******************************/
main.c with source and header of cpp
/******************************/

static copilation:
gd98 -c libcpp.cpp  -o libcpp.o
ar rcs libcpp.a libcpp.o

gd main.c libcpp.a -lstdc++ -o prog_static.out

output:
natty@natty:~/test/intro12_full_exersize_shared_object$ ./prog_static.out 
Foo from c++
Bar return: 40
global_var: 20

/******************************/

Dynamic copilation implicit:
gd98 -fPIC -c libcpp.cpp -o libcpp_dyn.o
gd98 -shared -o libcppimp.so libcpp_dyn.o
gd main.c -L. -lcppimp -lstdc++ -o prog_dyn.out
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

another option: LD_LIBRARY_PATH=. ./prog_dyn.out

./prog_dyn.out
natty@natty:~/test/intro12_full_exersize_shared_object$ ./prog_dyn.out 

output:

Foo from c++
Bar return: 40
global_var: 20


/*
-lcppimp: מקשר נגד הספרייה libcppimp.so שנמצאת בתקייה הנוכחית.

-lstdc++: מקשר נגד הספרייה הסטנדרטית של C++.

export LD_LIBRARY_PATH=.: גורם לכך שהלינקר הדינמי יוכל למצוא את הקובץ libcppimp.so בזמן ריצה.
*/

/******************************/

Dynamic copilation explicit:
gd98 -fPIC -c libcpp.cpp -o libcpp_dyn.o
gd98 -shared -o libcpp.so libcpp_dyn.o
gd main_exp.c -ldl -lstdc++ -o prog_dyn_expl.out

output:
natty@natty:~/test/intro12_full_exersize_shared_object$ ./prog_dyn_expl.out 
Foo from c++
Bar return: 40
global_var: 20


/******************************/
main.cpp with source and header of c units
/******************************/

/******************************/

static copilation:
gd -c libc.c -o libc.o
ar rcs libc.a libc.o
gd98 main_imp.cpp libc.a -o cpp_static.out

output:
natty@natty:~/test/intro12_full_exersize_shared_object$ ./cpp_static.out

Hello from C!
Add Result: 20
g_counter: 20
/******************************/

Dynamic copilation implicit:
gd -fPIC -c libc.c -o libc_dyn.o
gd -shared -o libmyc.so libc_dyn.o -lc



/******************************/

Dynamic copilation explicit:
