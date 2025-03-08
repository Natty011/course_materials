/***************************************
* Author : Natty
* Reviewer : ???
* Date : 05 / 03 / 2025
* Last update: 08 / 03 / 2025
*****************************************/
/*#define PRINTS*/
#ifdef PRINTS
	#include <stdio.h> /* printf, puts  */
#endif
#include <stdint.h>		/*uint8_t, uint32_t */
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include <string.h> 	/* memcpy, memset, strcat,
							 strncat, strcpy, strcmp, strncpy */

#include "dhcp.h"

#define UNUSED( var )       ( (void)var )

#define BYTE_SIZE			( 8 )
#define BASE				( 2 )
#define MAX_SIZE			( 33 )
#define WORD_SIZE			( 32 )
#define RESERVED_ADDR_SIZE  ( 3 )

/******************************************************************************/
/*********************  Typedef ip array  *************************************/
/******************************************************************************/

typedef uint8_t ip_addrs_t[4];

/******************************************************************************/
/***************************** Success / Fail Enum ****************************/
/******************************************************************************/

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

/******************************************************************************/
/******************************* results/states Enums *************************/
/******************************************************************************/

typedef enum
{
	BACK_SLASH_NULL = '\0',
	ZERO_CHAR = 48,
	ONE_CHAR = 49

} char_represents_t;


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
/******************************************************************************/

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
	size_t count_Free_ip;

};

/******************************************************************************/
/************************ static globals variables ****************************/
/******************************************************************************/

static char reserved_network[MAX_SIZE] = { 0 };
static char reserved_server[MAX_SIZE] = { 0 };
static char reserved_broadcast[MAX_SIZE]= { 0 };

static char *reserved_ips[RESERVED_ADDR_SIZE] = 
			{reserved_network, reserved_server, reserved_broadcast };

/******************************************************************************/
/************************ static functions declartions ************************/
/******************************************************************************/

static void RecDHCPDestroy(dhcp_node_t *root);
static dhcp_node_t *CreateNode(dhcp_node_t *parent );
static int Atoi2Base(const char *str, int base);
static char* ItoaTo2BaseOrigin(int n, char* str, int base, size_t len_str);
static const char* WhiteSpacesSkip(const char *nptr);
static void ReverseStr(char* str);

static char *ItoaTo2Base(dhcp_t* dhcp, char *dest, 
	      		 const ip_addrs_t requested_ip, state_convert_t state );

static void UpdadePathToIsAllocated( dhcp_node_t *node );

static int
		 TryToAllocExactHostIp(dhcp_node_t *root,
								 char *host_ip, size_t host_bits);

static void
 	   StrHostIpToUint(char *host_ip, ip_addrs_t ret_allocated_ip);
	   
static int 
		DHCPFreeIpExist(dhcp_node_t *root, char *host_ip, int host_bits);

static int InitReservedIps(dhcp_t *dhcp, 
			char *reserved_ips[RESERVED_ADDR_SIZE], uint8_t host_size);		

/******************************************************************************/
/*******************End Of Static Functions declartions************************/
/******************************************************************************/


/******************************************************************************/
/*************************  DHCPCreate  ***************************************/
/******************************************************************************/

dhcp_t *DHCPCreate(const unsigned char subnet_ip[BYTES_IN_IP],
                           size_t bits_num_in_subnet)
{
	dhcp_t *dhcp_ptr = NULL;
	dhcp_node_t *root = NULL;

	char *prefix_ip = NULL;

	uint8_t host_size = WORD_SIZE - bits_num_in_subnet;

	uint32_t total = 1U<<host_size; 
	total = total - RESERVED_ADDR_SIZE;

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


	if ( FAIL == InitReservedIps(dhcp_ptr, reserved_ips, host_size ) )
	{
		return NULL;
	}

	dhcp_ptr->count_Free_ip = total; 

	return dhcp_ptr;
}

/******************************************************************************/
/*******************  DHCPAllocateIP  *****************************************/
/******************************************************************************/

