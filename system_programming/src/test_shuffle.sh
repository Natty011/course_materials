#!/bin/bash

# קומפילציה
gcc -Wall -Wextra -pedantic -ansi -g shuffle_sort.c -I ../include -o shuffle_sort.out

# הרצה רגילה עם הפניית פלט
./shuffle_sort.out /usr/share/dict/words > log.txt 2>&1
echo "פלט שמור ב־log.txt"

# הרצה עם valgrind
valgrind --leak-check=full --track-origins=yes ./shuffle_sort.out /usr/share/dict/words > valgrind_out.txt 2>&1
echo "valgrind_out.txt נשמר"

#chmod +x test_shuffle.sh
