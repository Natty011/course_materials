/******************************************************************************
*	Version 0.1
*   Last Updated:   1/1/1970
*                   00:00
******************************************************************************/
#ifndef __HASH_TABLE_H__		/* __HASH_TABLE_H__      */
#define __HASH_TABLE_H__		/* __HASH_TABLE_H__      */

#include <stddef.h>		        /* size_t	        	 */

typedef struct hash_table hash_table_t;

/******************************************************************************
* 
*   Description: Function to calculate a value's index in the hash-table
*   Arguments: * 'data' - Value to calculate
*              * 'size' - 
*   Return: Index in the hash-table
*  typedef size_t(*hash_func_t)(void* data, void* user_param);
*/  typedef size_t(*hash_func_t)(const void* value, size_t size);
/*
******************************************************************************/

/******************************************************************************
* 
*   Description: Function to compare two data values
*   Arguments: 	* 'check_data' - Current node data
*   			* 'new_data' - Data to compare to
*   Return: Comparison value
*           >0  - 'check_data' is larger than 'new_data'
*           <0  - 'check_data' is smaller than 'new_data'
*           ==0 - 'check_data' is equal to 'new_data'
* 
*/  typedef int(*cmp_func_t)( void* check_data,  void* new_data);
/* 
******************************************************************************/

/******************************************************************************
* 
*   Description: Function callback to modify all elements of the linked list
*   Arguments: 	* 'data' - Node element data
*	            * 'user_param' - Optional user parameter 
*   Return: Boolean value ( success = 0 or fail = 1 )
* 
*/  typedef int(*op_func_t)(void* data, void* user_param);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Creates a hash-table
*       Arguments: * 'hash_func' - Hash function to calculate indexes
*                  * 'cmp_func' - Comparison function for values
*                  * 'size' - Size of the hash-table
*       Return: Pointer to the hash-table manager struct, or NULL if failed
* 
*/      hash_table_t *HashTableCreate(hash_func_t hash_func,
                                      cmp_func_t cmp_func, 
                                      size_t size);

/******************************************************************************
*
*       Description: Destroys a hash-table
*       Arguments: 'table' - Hash-table to destroy
*       Return: N\A
*       Complexity: O(n)
*       Notes: If 'table' is NULL, no operation will be performed
* 
*/      void HashTableDestroy(hash_table_t *table);

/******************************************************************************
*
*       Description: Inserts a value into the hash-table
*       Arguments: * 'table' - Hash-table to insert to
*                  * 'value' - Value to insert
*       Return: SUCCESS (0) or FAILURE (1) if failed
*       Complexity: O(1)
*       Note: 'value' cannot be set to NULL
* 
*/      int HashTableInsert(hash_table_t *table, void *value);

/******************************************************************************
*
*       Description: Removes a value from the hash-table
*       Arguments: * 'table' - Hash-table to remove from
*                  * 'value' - Value to remove
*       Return: N\A
*       Complexity: O(1)
* 
*/      void HashTableRemove(hash_table_t *table, void *value);

/******************************************************************************
*
*       Description: Get the number of values in the hash-table
*       Arguments: 'table' - Hash-table to meassure
*       Return: The number of values in the hash-table
*       Complexity: O(k) (k = hash-table size)
* 
*/      size_t HashTableSize(const hash_table_t *table);

/******************************************************************************
*
*       Description: Check is a hash-table empty or not
*       Arguments: 'table' - Hash-table to check
*       Return: TRUE (1) if empty, FALSE (0) if not
*       Complexity: O(k) (k = hash-table size)
* 
*/      int HashTableIsEmpty(const hash_table_t *table);

/******************************************************************************
*
*       Description: Find value in a hash-table with it's equivalent value
*       Arguments: * 'table' - Hash-table to search
*                  * 'equivalent_value' - Equivalent value to search
*       Return: Returns the value or NULL if value not in hash-table
*       Complexity: O(1)
* 
*/      void *HashTableFind(const hash_table_t *table, void *equivalent_value);

/******************************************************************************
*
*       Description: Executes an operation function on every value
*       Arguments:
*       Return:
*       Complexity: O(k) (k = hash-table size)
*       Notes:
* 
*/      int HashTableForEach(hash_table_t *table, op_func_t op_func, 
                             void *user_param);
/*
******************************************************************************/

#endif                           /* __HASH_TABLE_H__     */


