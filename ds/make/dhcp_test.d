dhcp_test.o: ../test/dhcp_test.c ../include/dhcp.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c ../test/dhcp_test.c -o  dhcp_test.o
