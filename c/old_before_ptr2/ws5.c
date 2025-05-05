/***************************************
* Autor : Natty
* Reviewr : 
* Date : 15 / 11 / 2024
* Last update: 16 / 11 / 2024
*****************************************/

#include <stdio.h>  /* FILE, fopen, fclose, putchar, getchar */
#include <assert.h> /* assert */
#include <stdlib.h> /* exit, EXIT_FAILURE, system */


/*************** typedef and structure declaration *************************/

typedef void (*myfunc_t)(int); /* PrintPtr */ 

/* structure   */
struct print_me
 { 
     int x;
     myfunc_t PrintPtr; 
 };

/***************End of typedef and structure declaration ******************/


/***************************function declaration**************************/
void PrintMe();
void print(int x);



/********************End of function declaration**************************/


int main(void)
{  
 
   PrintMe();
    return 0;
}

/** Print function **/
/* Print value of an int's type variable */
void print(int x)
{
    printf("%d\n", x);
    return;
}


/** PrintMe function **/
 /* Prints value of each x's struct member by 
   function pointer of other group member of 
   the same struct */
 
void PrintMe() 
{
    int i = 0;
    struct print_me printx[10]; /* An array of 10 structs of type print_me */
    
    for (i = 0; i < 10 ; ++i)
    {
       printx[i].x = 2 * i; /* Initialization */
       printx[i].PrintPtr = print; /* Initialization of each function pointer*/
        
       /* Prints the value of each x's struct member  */
       printf("x value of struct printx[%d] = ",i);
       printx[i].PrintPtr(printx[i].x);   
    }
    return;
}


