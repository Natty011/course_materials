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
#define WORD_SIZE			( 32 )


/************************************************************/
/********************  lut_knight_moves**********************/
/************************************************************/

typedef uint8_t ip_addrs_t[4];
/******************************************************************************/
/***************************** Success / Fail Enum ****************************/
/******************************************************************************/


typedef enum
{
	BACK_SLASH_NULL = '\0',
	ZERO_CHAR = 48,
	ONE_CHAR = 49

} char_represents_t;

typedef enum
{
	IS_FULL = -3,
	SYS_FAIL = -2,
	DOUBLE_FREE_FAIL = -1,
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

typedef enum
{
	INIT_IP = 0,
	PORTION_IP = 1

} state_convert_t;



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

static char reserved_network[MAX_SIZE] = { 0 };
static char reserved_server[MAX_SIZE] = { 0 };
static char reserved_broadcast[MAX_SIZE]= { 0 };

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
	       const ip_addrs_t requested_ip, state_convert_t state );

static void UpdadePathToIsAllocated( dhcp_node_t *node );
static int
		 TryToAllocExactHostIp(dhcp_node_t *root, char *host_ip,
								 size_t host_bits);

static void
 	   StrHostIpToUint(char *host_ip, ip_addrs_t ret_allocated_ip);
	   
static int 
		DHCPFreeIpExist(dhcp_node_t *root, char *host_ip, int host_bits);

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
	/*char prefix_ip_copy[MAX_SIZE] = { 0 };*/

	char word[MAX_SIZE] = { 0 };
	/*char word2[MAX_SIZE] = { 0 };*/
	uint8_t host_size = WORD_SIZE - bits_num_in_subnet;
	int res = 0;
	/*
	char *host_network_ip = NULL;
	char *host_broadcast_ip = NULL;
	char *host_server_ip = NULL;
*/
	uint32_t total = 1U<<host_size; /*, res_candidate = 0*/
	/*
	ip_addrs_t network_ip = { 0 };
	ip_addrs_t broadcast_ip = { 0 };
	ip_addrs_t server_ip = { 0 };
*/
	
	total = total - 3;
	/*printf("total = { %u} \n", total );*/


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

	ItoaTo2Base(dhcp_ptr, prefix_ip, subnet_ip, INIT_IP) ;

	dhcp_ptr->ip = prefix_ip;

	/*puts(dhcp_ptr->ip);*/

	ItoaTo2Base(dhcp_ptr, word, subnet_ip, PORTION_IP) ;
	/*puts(word +  bits_num_in_subnet) ;*/

	memset(reserved_network, '0', host_size);
	reserved_network[host_size] = BACK_SLASH_NULL;

	memset(reserved_broadcast, '1', host_size);
	reserved_broadcast[host_size] = BACK_SLASH_NULL;

	memset(reserved_server, '1', host_size);
	reserved_server[host_size - 1] = ZERO_CHAR;
	reserved_server[host_size] = BACK_SLASH_NULL;
/*
	puts(reserved_network);
	puts(reserved_server);
	puts(reserved_broadcast);
*/

	res = TryToAllocExactHostIp( dhcp_ptr->root,reserved_network, host_size );
	res = TryToAllocExactHostIp( dhcp_ptr->root,reserved_server, host_size);
	res = TryToAllocExactHostIp( dhcp_ptr->root,reserved_broadcast, host_size );
	UNUSED(res);

	return dhcp_ptr;
}

/************************************************************/
/********************  DHCPAllocateIP  **********************/
/************************************************************/

