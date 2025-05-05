producer_consumer.o: ../src/producer_consumer.c ../include/utils.h
	gcc -ansi -pedantic-errors -Wall -Wextra  -I ../include/ -g -DPRINTS -c -fPIC ../src/producer_consumer.c -o  producer_consumer.o
