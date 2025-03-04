/******************************************************************************
*	Version 1.1
*   Last Updated:   04/03/25
*                   16:32
******************************************************************************/
#ifndef __DHCP_H__		/* __DHCP_H__ */
#define __DHCP_H__		/* __DHCP_H__ */

#include <stddef.h>     /* size_t     */

#define  BYTES_IN_IP    (4)

typedef struct dhcp dhcp_t;

/******************************************************************************
*
*       Description: Create a new DHCP
*       Arguments: * 'subnet_ip' - The static subnet address
*                  * 'bits_num_in_subnet' - Size of the subnet mask
*       Return: The newly created DHCP
*       Note: First element of 'subnet_ip' is the first part of the address
* 
*/      dhcp_t *DHCPCreate(const unsigned char subnet_ip[BYTES_IN_IP],
                           size_t bits_num_in_subnet);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroy a valid DHCP
*       Arguments: 'dhcp' - The DHCP to destroy
*       Return: N\A
*       Note: if "dhcp" is NULL, no operations will be performed
* 
*/      void DHCPDestroy(dhcp_t* dhcp);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Allocate an address through the DHCP
*       Arguments: * 'dhcp' - The DHCP to allocate an address from
*                  * 'requested_ip' - The address to allocate
*                  * 'allocated_ip' - The returned address allocated
*       Return: SUCCESS (0), ALLOC_FAIL (1), REQUEST_NOT_MET (2)
*       Note: 'requested_ip' can be NULL to get not specify ip
*             The requested address could already be allocated, therefore
*             the DHCP will allocate the next best available address.
*             If no IP found larger than requested address - return FAILURE.
*             Undefined behavior if requested_ip subnet_ip is different than dhcp subnet_ip.
* *
*/      int DHCPAllocateIP(dhcp_t* dhcp,
                           const unsigned char requested_ip[BYTES_IN_IP],
                           unsigned char ret_allocated_ip[BYTES_IN_IP]);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Free an allocated address from the DHCP
*       Arguments: * 'dhcp' - DHCP to free the address from
*                  * 'ip_to_free' - The address to free
*       Return: SUCCESS (0) or DOUBLE_FREE_FAIL (-1) if 'ip_to_free' is already free
*       Note: Undefined behaviour if 'dhcp' or 'ip_to_free' is NULL
* 
*/      int DHCPFreeIP(dhcp_t* dhcp,
                       const unsigned char ip_to_free[BYTES_IN_IP]);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Count the number of available addresses to allocate
*       Arguments: 'dhcp' - DHCP to get the statistic from
*       Return: Number of free addresses
*       Note: Undefined behaviour if 'dhcp' is NULL
* 
*/      size_t DHCPCountFree(const dhcp_t* dhcp);
/*
******************************************************************************/

#endif                  /* __DHCP_H__ */ 