int DHCPAllocateIP(dhcp_t* dhcp,
	const unsigned char requested_ip[BYTES_IN_IP],
	unsigned char ret_allocated_ip[BYTES_IN_IP])
{
	
	char word[MAX_SIZE] = { 0 };
	/*char *candidate = NULL;*/
	dhcp_node_t *root = dhcp->root;
	size_t subnet_size_bits = dhcp->bits_num_in_subnet;
	/*char word2[MAX_SIZE] = { 0 };*/
	uint8_t host_size_bits = WORD_SIZE - subnet_size_bits;
	int res = 0;
	char prefix_ip_copy[MAX_SIZE] = { 0 };
	char *host_ip_to_allocate = NULL;
	uint32_t total = 1U<<host_size_bits, res_candidate = 0;

	assert(dhcp);
	assert(requested_ip);
	assert(ret_allocated_ip);

	/* check if the prefix of requested_ip is correct */

	#ifndef NDEBUG 
	if(  *(uint32_t*)requested_ip )
	{
		ItoaTo2Base(dhcp, prefix_ip_copy, requested_ip, INIT_IP) ;
		assert( ! strcmp(prefix_ip_copy, dhcp->ip ) );

	}
	#endif

	total = total - 3; /* 253 */

	strcpy(prefix_ip_copy, dhcp->ip);

	printf("requested_ip = {%u, %u, %u, %u} \n", requested_ip[0], requested_ip[1],
							requested_ip[2], requested_ip[3]);

	ItoaTo2Base(dhcp, word, requested_ip, PORTION_IP) ;
	host_ip_to_allocate = word +  subnet_size_bits;
	/*puts(host_ip_to_allocate) ;*/

	res = TryToAllocExactHostIp( root,
				host_ip_to_allocate, host_size_bits );

	/*printf("res = { %d }\n", res);*/

	if(IS_FULL != res)
	{
		
		if(SYS_FAIL == res )
		{
			return FAIL;
		}

		if(host_size_bits == res )
		{
			memcpy(ret_allocated_ip, requested_ip, BYTES_IN_IP);
			return SUCCESS;
		}
		
		while(host_size_bits != res )
		{
			/*strcpy(word2, reserved_network );*/
			res_candidate = AtoiUpTo36Base(host_ip_to_allocate, BASE);
			/*puts(host_ip_to_allocate);*/

			if(res_candidate >= total )
			{
				return FAIL;
			}

			/*printf("res_candidate = { %u} \n", res_candidate );*/
			res_candidate += 1U;
			/*printf("res_candidate = { %u} \n", res_candidate );*/

			ItoaUpTo36Base(res_candidate, host_ip_to_allocate, BASE);
			/*puts(host_ip_to_allocate);*/

			res = TryToAllocExactHostIp( root,
				host_ip_to_allocate, host_size_bits );

			/*printf("res = { %d }\n", res);*/

			

		}

		host_ip_to_allocate = strcat(prefix_ip_copy, host_ip_to_allocate);
			/*puts(host_ip_to_allocate);*/

			StrHostIpToUint(host_ip_to_allocate, ret_allocated_ip);
  			 printf("ret_allocated_ip = {%u, %u, %u, %u} \n", ret_allocated_ip[0],
				 ret_allocated_ip[1], ret_allocated_ip[2], ret_allocated_ip[3]);

		return 	REQUEST_NOT_MET;		
	}

	return FAIL;
}

/************************************************************/
/*********************  DHCPFreeIP  *************************/
/************************************************************/

int DHCPFreeIP(dhcp_t* dhcp,
	const unsigned char ip_to_free[BYTES_IN_IP])
{
	
	int level = 0;
	dhcp_node_t *current = NULL, *parent = NULL;


	char word[MAX_SIZE] = { 0 };
	char *reserved_ips[3] = {reserved_network, reserved_server,
							 reserved_broadcast };

							 dhcp_node_t *root = dhcp->root;
	size_t subnet_size_bits = dhcp->bits_num_in_subnet;
	uint8_t host_size_bits = WORD_SIZE - subnet_size_bits, idx = 0;
	/*int res = 0;*/

	char prefix_ip_copy[MAX_SIZE] = { 0 };
	char *host_ip_to_free = NULL;

	assert(dhcp);
	assert(ip_to_free);
	
	/* check if the prefix of requested_ip is correct */
	#ifndef NDEBUG 
		if(  *(uint32_t*)ip_to_free )
		{
			ItoaTo2Base(dhcp, prefix_ip_copy, ip_to_free, INIT_IP) ;
			assert( ! strcmp(prefix_ip_copy, dhcp->ip ) );

		}
	#endif

	strcpy(prefix_ip_copy, dhcp->ip);

	printf("ip_to_free = {%u, %u, %u, %u} \n", ip_to_free[0], ip_to_free[1],
						ip_to_free[2], ip_to_free[3]);

	
												
	ItoaTo2Base(dhcp, word, ip_to_free, PORTION_IP) ;
	host_ip_to_free = word +  subnet_size_bits;
	

	for(idx = 0; idx < 3; ++idx )
	{
		if ( ! strcmp(host_ip_to_free, reserved_ips[idx] ) )
		{
			return DOUBLE_FREE_FAIL; /* or  FAIL ? DOUBLE_FREE_FAIL ?  */
		}
	}
	
	current = root;

	printf("root = %p\n", (void*)root);

	/* To go down to the leaf */
	for(level = 0; level < host_size_bits; ++level )
	{
		int bit = host_ip_to_free[level] - ZERO_CHAR;

		if( NULL == current->child[bit] )
		{
			return DOUBLE_FREE_FAIL;
		}

		current = current->child[bit];
		printf("current = %p\n", (void*)current);

	}

	/* level == host_bits */
	/*while(current != root )*/
	/*
	puts("hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii");

	for(level = host_size_bits - 1; level >= 0; --level )

	{
		int bit = host_ip_to_free[level] - ZERO_CHAR;
		printf("bit = %d \n", bit );
		printf("current = %p\n", (void*)current);

		parent = current->parent;
		printf("level = %d \n", level );
		printf("parent = %p\n", (void*)parent);
		free(current);
		current = NULL;
		parent->is_occupied = FALSE;
		parent->child[ bit ] = NULL;

		if( NULL == parent->child[ !bit ] )
		{
			current = parent;
		}

		else
		{
			--level;
			while( level >= 0)
			{
				printf("level = %d \n", level );

				parent = parent->parent;
				printf("parent = %p\n", (void*)parent);

				parent->is_occupied = FALSE;

				--level;
			}
			puts("bbbbbbbbbbbbbbbbbbbbbbbbb");
			printf("level = %d \n", level );

			break;
		}
	}

	return SUCCESS;
*/

	return DHCPFreeIpExist(root, host_ip_to_free , host_size_bits);

	
}

