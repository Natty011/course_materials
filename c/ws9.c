/***************************************
* Author : Natty
* Reviewer : Natan
* Date : 25 / 11 / 2024
* Last update: 27 / 11 / 2024
*****************************************/

#include <stdio.h> /* printf, fputs, puts, sprinf, fgets, feof, rewind */
#include <stdlib.h> /* malloc, realloc, free, atoi, atof */
#include <string.h> /* strcat, strcpy, strlen, strncpy */
#include <assert.h> /* assert */
#define LEN_NAME 20
#define LEN_SURNAME 20
#define MAX_CHAR 30 /* For char array buffer */
#define EPSILON 0.000001 /* to compare the float number after loading */
#define ABS(a, b) (((a) > (b)) ? ((a)-(b)) : -((a)-(b)))

/*************** typedef and structure declaration *************************/

typedef struct RealGrade
{
	unsigned int grd_re;
	
}real_grade_t;



typedef struct Humanistic
{
	unsigned int grd_h;
	
}humanistic_t;


typedef struct Grades
{
	humanistic_t grd_human;
	real_grade_t grd_real;
	float grd_sport;
	
}grade_t;

/*** Save Student ***/
typedef struct Student
{
	char name[LEN_NAME];
	char surname[LEN_SURNAME];
	grade_t grade;
	

}student_t, *p_student_t;

/***************End of typedef and structure declaration ******************/

/***************************function declaration**************************/

p_student_t CreateDataBaseStd(p_student_t p_std);
p_student_t InitStdEmpty(p_student_t p_std); 

char* StrnCpy(char *dest, const char *src, size_t n);
char* RemoveNewLineAddNull( char* str );
char* StudentFullName( p_student_t p_std, char temp_str[MAX_CHAR] );

FILE* FillDataBaseStudent(FILE* file, p_student_t p_std);
FILE* ExtractDataBaseStudent(FILE* file, p_student_t p_std);

p_student_t SaveStudentDataBase(p_student_t p_std);
p_student_t LoadStudentDataBase(p_student_t p_std, char* fullname);

static void TestSaveAndLoadStudent(p_student_t p_std_s, p_student_t p_std_l);
/***************************End of function declaration******************/

int main ()
{

   p_student_t p_std1 = NULL;
   p_student_t p_std2 = NULL;
   
   puts("=====================================================");
   puts("'TestSaveAndLoadStudent(p_std1, p_std2)'");
   puts("-----------------------------------------------------");
   
   p_std1 = CreateDataBaseStd(p_std1);/*Dinamic allocation, must to free @end*/
   /* THE data of The student that need to be save*/
   strcpy(p_std1->name, "Natty");
   strcpy(p_std1->surname, "Levi");
   p_std1->grade.grd_human.grd_h = 87;
   p_std1->grade.grd_real.grd_re = 93;
   p_std1->grade.grd_sport = 87.587462;
   
   p_std1 = SaveStudentDataBase(p_std1);
   

   /* THE data of The student that need to be load to the student's struct*/
   p_std2 = CreateDataBaseStd(p_std2);/*Dinamic allocation, must to free @end*/
   p_std2 = LoadStudentDataBase(p_std2, "Natty Levi");/*Load from the file */
   /* Test the results of the members' structs */
   
   TestSaveAndLoadStudent(p_std1, p_std2);
   puts("=====================================================");
   
  /*  Dont forget to free the allocation */
    free(p_std1);
    free(p_std2);
	return 0;
}
/* Compare the loading and the saving data base */
static void TestSaveAndLoadStudent(p_student_t p_std_s, p_student_t p_std_l)
{
   
   if(strcmp(p_std_s->name, p_std_l->name))
   {
       printf("Failed load the name\n");
   }
   
   if(strcmp(p_std_s->surname, p_std_l->surname))
   {
       printf("Failed load the surname\n");
   }
   
   if(p_std_s->grade.grd_human.grd_h != p_std_l->grade.grd_human.grd_h)
   {
       printf("Failed load the human grade\n");
   }
   
   if(p_std_s->grade.grd_real.grd_re != p_std_l->grade.grd_real.grd_re)
   {
       printf("Failed load the real grade\n");
   }
   
   if(!(EPSILON >= ABS(p_std_s->grade.grd_sport, p_std_l->grade.grd_sport)))
   {
       printf("Failed load the sport grade\n");
   }
   
   printf("The loading pass Successfully \n");
   
   return;
} 

/* Loading the data base to the struct */ 
p_student_t LoadStudentDataBase(p_student_t p_std, char* fullname)
{
    FILE* file = fopen(fullname, "rb");
    
    if (file == NULL)
    {
       printf("Failed to open the file\n");
       exit(EXIT_FAILURE);
    }
    
    file = ExtractDataBaseStudent(file, p_std);
    
    
    
    if( 0 != fclose(file)  )
    {
       printf("Failed to close the file\n");
       exit(EXIT_FAILURE);
    }
    
   return p_std;

}