int DHCPAllocateIP(dhcp_t* dhcp,
	const unsigned char requested_ip[BYTES_IN_IP],
	unsigned char ret_allocated_ip[BYTES_IN_IP])
{
	int res = 0;
	dhcp_node_t *root = dhcp->root;
	size_t subnet_size_bits = dhcp->bits_num_in_subnet;

	uint8_t host_size_bits = WORD_SIZE - subnet_size_bits;

	char prefix_ip_copy[MAX_SIZE] = { 0 }, word[MAX_SIZE] = { 0 },
				*host_ip_to_allocate = NULL;

	uint32_t total = (1UL<<host_size_bits) - RESERVED_ADDR_SIZE,
						 res_candidate = 0;

	word[WORD_SIZE] = BACK_SLASH_NULL;

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

	strcpy(prefix_ip_copy, dhcp->ip);

	#ifdef PRINTS
		/*printf("requested_ip = {%u, %u, %u, %u} \n", requested_ip[0], requested_ip[1],
							requested_ip[2], requested_ip[3]);*/
	#endif

	host_ip_to_allocate = word;
	host_ip_to_allocate = ItoaTo2Base(dhcp, host_ip_to_allocate,
					 requested_ip, PORTION_IP) ;

	res = TryToAllocExactHostIp( root,
				host_ip_to_allocate, host_size_bits );

	if(IS_FULL != res)
	{
		if(SYS_FAIL == res )
		{
			return FAIL;
		}

		if(host_size_bits == res )
		{
			memcpy(ret_allocated_ip, requested_ip, BYTES_IN_IP);
			--dhcp->count_Free_ip;		 
			return SUCCESS;
		}
		
		while(host_size_bits != res )
		{
			res_candidate = Atoi2Base(host_ip_to_allocate, BASE);

			if(res_candidate >= total )
			{
				return FAIL;
			}

			res_candidate += 1U;

			ItoaTo2BaseOrigin(res_candidate, host_ip_to_allocate,
								 BASE, host_size_bits);

			res = TryToAllocExactHostIp( root,
				host_ip_to_allocate, host_size_bits );
		}

		host_ip_to_allocate = strcat(prefix_ip_copy, host_ip_to_allocate);

		StrHostIpToUint(host_ip_to_allocate, ret_allocated_ip);

		#ifdef PRINTS
		/*
  			 printf("ret_allocated_ip = {%u, %u, %u, %u} \n", ret_allocated_ip[0],
				 ret_allocated_ip[1], ret_allocated_ip[2], ret_allocated_ip[3]);
		*/
		#endif

		--dhcp->count_Free_ip;		 
		return 	REQUEST_NOT_MET;		
	}

	return FAIL;
}

/******************************************************************************/
/*********************  DHCPFreeIP  *******************************************/
/******************************************************************************/

int DHCPFreeIP(dhcp_t* dhcp,
	const unsigned char ip_to_free[BYTES_IN_IP])
{
	
	int level = 0, res = DOUBLE_FREE_FAIL;
	dhcp_node_t *current = NULL, *root = NULL;

	char word[MAX_SIZE] = { 0 }, *host_ip_to_free = NULL;

	size_t subnet_size_bits = dhcp->bits_num_in_subnet;
	uint8_t host_size_bits = WORD_SIZE - subnet_size_bits, idx = 0;

	word[WORD_SIZE] = BACK_SLASH_NULL;
	host_ip_to_free = word;

	assert(dhcp);
	assert(ip_to_free);

	root = dhcp->root;

	/* check if the prefix of requested_ip is correct */
	#ifndef NDEBUG 
		if(  *(uint32_t*)ip_to_free )
		{
			ItoaTo2Base(dhcp, word, ip_to_free, INIT_IP) ;
			assert( ! strcmp(word, dhcp->ip ) );

		}
	#endif
	
	#ifdef PRINTS 
	/*	
		printf("ip_to_free = {%u, %u, %u, %u} \n", ip_to_free[0], ip_to_free[1],
						ip_to_free[2], ip_to_free[3]);
	*/
	#endif
				
	host_ip_to_free = ItoaTo2Base(dhcp, host_ip_to_free, ip_to_free, PORTION_IP) ;

	for(idx = 0; idx < RESERVED_ADDR_SIZE ; ++idx )
	{
		if ( ! strcmp(host_ip_to_free, reserved_ips[idx] ) )
		{
			return DOUBLE_FREE_FAIL; /* or  FAIL ? DOUBLE_FREE_FAIL ?  */
		}
	}
	
	current = root;

	/* To go down to the leaf */
	for(level = 0; level < host_size_bits; ++level )
	{
		int bit = host_ip_to_free[level] - ZERO_CHAR;

		if( NULL == current->child[bit] )
		{
			return DOUBLE_FREE_FAIL;
		}

		current = current->child[bit];

	}

	res = DHCPFreeIpExist(root, host_ip_to_free , host_size_bits);
	 
	return res ? res  : ! (++dhcp->count_Free_ip ) ; 	 
 
}