/************************************************************/
/********************  DHCPFreeIpExist  *********************/
/************************************************************/

static int DHCPFreeIpExist(dhcp_node_t *root, char *host_ip,
							int host_bits)
{
	int level = 0, host_bits_size = (int)host_bits;
	dhcp_node_t *current = NULL, *parent = NULL;

	current = root;
	/*printf("root = %p\n", (void*)root);*/

	/* To go down to the leaf */
	for(level = 0; level < host_bits; ++level )
	{
		int bit = host_ip[level] - ZERO_CHAR;

		if( NULL == current->child[bit] )
		{
			return DOUBLE_FREE_FAIL;
		}

		current = current->child[bit];
		/*printf("current = %p\n", (void*)current);*/

	}
	/* level == host_bits */
	/*while(current != root )*/
	/*puts("hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii");*/

	for(level = host_bits - 1; level >= 0; --level )

	{
		int bit = host_ip[level] - ZERO_CHAR;
		/*
		printf("bit = %d \n", bit );
		printf("current = %p\n", (void*)current);
		*/

		parent = current->parent;
		/*
		printf("level = %d \n", level );
		printf("parent = %p\n", (void*)parent);
		*/
		free(current);
		current = NULL;

		parent->is_occupied = FALSE;

		parent->child[ bit ] = NULL;

		if( NULL == parent->child[ !bit ] )
		{
			current = parent;
		}

		else
		{
			/*puts("bbbbbbbbbbbbbbbbbbbbbbbbb");
			printf("level = %d \n", level );*/
			--level;
			while( level >= 0)
			{
				/*printf("level = %d \n", level );*/

				parent = parent->parent;
				/*printf("parent = %p\n", (void*)parent);*/

				parent->is_occupied = FALSE;

				--level;
			}
			break;
		}
	}

	return SUCCESS;

}						
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
	const ip_addrs_t requested_ip, state_convert_t state )
{
	uint8_t i = 0;
	
	for( i = 0; i < BYTES_IN_IP; ++i )
	{

	ItoaUpTo36Base(requested_ip[i],
		dest + (i * BYTE_SIZE) , BASE); 

	}


	if( PORTION_IP == state)
	{
		*(dest + MAX_SIZE) = '\0';
		return dest ;

	}

	*(dest + dhcp->bits_num_in_subnet) = '\0';

	return dest;

}

/************************************************************/
/********************** CreateNode **************************/
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
/****************** UpdadePathToIsAllocated *****************/
/************************************************************/
static void UpdadePathToIsAllocated( dhcp_node_t *node)
{
	dhcp_node_t *parent = NULL;
	int left_alloc = 0, right_alloc = 0;
	assert(node);
	parent = node->parent;

	while(parent)
	{
		left_alloc = ( parent->child[LEFT] && 
					parent->child[LEFT]->is_occupied );

		right_alloc = ( parent->child[RIGHT] && 
			parent->child[RIGHT]->is_occupied );

		if( left_alloc && right_alloc )
		{
			parent->is_occupied = TRUE;
		}
		
		else
		{
			break;
		}

		parent = parent->parent;
	}
}



