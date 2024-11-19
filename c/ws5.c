/***************************************
* Autor : Natty
* Reviewr : Idan
* Date : 15 / 11 / 2024
* Last update: 17 / 11 / 2024
*****************************************/

#include <stdio.h> /* stdin, stdout, FILE, fopen, fclose, fputs,
                      feof, fgets, rename */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <string.h> /* strcpy, strcmp */ 

#define N 5
#define MAXLETTERS 100

/*************** typedef and structure declaration *************************/
/*************** 1st qeustion *************************/
typedef void (*myfunc_t)(int); /* PrintPtr */ 

/* structure   */
struct print_me
 { 
     int x;
     myfunc_t PrintPtr; 
 };

/*************** 2nd qeustion *************************/
typedef enum
{ 

	REMOVE, 
	COUNT, 
	EXIT, 
	ADD_FIRST, 
	ADD_LAST
	
} op_type;


typedef int (*comper_t)(char* str, char* special);
typedef op_type (*operation_t) ( char* filename, char* str);

/* structure   */
typedef struct 
 { 
     char command[10]; /* get the special strings for comparison*/
     comper_t compare;
     operation_t oprate; 
 }operator_t;
 
/***************End of typedef and structure declaration ******************/
 
/***************************function declaration**************************/

/*************** 1st qeustion *************************/
void PrintMe();
void print(int x);

/*************** 2nd qeustion *************************/
void LoggerCall(int argc, char* argv[]);
void Logger ( char* file_name );
void InitArrays ( operator_t operators[] );
int SimpleCompare ( char* input , char* command );
int IsAddLast ( char* input , char* command );
int IsAddFirst ( char* input , char* command );

op_type Remove ( char* filename, char* str );
op_type Exit ( char* filename, char* str );
op_type Count (char* filename, char* str );
op_type AddLast (char* filename, char* str );
op_type AddFirst (char* filename, char* str );

/********************End of function declaration**************************/

int main ( int argc , char* argv[] )
{
	

  /*************** 1st qeustion *************************/
  puts("");
  puts("Test of the 1st qeustion:");
  PrintMe();
	
  /*************** 2nd qeustion *************************/
  puts("");
  puts("Test of the 2nd qeustion:");	
  LoggerCall(argc, argv);
	
  return 0;
}

  /*************** 2nd qeustion *************************/	
  /* LoggerCall function */
  /* Call to Logger in order to handle a file from the user */
   
void LoggerCall(int argc, char* argv[])
{
   char* file_name = NULL;

   if (argc < 2)
   {
        printf("Missing File\n");
        return;
   }
   
	file_name = argv[1];
	
	Logger ( file_name );
	
	return;
}   
   
/* Logger function that handle entry file  from the user*/

void Logger (char* file_name )
{
    operator_t operators[N];
	op_type action = ADD_LAST;
	char input[MAXLETTERS] = {0};
	
	size_t i = 0;
	
	InitArrays ( operators );

	while ( action != EXIT &&  action != REMOVE )
	{
	 	printf( "Enter a line:\n" );
   	 	fgets(input, MAXLETTERS, stdin); 
   		
		for (i = 0 ; i < N ; ++i)
		{
			if ( operators[i].compare ( input , operators[i].command ) )
			{
				action = operators[i].oprate( file_name , input );
				break;
			}
		}
	}
	
}

/* Initialization of the array of the Logger's functions*/

void InitArrays ( operator_t operators[] )
{

	char* special[] = { "-remove\n", "-exit\n" , "-count\n", "<" , ""};
	comper_t compare_functions[] = {SimpleCompare ,SimpleCompare,
	                                 SimpleCompare, IsAddFirst , IsAddLast};
	operation_t operte_function[] = {Remove , Exit , Count, AddFirst , AddLast};   
	size_t i = 0;
	
	for( i = 0 ; i < N ; ++i)
	{
		strcpy(operators[i].command , special[i]);
		operators[i].compare = compare_functions[i];
		operators[i].oprate = operte_function[i];
	}
}
/* Chack for "-remove\n", "-exit\n" , "-count\n" */
int SimpleCompare ( char* input , char* command )
{
	if ( strcmp( input , command ) == 0 )
	{
		return 1;
	}
	
	return 0;
}
/* Chack for adding to the end of the file */
int IsAddLast ( char* input , char* command )
{
	return 1;
}

int IsAddFirst ( char* input , char* command )
{
	if ( (*input == '<') )
	{
		return 1;
	}
	
	return 0;
}

/* Remove the file */
op_type Remove ( char* filename, char* str )
{
	remove(filename); 
	return REMOVE;                   
}

op_type Exit ( char* filename, char* str )
{
  	return EXIT;       
}

/* Counts the lines' number */
op_type Count (char* filename, char* str )
{
	char buffer[MAXLETTERS] = { 0 };
	size_t count = 0;
	FILE* file = fopen(filename, "r");
	
	if (file == NULL)
	{
         printf("Failed to open the file\n");
         exit(EXIT_FAILURE);
    }
	
 	 while ( fgets(buffer, MAXLETTERS, file) )
 	 {
 	    if (!feof(file))
           {
              count++;
           }
 	 } 
 	 printf("%lu lines\n", count);
 	 fclose(file);

	return COUNT;
}

/* Append to the End of the file */
op_type AddLast (char* filename, char* str )
{
    FILE* file = fopen(filename, "a");
    if (file == NULL)
	{
         printf("Failed to open the file\n");
         exit(EXIT_FAILURE);
    } 
    fputs(str, file); /* put the string in the file that user opened */
    fclose(file);
    return ADD_LAST;
}

/* Append to the start of the file */
op_type AddFirst (char* filename, char* str )
{
    char buffer[MAXLETTERS] = { 0 };
    FILE* file = fopen(filename, "a+"); 
    FILE* file_temp = fopen("temp_file", "a+");
    
    if (file == NULL)
	{
         printf("Failed to open the file\n");
         exit(EXIT_FAILURE);
    } 
    
    fputs(str + 1, file_temp); /* put the string in the temp file  */
    rewind(file);
    while ( fgets(buffer, MAXLETTERS, file) )
 	 {
 	    if (!feof(file)) /* Copy the lines' file to the temp_file */
           {
             fputs(buffer, file_temp); 
           }
    }
    
    rename("temp_file", filename);
    fclose(file);
    fclose(file_temp); /* Must close pointer file, otherwise it is reachable */
    return ADD_FIRST;
}


/** Print function **/
/* Print value of an int's type variable */
void print(int x)
{
    printf("%d\n", x);
    return;
}

  /*************** 1st qeustion *************************/

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



