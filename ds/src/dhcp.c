/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 26 / 02 / 2025
* Last update: 02 / 03 / 2025
*****************************************/
/*#define PRINTS*/
#ifdef PRINTS
	#include <stdio.h> /* printf */
#endif
#include <stdint.h>
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include <string.h> 	/* strcat */
#include <ctype.h>      /* tolower*/
#include "dhcp.h"

/* #include "bit_array.h" */

#define UNUSED( var )       ( (void)var )
#define BYTE_SIZE			( 8 )
#define BASE				( 2 )
#define MAX_SIZE			( 33 )


/************************************************************/
/********************  lut_knight_moves**********************/
/************************************************************/

typedef uint8_t ip_addrs_t[4];
/******************************************************************************/
/***************************** Success / Fail Enum ****************************/
/******************************************************************************/


typedef enum
{
	ZERO_CHAR = 48,
	ONE_CHAR = 49

} char_represents_t;

typedef enum
{
	SUCCESS = 0,
	FAIL = 1,
	REQUEST_NOT_MET = 2

} result_t;

/******************************************************************************/
/******************************* True / False Enum ****************************/
/******************************************************************************/

typedef enum
{
	FALSE = 0,
	TRUE = 1
} op_result_t;

typedef enum
{
	LEFT = 0,
	RIGHT = 1,
	num_of_childs
} child_t;

/******************************************************************************/
/***************************** Management struct ******************************/

typedef struct dhcp_node
{
	struct dhcp_node *child[num_of_childs];
	struct dhcp_node *parent;
	int is_occupied;

}dhcp_node_t;


struct dhcp
{
	dhcp_node_t *root;
	char *ip;
	size_t bits_num_in_subnet;

};

/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/

static void RecDHCPDestroy(dhcp_node_t *root);
static dhcp_node_t *CreateNode(dhcp_node_t *parent );


static int AtoiUpTo36Base(const char *str, int base);
static char* ItoaUpTo36Base(int n, char* str, int base);
static const char* WhiteSpacesSkip(const char *nptr);
static void ReverseStr(char* str);
static int Atoi10Base(const char *nptr);
static char* Itoa10Base(int n, char* str);
static char *ItoaTo2Base(dhcp_t* dhcp, char *dest, 
					const ip_addrs_t requested_ip );

#ifdef PRINTS
#endif

/******************************************************************************/
/*******************End Of Static Functions declartions************************/
/******************************************************************************/

/******************************************************************************/

/************************************************************/
/********************  DHCPCreate  *************************/
/************************************************************/
dhcp_t *DHCPCreate(const unsigned char subnet_ip[BYTES_IN_IP],
                           size_t bits_num_in_subnet)
{
	dhcp_t *dhcp_ptr = NULL;
	dhcp_node_t *root = NULL;
	char *prefix_ip = NULL;
	/*uint8_t i = 0;*/
	/*uint32_t *ptr = NULL;*/
	/*const uint8_t *test = NULL;*/
	/*ip_addrs_t ip1 = {192, 168, 3, 5};*/
	/*test = (const uint8_t*)ip1;*/
	/*puts((char*)test );*/
	/*ptr = (uint32_t*)ip1;*/
	/*puts((char*)ptr + 1);*/
	/*printf(" %u \n ", *((uint8_t*)ptr + 1 ));*/
	/*printf(" %u \n ", *(test + 2) );*/

	dhcp_ptr = (dhcp_t*)malloc( sizeof(dhcp_t) );

	if( NULL == dhcp_ptr )
	{
		return NULL;
	}

	root = (dhcp_node_t*)malloc( sizeof( dhcp_node_t) );

	if( NULL == root )
	{
		free( dhcp_ptr );
		dhcp_ptr = NULL;
		return NULL;
	}

	prefix_ip = (char*)malloc( sizeof(char*) * MAX_SIZE );

	if( NULL == prefix_ip )
	{
		free( root );
		root = NULL;
		
		free( dhcp_ptr );
		dhcp_ptr = NULL;

		return NULL;
	}

	root->child[LEFT] = root->child[RIGHT] = NULL;
	root->is_occupied = FALSE;
	root->parent = NULL;

	dhcp_ptr->root = root; 
	dhcp_ptr->bits_num_in_subnet = bits_num_in_subnet;

	ItoaTo2Base(dhcp_ptr, prefix_ip, subnet_ip)	;
	/*
	for( i = 0; i < BYTES_IN_IP; ++i )
	{

		ItoaUpTo36Base(subnet_ip[i],
			prefix_ip + (i * BYTE_SIZE) , BASE); 

	}

	*(prefix_ip + bits_num_in_subnet) = '\0';

	*/
	

	dhcp_ptr->ip = prefix_ip;

	puts(dhcp_ptr->ip);

	return dhcp_ptr;
}						   
/*
int DHCPAllocateIP(dhcp_t* dhcp,
	const unsigned char requested_ip[BYTES_IN_IP],
	unsigned char ret_allocated_ip[BYTES_IN_IP])
{


}
*/