/************************************************************/
/********************  StrHostIpToUint  *********************/
/************************************************************/

static void StrHostIpToUint(char *host_ip, ip_addrs_t ret_allocated_ip)
{
	uint8_t i = 0;

	char one_bye[9] = { 0 };
	one_bye[8] = BACK_SLASH_NULL;	

	for( i = 0; i < BYTES_IN_IP; ++i )
	{
		strncpy(one_bye,host_ip + (i * BYTE_SIZE), BYTE_SIZE );
		ret_allocated_ip[i] =
			 (uint8_t)AtoiUpTo36Base(one_bye , BASE);
	}

}

/************************************************************/
/****************  TryToAllocExactHostIp  *******************/
/************************************************************/

static int TryToAllocExactHostIp(dhcp_node_t *root, char *host_ip,
									 size_t host_bits)
{
	dhcp_node_t *current = root;
	size_t level = 0;

	if(root->is_occupied)
	{
		return IS_FULL;
	}

	for( level = 0; level < host_bits; ++level)
	{
		int bit = host_ip[level] - ZERO_CHAR;

		/*if( current->child[bit]->is_occupied )
		{
			return level;
		}*/

		if( NULL == current->child[bit] ) /* not_occupuied bit */
		{
			current->child[bit] = CreateNode(current);

			if( !current->child[bit] )
			{
				return SYS_FAIL;
			}

		}

		current = current->child[bit];

		if( current->is_occupied ) /* the required path already occupied */
		{
			return level;
		}
	}

	current->is_occupied = TRUE;
	UpdadePathToIsAllocated(current);
	return level;
}


/************************************************************/
/********** End Of Static Functions definition  *************/
/************************************************************/

/*static PrintDataIp()
{

dhcp_t *dhcp_ptr = NULL;
	dhcp_node_t *root = NULL;
	char *prefix_ip = NULL;
	char prefix_ip_copy[MAX_SIZE] = { 0 };

	char word[MAX_SIZE] = { 0 };
	char word2[MAX_SIZE] = { 0 };
	uint8_t host_size = WORD_SIZE - bits_num_in_subnet;
	int res = 0;
	char *host_network_ip = NULL;
	char *host_broadcast_ip = NULL;
	char *host_server_ip = NULL;

	uint32_t total = 1U<<host_size, res_candidate = 0;
	ip_addrs_t network_ip = { 0 };
	ip_addrs_t broadcast_ip = { 0 };
	ip_addrs_t server_ip = { 0 };

puts("++++++++++++++++++++network_ip+++++++++++++++++");

	res = TryToAllocExactHostIp( dhcp_ptr->root,reserved_server, host_size);

	printf("res = { %d }\n", res);

	puts("++++++++++++++++++++server_ip++++++++++++++++++");

	strcpy(prefix_ip_copy, prefix_ip);

	host_server_ip = strcat(prefix_ip_copy, reserved_server);
	puts(host_server_ip);
	StrHostIpToUint(host_server_ip, server_ip);
  			 printf("{%u, %u, %u, %u}\n", server_ip[0], server_ip[1],
				server_ip[2], server_ip[3]);

	puts("++++++++++++++++++++server_ip+++++++++++++++++");

	res = TryToAllocExactHostIp( dhcp_ptr->root,reserved_broadcast, host_size );
	printf("res = { %d }\n", res);

	puts("++++++++++++++++++++broadcast_ip++++++++++++++++");
	strcpy(prefix_ip_copy, prefix_ip);
	puts(prefix_ip_copy);
	
	host_broadcast_ip = strcat(prefix_ip_copy, reserved_broadcast);
	puts(host_broadcast_ip);

	StrHostIpToUint(host_broadcast_ip, broadcast_ip);
  			 printf("{%u, %u, %u, %u}\n", broadcast_ip[0], broadcast_ip[1],
				broadcast_ip[2], broadcast_ip[3]);
				
	puts("++++++++++++++++++++broadcast_ip++++++++++++++++++");

	puts("++++++++++++++++++++*************++++++++++++++++++");
	*/

	/*
	puts("++++++++++++++++++++network_ip++++++++++++++++++");
	strcpy(prefix_ip_copy, prefix_ip);

	host_network_ip = strcat(prefix_ip_copy, reserved_network);
	puts(host_network_ip);
	StrHostIpToUint(host_network_ip, network_ip);
  			 printf("{%u, %u, %u, %u}\n", network_ip[0], network_ip[1],
				network_ip[2], network_ip[3]);

	puts("++++++++++++++++++++network_ip+++++++++++++++++");


	printf("res = { %d }\n", res);

	puts("++++++++++++++++++++server_ip++++++++++++++++++");

	strcpy(prefix_ip_copy, prefix_ip);

	host_server_ip = strcat(prefix_ip_copy, reserved_server);
	puts(host_server_ip);
	StrHostIpToUint(host_server_ip, server_ip);
  			 printf("{%u, %u, %u, %u}\n", server_ip[0], server_ip[1],
				server_ip[2], server_ip[3]);

	puts("++++++++++++++++++++server_ip+++++++++++++++++");

	printf("res = { %d }\n", res);

	puts("++++++++++++++++++++broadcast_ip++++++++++++++++");
	strcpy(prefix_ip_copy, prefix_ip);
	puts(prefix_ip_copy);
	
	host_broadcast_ip = strcat(prefix_ip_copy, reserved_broadcast);
	puts(host_broadcast_ip);

	StrHostIpToUint(host_broadcast_ip, broadcast_ip);
  			 printf("{%u, %u, %u, %u}\n", broadcast_ip[0], broadcast_ip[1],
				broadcast_ip[2], broadcast_ip[3]);
				
	puts("++++++++++++++++++++broadcast_ip++++++++++++++++++");


}
*/


