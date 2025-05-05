dhcp.o: ../src/dhcp.c ../include/dhcp.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/dhcp.c -o  dhcp.o
