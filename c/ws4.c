/***************************************
* Autor : Natty
* Reviewr : 
* Date : 13 / 11 / 2024
* Last update: 14 / 11 / 2024
*****************************************/

#include <stdio.h>  /* putchar, getchar */
#include <assert.h> /* assert */
#include <stdlib.h> /* exit, EXIT_FAILURE, system */

typedef void (*myfunc_t)(); /* Using in ATPressedLUT() function */

/***************************function declaration**************************/

static void Test3ATPressed();
static void APrint();
static void TPrint();

void ATPressed();
void ATPressedCase();
void ATPressedLUT();
 
/********************End of function declaration**************************/

int main(void)
{  
 
   Test3ATPressed();
   
    return 0;
}

/********** ATPressed function*********/
/* Printing to stdout "A-pressed", "T-pressed" while typing A or T 
   characther respectivly, otherwise prints nothing.
   While the program is running the user won't see the typing results in
   the commend line of the shell. Escape button will finish the progrem 
   Return  Value: void.
   Note: (1) if/else implementation 
   */

void ATPressed()
{   
    char ch = 0;

    if(system("stty -icanon -echo")) /* system() Should return 0 */
    {
        exit(EXIT_FAILURE);
    }
 
    while ( ch != 27 )  /* 27 is an Escape characther*/
    {
        ch = getchar();
        
        if ( ch == 'A' )
        {   
            puts("A-pressed");
            
        }
        
        else if ( ch == 'T' )
        {
            puts("T-pressed");
        } 
    }

    if(system("stty icanon echo"))
    {
        exit(EXIT_FAILURE);
    }
    
    return;
}


/********** ATPressedCase function*********/
/* Printing to stdout "A-pressed", "T-pressed" while typing A or T 
   characther respectivly, otherwise prints nothing.
   While the program is running the user won't see the typing results in
   the commend line of the shell. Escape button will finish the progrem */
/* Return  Value: void.*/ 
/*   Note: (1) Switch case implementation */

void ATPressedCase()
{   
    char ch = 0;
    
    if(system("stty -icanon -echo")) /* system() Should return 0 */
    {
        exit(EXIT_FAILURE);
    }

    while ( ch != 27 )  /* 27 is an Escape characther*/
    {
        ch = getchar();
        switch ( ch )
        {
         case 'A':
                  puts("A-pressed");
                  break;
              
        case 'T':
                  puts("T-pressed");
                  break;

        }
    }
    
    if(system("stty icanon echo"))
    {
        exit(EXIT_FAILURE);
    }
    
    return;
}

/********** ATPressedCase function*********/
/* Printing to stdout "A-pressed", "T-pressed" while typing A or T 
   characther respectivly, otherwise prints nothing.
   While the program is running the user won't see the typing results in
   the commend line of the shell. Escape button will finish the progrem */
/* Return  Value: void.*/ 
/*   Note: (1) LUT implementation */

/********** APrint function*********/
/* An auxilery function  of ATPressedLUT() in order
   to print "A-pressed" */

static void APrint()
{
   puts("A-pressed");
   return; 
}

/********** TPrint function*********/
/* An auxilery function  of ATPressedLUT() in order
   to print "T-pressed" */

static void TPrint()
{
   puts("T-pressed");
   return; 
}

/********** ATPressedLUT function*********/
/* Printing to stdout "A-pressed", "T-pressed" while typing A or T 
   characther respectivly, otherwise prints nothing.
   While the program is running the user won't see the typing results in
   the commend line of the shell. Escape button will finish the progrem */
/* Return  Value: void.*/ 
/*   Note: (1) LUT implementation */

void ATPressedLUT()
{ 
    unsigned char ch = 0; 
    
    myfunc_t ptr_arr[256] = {NULL};
    ptr_arr[65] = APrint; 
    ptr_arr[84] = TPrint;
   
    if(system("stty -icanon -echo")) /* system() Should return 0 */
    {
        exit(EXIT_FAILURE);
    }
    
    while( ch != 27 ) /* ESC character */
    { 
        ch = getchar();  /*Get the first character */    
        if(ptr_arr[ch] != NULL) /*Not to get segmentation dump */ 
        {   
            /*Printing to stdout "A-pressed" OR "T-pressed"*/
            (*ptr_arr[ch])();
        }
    }
    if(system("stty icanon echo")) /* system() Should return 0 */
    {
        exit(EXIT_FAILURE);
    } 
 
  return;
 }
     
/********** Test3ATPressed function*********/
/* Test the ATPressed() , ATPressedCase() and ATPressedLUT() functions
   by calling them. Prints that the above functions are running */
/* Arguments: void */
/* Return value: void */

static void Test3ATPressed()
{   

    puts("'TestATPressed()' Running...");
    ATPressed();
    
    puts("'TestATPressedCase()' Running...");
    ATPressedCase();
    
    puts("'TestATPressedLUT()' Running...");
    ATPressedLUT();
    
    return;
}