/************************************************************/
/********************  DHCPDestroy  *************************/
/************************************************************/

void DHCPDestroy(dhcp_t* dhcp)
{
	if( NULL != dhcp )
	{
		RecDHCPDestroy(dhcp->root);
		dhcp->root = NULL;

		free(dhcp->ip);
		dhcp->ip = NULL;

		free(dhcp);
		dhcp = NULL;

	}
}


	
/************************************************************/
/*************  Static Functions definition  ****************/
/************************************************************/


/************************************************************/
/************** ItoaUpTo36Base function definition *********/
/************************************************************/
/* 
   DESCRIPTION: Converts an integer value to a null-terminated string
                using the specified base and stores the result in the
                array given by str parameter.

   RETURN VALUE: A pointer to the resulting null-terminated string,
                  same as parameter str.
                  
    NOTE: 1) If base is 10 and value is negative, the resulting string is
            preceded with a minus sign (-). With any other base,
            value is always considered unsigned.   
         
          2) Numerical base used to represent the value as a string,
             between 2 and 36, where 10 means decimal base,
             16 hexadecimal, 8 octal, and 2 binary.

*/


/************************************************************/
/********************  ItoaUpTo36Base ***********************/
/************************************************************/

static char* ItoaUpTo36Base(int n, char* str, int base)
{

	int remainder = 0;
	char* pstr = str;
	size_t count = 0, i = 0;

	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	
	if (  (base > 36) || (base < 2) )
	{
	   puts("Invalid base value");
	   return str;
	}

	if( n <= 0 )
	{
		if ( n == 0)
		{
			for(i = 0; i < 8 ; ++i)
			{
				*( str+i )= '0';
			}
			*(str +i) = '\0';
			return str; 
		}
		else if ((n < 0) && ( base == 10) )
		{
			return Itoa10Base( n, str);
		}
		
		else
		{
			n = -n;
		}
	}
	/* The base isn't negative decimal */
	while( n )
	{
		remainder = n % base;
		*str++ = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
		n = n / base;
		++count;
	}
	*str = '\0'; 

	if( BYTE_SIZE - count != 0)
	{
		str = strncat(str, "00000000", BYTE_SIZE - count); /*8 - count */
	}
	

	ReverseStr(pstr);

	return pstr;	
}



/************************************************************/
/*********** AtoiUpTo36Base function definition *************/
/************************************************************/
/* 
   DESCRIPTION: The AtoiUpTo36Base() function converts the initial 
                part of the string in str to an integer value
                 according to the given base, which must be between
                 2 and 36 inclusive.
       
   RETURN VALUE:  The  AtoiUpTo36Base() function returns the result
                  of the conversion in decimal integer, unless the
                  value would underflow or overflow. 
        
    NOTE: 1) If base is 10 and value is negative, the resulting string is
            preceded with a minus sign (-). With any other base,
            value is always considered unsigned.   
          2) errno  is  not set on error so there is no way to distinguish
             between 0 as an error and as the converted value. 
             
          3) No checks for overflow or underflow are done.
   
*/

static int AtoiUpTo36Base(const char *str, int base)
{
	int dig = 0;
	int num = 0;

	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	
	if (  (base > 36) || (base < 2) )
	{
	   puts("Invalid base value");
	   return 0;
	}
	
	str = WhiteSpacesSkip(str);
	if ( ( base == 10) )
		{
			return Atoi10Base( str );
		}
		
	while( (('0' <= *str ) && ( *str <='9' ) )||
	       (('a' <= *str ) && ( *str <='z' ) ) ||
	       (('A' <= *str ) && ( *str <='Z' )  ) )
	{      
		dig = ( *str > '9' ) ? tolower(*str) - 'a' +10 : *str - '0'; 
		num = num*base + dig ;
		++str;
	}
	
	return num;
}