/******************************************************************************/
/********************  DHCPFreeIpExist  ***************************************/
/******************************************************************************/

static int DHCPFreeIpExist(dhcp_node_t *root, char *host_ip,
							int host_bits)
{
	int level = 0;
	dhcp_node_t *current = NULL, *parent = NULL;

	current = root;

	/* To go down to the leaf */
	for(level = 0; level < host_bits; ++level )
	{
		int bit = host_ip[level] - ZERO_CHAR;

		if( NULL == current->child[bit] )
		{
			return DOUBLE_FREE_FAIL;
		}

		current = current->child[bit];

	}

	for(level = host_bits - 1; level >= 0; --level )

	{
		int bit = host_ip[level] - ZERO_CHAR;

		parent = current->parent;

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
				parent = parent->parent;

				parent->is_occupied = FALSE;

				--level;
			}

			break;
		}
	}

	return SUCCESS;
}						
/******************************************************************************/
/********************  DHCPDestroy  *******************************************/
/******************************************************************************/
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

/******************************************************************************/
/*******************  DHCPCountFree *******************************************/
/******************************************************************************/
size_t DHCPCountFree(const dhcp_t* dhcp)
{
	assert(dhcp);
	return dhcp->count_Free_ip;
}

	
/******************************************************************************/
/*************  Static Functions definition  **********************************/
/******************************************************************************/


/******************************************************************************/
/********************  ItoaTo2BaseOrigin **************************************/
/******************************************************************************/

/* 
   DESCRIPTION: Converts an integer value to a null-terminated string
                of base 2 and stores the result in the
                array given by str parameter.

   RETURN VALUE: A pointer to the resulting null-terminated string,
                  same as parameter str.
                  
    NOTE: 1) value is always considered unsigned.   
         
*/

static char* ItoaTo2BaseOrigin(int n, char* str, int base , size_t len_str)
{
	int remainder = 0;
	char* pstr = str;
	size_t count = 0, i = 0; 

	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (  2 != base )
	{
	   puts("Invalid base value");
	   return str;
	}

	if ( n == 0)
	{
		for(i = 0; i < len_str ; ++i)
		{
			*( str + i ) = ZERO_CHAR;
		}
		*(str + i ) = BACK_SLASH_NULL;
		return str; 
	}
		
	
	/* The base isn't negative decimal */
	while( n )
	{
		remainder = n % base;
		*str++ =  remainder + '0';
		n = n / base;
		++count;
	}
	*str = '\0'; 

	if( len_str - count != 0)
	{
		str = strncat(str, "0000000000000000000000", len_str  - count); 
	}
	
	ReverseStr(pstr);

	return pstr;	
}

/******************************************************************************/
/**************** Atoi2Base function definition *******************************/
/******************************************************************************/
/* 
   DESCRIPTION: The Atoi2Base() function converts the initial 
                part of the string in str to an integer value
                 according to  base 2(binary string).
       
   RETURN VALUE:  The  Atoi2Base() function returns the result
                  of the conversion in decimal integer, unless the
                  value would underflow or overflow. 
        
    NOTE:  
          1) errno  is  not set on error so there is no way to distinguish
             between 0 as an error and as the converted value. 
             
          2) No checks for overflow or underflow are done.
*/