/* Extract the data base to the sturct's members*/
FILE* ExtractDataBaseStudent(FILE* file, p_student_t p_std)
{
    char temp_str[MAX_CHAR] = { 0 };
    p_std = InitStdEmpty(p_std);
    rewind(file);
    
    /* Not to get warning of unused return value*/
    if(!fgets(temp_str, MAX_CHAR, file)){} 
    RemoveNewLineAddNull(temp_str);
    StrnCpy(p_std->name, temp_str,strlen(temp_str) + 1 ); /* with '\0' */

    if(!fgets(temp_str, MAX_CHAR, file)){} 
    RemoveNewLineAddNull(temp_str);
    StrnCpy(p_std->surname, temp_str,strlen(temp_str) + 1 );  

    if(!fgets(temp_str, MAX_CHAR, file)){} 
    RemoveNewLineAddNull(temp_str);
    p_std->grade.grd_human.grd_h = atoi(temp_str);

    if(!fgets(temp_str, MAX_CHAR, file)){} 
    RemoveNewLineAddNull(temp_str);
    p_std->grade.grd_real.grd_re = atoi(temp_str);

    if(!fgets(temp_str, MAX_CHAR, file)){} 
    RemoveNewLineAddNull(temp_str);
    p_std->grade.grd_sport = atof(temp_str);

    if(!fgets(temp_str, MAX_CHAR, file)){} 
    if (feof(file)) 
    {
        puts("End of file is reached successfully");
    }
    
    return file;

}

 /*  Save Data Base of the student*/ 
p_student_t SaveStudentDataBase(p_student_t p_std)
{
    char temp_str[MAX_CHAR] = { 0 };
    char* fullname = StudentFullName( p_std,  temp_str);
    FILE* file = fopen(fullname, "wb");

    if (file == NULL)
    {
       printf("Failed to open the file\n");
       exit(EXIT_FAILURE);
    }
    
    file = FillDataBaseStudent(file, p_std);
    
    if( 0 != fclose(file)  )
    {
       printf("Failed to close the file\n");
       exit(EXIT_FAILURE);
    }
    
   return p_std;
} 

/* Fill the data base from the sturct's members*/
FILE* FillDataBaseStudent(FILE* file, p_student_t p_std)
{

   char temp_str[MAX_CHAR] = { 0 };
   
   strcpy(temp_str, p_std->name); /* Copy the string */
   strcat( temp_str , "\n"); /* new line for the file */
   fputs(temp_str, file); /* put the string in the file that user opened */

   strcpy(temp_str, p_std->surname);
   strcat( temp_str , "\n"); 
   fputs(temp_str, file);
   
   /* Convert integer to string */
   sprintf(temp_str, "%d", p_std->grade.grd_human.grd_h);  
   strcat( temp_str , "\n"); 
   fputs(temp_str, file);
   

   sprintf(temp_str, "%d", p_std->grade.grd_real.grd_re);  
   strcat( temp_str , "\n"); 
   fputs(temp_str, file);
   
   /* Convert float to string */
   sprintf(temp_str, "%f", p_std->grade.grd_sport); 
   strcat( temp_str , "\n"); 
   fputs(temp_str, file);

   return file;
}

/* Create a string of the student full name and using it as
   a name of the file itself */
    
char* StudentFullName( p_student_t p_std, char temp_str[MAX_CHAR] )
{

    strcpy(temp_str, p_std->name); 
    strcat( temp_str , "_"); /* Concatenating 'underscore' for surname */
    strcat( temp_str , p_std->surname); 
    
    return temp_str;
}  
 
/* Allocate memory for Struct Student*/
p_student_t CreateDataBaseStd(p_student_t p_std)
{
   p_std = (p_student_t)malloc(sizeof(student_t));
   assert(p_std);
   
   return p_std;
   
}

/*  Initialization the DataBase Student to an empty data*/ 
p_student_t InitStdEmpty(p_student_t p_std)
{

   strcpy(p_std->name, "                   "); /*  20 spaces */
   strcpy(p_std->surname, "                   "); /*  20 spaces */
   p_std->grade.grd_human.grd_h = 0;
   p_std->grade.grd_real.grd_re = 0;
   p_std->grade.grd_sport = 0.0;
   
    return p_std;
}

/**********StrnCpy function*********/
/* Copy "n" first characters from src to dest string */
/* Arguments:  */
/* Return value: Pointer to the dest string */

char *StrnCpy(char *dest, const char *src, size_t n)
{
 
    char* p = dest;
    size_t i = 0;

    assert(dest);
    assert(src);

    while ( i < n && *(src + i))
    {
       *(p +i) = *(src + i);
       i++;
    }
    /*To  add '\0' if necessary*/
    /*Do not overwrite data after arriving to dest array null char control*/
    while ( i != n && *(p + i) ) 
    {
       *(p +i) = '\0';
       i++;
    }
    
    return dest;
}

/* Must not to copy back the new line characther '\n', 
   and should replace it with a null termination characther '\0' */
char* RemoveNewLineAddNull( char* str )
{
    size_t i = 0;
    while( *(str + i) != '\n' ) 
    {
        ++i;
    }
    *(str + i) = '\0';
    return str;
}




