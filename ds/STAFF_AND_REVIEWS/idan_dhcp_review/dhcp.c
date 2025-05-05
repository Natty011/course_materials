/*******************************************************************************
 *
 *	Aouther:	Idan Hadad
 *	Review:
 *	Date:
 *	worksheet:  Dhcp
 *
 ***************************************()**************************************/
#include <stdint.h> /*      uint8_t          */
#include <stdlib.h> /*      calloc , free    */
#include <string.h> /*      memcpy           */
#include <assert.h> /*      assert           */

#include <stdio.h>

#include "bit_array.h"
#include "dhcp.h"

#define NETWORK_ID 0
#define BITS_IN_BYTE 8
#define BITS_IN_BIT_ARRAY 64
#define BITS_IN_HOST_ID(subnet_len) ((BITS_IN_BYTE * BYTES_IN_IP) -(subnet_len))

/******************************* Enum typdefs *********************************/

typedef enum
{

    FALSE = 0,
    TRUE = 1

} bool_t;

typedef enum
{

    SUCCESS = 0,
    FAIL = 1

} result_t;

/****************************** types typdefs *********************************/

typedef uint8_t ip_t[BYTES_IN_IP];

/******************************************************************************/
/***************************** Management struct ******************************/

struct dhcp
{

    uint32_t subnet;
    uint32_t host_id_mask;
    char bit_map[1];
};

/******************************************************************************/
/*********************** ststic functions declartions *************************/

static uint32_t MakeAlloc(dhcp_t* dhcp, uint32_t host_id);

static result_t FreeAddrs(dhcp_t* dhcp, uint32_t host_id);

static uint32_t SearchFreeIp(dhcp_t* dhcp, uint32_t host_id);

static uint32_t ReadIpFromArray(const ip_t ip_arr);
static void WriteIpToArray(ip_t ip_arr, uint32_t ip);

/******************************************************************************/
/******************************** Dhcp Create  ********************************/

dhcp_t *DHCPCreate(const ip_t subnet, size_t subnet_len)
{
    dhcp_t *dhcp = NULL;
    size_t alloc_size = 0;
    uint32_t subnet_mask = ((uint32_t)-1);
    uint32_t host_id_len = BITS_IN_HOST_ID(subnet_len);
    
    uint32_t host_id_options = (1<<host_id_len);

    uint32_t num_of_bit_arrays = host_id_options>>6;  /* div by 64 */ 

    alloc_size = offsetof(dhcp_t, bit_map) + num_of_bit_arrays * sizeof(size_t);

    dhcp = calloc(1, alloc_size);

    if (NULL == dhcp)
    {
        return NULL;
    }

    
    MakeAlloc(dhcp, NETWORK_ID);
    MakeAlloc(dhcp, host_id_options - 1); /* BroadCast */
    MakeAlloc(dhcp, host_id_options - 2); /* Server */
    
    subnet_mask <<= host_id_len;
    dhcp->subnet = ReadIpFromArray(subnet) & subnet_mask;

    dhcp->host_id_mask = host_id_options - 1;

    return dhcp;
}

/******************************************************************************/
/******************************** DHCPDestroy *********************************/

void DHCPDestroy(dhcp_t *dhcp)
{
    if (dhcp)
    {
        free(dhcp);
        dhcp = NULL;
    }
}

/******************************************************************************/
/****************************** DHCPAllocateIP ********************************/

int DHCPAllocateIP(dhcp_t* dhcp, const ip_t requested_ip, ip_t ret_ip)
{
    uint32_t ip_set = 0, host_id_set = 0;

    uint32_t req_ip = requested_ip ? ReadIpFromArray(requested_ip) : NETWORK_ID;

    uint32_t host_id_to_search_from = req_ip & dhcp->host_id_mask;

    host_id_set = SearchFreeIp(dhcp, host_id_to_search_from);

    if (host_id_set != NETWORK_ID)
    {
        ip_set =  MakeAlloc(dhcp, host_id_set);
        WriteIpToArray(ret_ip, ip_set);
        
        return SUCCESS;
    }

    return FAIL;
}

/******************************************************************************/
/********************************* DHCPFreeIP *********************************/

int DHCPFreeIP(dhcp_t* dhcp, const ip_t  ip)
{
    uint32_t host_id = ReadIpFromArray(ip) & dhcp->host_id_mask;

    return FreeAddrs(dhcp, host_id);
}

/******************************************************************************/
/******************************** DHCPCountFree *******************************/

size_t DHCPCountFree(const dhcp_t* dhcp)
{
    uint32_t host_id_options = dhcp->host_id_mask + 1;
    uint32_t num_of_bit_arrays = (host_id_options / BITS_IN_BIT_ARRAY);
    bit_arr_t* arr = (bit_arr_t*)dhcp->bit_map;
    uint32_t i = 0, counter = 0;

    for (i = 0; i < num_of_bit_arrays; ++i)
    {
        counter += BitArrCountOff(arr[i]);
    }
    return counter;
}

/******************************************************************************/
/************************ ststic functions definitions ************************/

static uint32_t MakeAlloc(dhcp_t* dhcp, uint32_t host_id)
{
    bit_arr_t* bit_array_arr = (bit_arr_t*)dhcp->bit_map;

    uint32_t arr_num = host_id / BITS_IN_BIT_ARRAY;

    uint32_t host_id_index = host_id % BITS_IN_BIT_ARRAY;
    
    bit_array_arr[arr_num] = 
    BitArrSetOn(bit_array_arr[arr_num]);
        
    return  dhcp->subnet + host_id;
}

static result_t FreeAddrs(dhcp_t* dhcp, uint32_t host_id)
{
    bit_arr_t* bit_array_arr = (bit_arr_t*)dhcp->bit_map;

    uint32_t arr_num = host_id / BITS_IN_BIT_ARRAY;

    uint32_t host_id_index = host_id % BITS_IN_BIT_ARRAY;
    
    if (BitArrGetVal(bit_array_arr[arr_num], host_id_index) == 0)
    {
        return FAIL;
    }

    bit_array_arr[arr_num] = 
    BitArrSetOff(bit_array_arr[arr_num], host_id_index);

    return SUCCESS;
}

static uint32_t SearchFreeIp(dhcp_t* dhcp, uint32_t host_id)
{
    bit_arr_t* bit_array_arr = (bit_arr_t*)dhcp->bit_map;
    
    uint32_t bit_arr_len = (dhcp->host_id_mask + 1) / BITS_IN_BIT_ARRAY;

    uint32_t arr_num = host_id / BITS_IN_BIT_ARRAY;

    uint32_t host_id_index = host_id % BITS_IN_BIT_ARRAY;

    for (; arr_num < bit_arr_len; ++arr_num)
    {
        for (; host_id_index < BITS_IN_BIT_ARRAY; ++host_id_index)
        {
            if (BitArrGetVal(bit_array_arr[arr_num], host_id_index) == 0 )
            {
                return host_id;
            }
            ++host_id;
        }
        host_id_index = 0;
    }

    return NETWORK_ID;
}

static uint32_t ReadIpFromArray(const ip_t ip_arr)
{
    uint8_t flip_arr[BYTES_IN_IP] = {0};
    uint8_t i = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        flip_arr[i] = ip_arr[BYTES_IN_IP - 1 - i];
    }

    return (*(uint32_t*)(&flip_arr));
}

static void WriteIpToArray(ip_t ip_arr, uint32_t ip)
{
    uint8_t* ptr = (uint8_t*)&ip;

    uint8_t i = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        ip_arr[BYTES_IN_IP - 1 - i] = ptr[i];
    }
}

/**************************************()**************************************/