static int Atoi2Base(const char *str, int base)
{
	int dig = 0;
	int num = 0;

	assert( str );

	if (  ( 2 !=  base) )
	{
		#ifdef PRINTS
			puts("Invalid base value");
		#endif

		return 0;
	}
	
	str = WhiteSpacesSkip(str);

	while(  (ZERO_CHAR <= *str ) && ( *str <= ONE_CHAR ) )
	        
	{      
		dig =  *str - '0'; 
		num = num*base + dig ;
		++str;
	}
	
	return num;
}


/******************************************************************************/
/********************  WhiteSpacesSkip  ***************************************/
/******************************************************************************/

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

/******************************************************************************/
/************************* ReverseStr *****************************************/
/******************************************************************************/

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

/******************************************************************************/
/******************* RecDHCPDestroy *******************************************/
/******************************************************************************/

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

/******************************************************************************/
/******************* ItoaTo2Base **********************************************/
/******************************************************************************/

static char *ItoaTo2Base(dhcp_t* dhcp, char *dest, 
	const ip_addrs_t requested_ip, state_convert_t state )
{
	uint8_t i = 0;
	
	for( i = 0; i < BYTES_IN_IP; ++i )
	{

	ItoaTo2BaseOrigin(requested_ip[i],
		dest + (i * BYTE_SIZE) , BASE, BYTE_SIZE); 

	}

	if( PORTION_IP == state)
	{
		*(dest + MAX_SIZE) = BACK_SLASH_NULL;
		return dest + dhcp->bits_num_in_subnet ;

	}

	*(dest + dhcp->bits_num_in_subnet) = BACK_SLASH_NULL;

	return dest;

}
/******************************************************************************/
/********************* CreateNode *********************************************/
/******************************************************************************/

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

/******************************************************************************/
/****************** UpdadePathToIsAllocated ***********************************/
/******************************************************************************/

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


/******************************************************************************/
/************************* StrHostIpToUint ************************************/
/******************************************************************************/

static void StrHostIpToUint(char *host_ip, ip_addrs_t ret_allocated_ip)
{
	uint8_t i = 0;

	char one_bye[9] = { 0 };
	one_bye[8] = BACK_SLASH_NULL;	

	for( i = 0; i < BYTES_IN_IP; ++i )
	{
		strncpy(one_bye,host_ip + (i * BYTE_SIZE), BYTE_SIZE );
		ret_allocated_ip[i] =
			 (uint8_t)Atoi2Base(one_bye , BASE);
	}

}

/******************************************************************************/
/********************** TryToAllocExactHostIp ***********************************/
/******************************************************************************/

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


		if( NULL == current->child[bit] ) /* not occupied bit */
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

/******************************************************************************/
/***************************  InitReservedIps  ********************************/
/******************************************************************************/


static int InitReservedIps(dhcp_t *dhcp,
	char *reserved_ips[RESERVED_ADDR_SIZE], uint8_t host_size)
{
   int res = 0, i = 0;
   dhcp_node_t *root = dhcp->root;

   memset(reserved_ips[0], '0', host_size);
   reserved_ips[0][host_size] = BACK_SLASH_NULL;

   memset(reserved_ips[1], '1', host_size);
   reserved_ips[1][host_size - 1] = ZERO_CHAR;
   reserved_ips[1][host_size] = BACK_SLASH_NULL;

   memset(reserved_ips[2], '1', host_size);
   reserved_ips[2][host_size] = BACK_SLASH_NULL;

   
   for( i = 0; i < RESERVED_ADDR_SIZE ; ++i )
   {
	   res = TryToAllocExactHostIp(root, reserved_ips[i], host_size );

	   if( FAIL == res )
	   {
		   DHCPDestroy(dhcp);
		   root = NULL;
		   dhcp = NULL;

		   return FAIL;
	   }
   }

   return SUCCESS;
   
}


/******************************************************************************/
/**************End Of Static Functions definition *****************************/
/******************************************************************************/