/************************************************************/
/********************  WhiteSpacesSkip**********************/
/***********************************************************/

/*  An auxilary function that skipping intial portion 
    of the white spaces */
static const char* WhiteSpacesSkip(const char *nptr)
{
	while(( *nptr == 32) || ((*nptr >= 9) && (*nptr <=13 )))
	{
		++nptr;
	} 
	return nptr;
}

/************************************************************/
/*************************  ReverseStr***********************/
/************************************************************/
/* An auxilary function to reverse a string*/

static void ReverseStr(char* str)
{

	char temp = 0;
	int low = 0;
	int high = strlen(str) - 1 ;

	while( low < high )
	{
		temp = str[low];
		str[low] = str[high];
		str[high] = temp;
		low++;
		high--;
	}
	
}

/************************************************************/
/**************** Atoi function definition ******************/
/************************************************************/

/* 

   DESCRIPTION: The  Atoi() function  converts the initial portion
                 of the string pointed to by nptr to int.
                 
   RETURN VALUE: The converted value or 0 on error.
 
   NOTE: 1) errno  is  not set on error so there is no way to distinguish
            between 0 as an error and as the converted value. 
         2) No checks for overflow or underflow are done.
            Only base-10 input can be converted.
*/

static int Atoi10Base(const char *nptr)
{
	int num = 0;
	int sign = 1;
	
	nptr = WhiteSpacesSkip(nptr);
	if( *nptr == '-')
	{
		sign = -1;
		++nptr;
	}

	while( ('0' <= *nptr ) && ( *nptr <='9' ))
	{
		num = num*10 + *nptr - '0';
		++nptr;
	}

	return ( sign * num );

}

/************************************************************/
/************* Itoa10Base function definition ***************/
/************************************************************/
/* 
   DESCRIPTION: Converts an integer value of base 10 to a null-terminated 
                string and stores the result in the array
                given by str parameter.
                 
   RETURN VALUE: A pointer to the resulting null-terminated string,
                  same as parameter str.
  
*/
static char* Itoa10Base(int n, char* str)
{

	int sign = 1;
	char* pstr = str;
	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	
	if( n <= 0 )
	{
		if ( n == 0)
		{
			*str++ = '0';
			*str = '\0';
			return str; 
		}
		else
		{
			n = -n;
			sign = -1;
		}
	}
	
	while( n )
	{
		*str++ = n % 10 + '0';
		n = n / 10;
	}
	
	if(sign == -1 )
	{
		*str++ = '-';
	}
	
	*str = '\0'; 

	ReverseStr(pstr);

	return pstr;
}

/************************************************************/
/******************* RecDHCPDestroy *************************/
/************************************************************/
static void RecDHCPDestroy(dhcp_node_t *root)
{
	if( NULL == root )
	{
		return;
	}

	RecDHCPDestroy(root->child[LEFT]);
	RecDHCPDestroy(root->child[RIGHT]);

	root->child[LEFT] = root->child[RIGHT] = NULL;

	free( root );

	root = NULL;
		
}

/************************************************************/
/******************* ItoaTo2Base *************************/
/************************************************************/

static char *ItoaTo2Base(dhcp_t* dhcp, char *dest, 
	const ip_addrs_t requested_ip )
{
uint8_t i = 0;

	for( i = 0; i < BYTES_IN_IP; ++i )
	{

	ItoaUpTo36Base(requested_ip[i],
	dest + (i * BYTE_SIZE) , BASE); 

	}

	*(dest + dhcp->bits_num_in_subnet) = '\0';

return dest;

}

/************************************************************/
/******************* CreateNode *************************/
/************************************************************/
static dhcp_node_t *CreateNode(dhcp_node_t *parent )
{
	dhcp_node_t *new_node = NULL;
	new_node = (dhcp_node_t*)malloc( sizeof( dhcp_node_t) );
	
	if( NULL == new_node )
	{
		return NULL;
	}

	new_node->child[LEFT] = new_node->child[RIGHT] = NULL;
	new_node->is_occupied = FALSE;
	new_node->parent = parent;

	return new_node;
}



/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/


	