/*
puts("++++++++++++++++++++network_ip++++++++++++++++++");
strcpy(prefix_ip_copy, prefix_ip);

host_network_ip = strcat(prefix_ip_copy, reserved_network);
puts(host_network_ip);
StrHostIpToUint(host_network_ip, network_ip);
			printf("{%u, %u, %u, %u}\n", network_ip[0], network_ip[1],
			network_ip[2], network_ip[3]);

puts("++++++++++++++++++++network_ip+++++++++++++++++");


printf("res = { %d }\n", res);

puts("++++++++++++++++++++server_ip++++++++++++++++++");

strcpy(prefix_ip_copy, prefix_ip);

host_server_ip = strcat(prefix_ip_copy, reserved_server);
puts(host_server_ip);
StrHostIpToUint(host_server_ip, server_ip);
			printf("{%u, %u, %u, %u}\n", server_ip[0], server_ip[1],
			server_ip[2], server_ip[3]);

puts("++++++++++++++++++++server_ip+++++++++++++++++");

printf("res = { %d }\n", res);

puts("++++++++++++++++++++broadcast_ip++++++++++++++++");
strcpy(prefix_ip_copy, prefix_ip);
puts(prefix_ip_copy);

host_broadcast_ip = strcat(prefix_ip_copy, reserved_broadcast);
puts(host_broadcast_ip);

StrHostIpToUint(host_broadcast_ip, broadcast_ip);
			printf("{%u, %u, %u, %u}\n", broadcast_ip[0], broadcast_ip[1],
			broadcast_ip[2], broadcast_ip[3]);
			
puts("++++++++++++++++++++broadcast_ip++++++++++++++++++");


res = TryToAllocExactHostIp( dhcp_ptr->root,reserved_network, host_size );


printf("res = { %d }\n", res);
*/

/*
if(IS_FULL != res)
{
	
	if(host_size != res )
	{
		strcpy(word2, reserved_network );
		res_candidate = AtoiUpTo36Base(word2, BASE);
		puts(word2);


		printf("res_candidate = { %u} \n", res_candidate );
		res_candidate += 1U;
		printf("res_candidate = { %u} \n", res_candidate );

		ItoaUpTo36Base(res_candidate, word2, BASE);
		puts(word2);

		res = TryToAllocExactHostIp( dhcp_ptr->root,word2, host_size );

		printf("res = { %d }\n", res);

		host_ip_to_allocate =	strcat(dhcp_ptr->ip, word2);
		puts(host_ip_to_allocate);

		StrHostIpToUint(host_ip_to_allocate, ret_allocated_ip);
			printf("{%u, %u, %u, %u}\n", ret_allocated_ip[0], ret_allocated_ip[1],
				ret_allocated_ip[2], ret_allocated_ip[3]);



	}
	*/





	

