/******************************************************************************
*	Version 1.0
*   Last Updated:   17/2/2025
*                   17:05
******************************************************************************/
#ifndef __HASH_TABLE_H__		/* __HASH_TABLE_H__      */
#define __HASH_TABLE_H__		/* __HASH_TABLE_H__      */

#include <stddef.h>		        /* size_t	        	 */
#include "aux_func.h"           /* match_func_t          */

typedef struct hash_table hash_table_t;

/******************************************************************************
* 
*   Description: Function to calculate a value's index in the hash-table
*   Arguments: * 'data' - Value to calculate
*              * 'size' - 
*   Return: Index in the hash-table
* 
*/  typedef size_t(*hash_func_t)(const void* value);
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
                                      match_func_t match_func, 
                                      size_t capacity);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Destroys a hash-table
*       Arguments: 'table' - Hash-table to destroy
*       Return: N\A
*       Complexity: O(n)
*       Notes: If 'table' is NULL, no operation will be performed
* 
*/      void HashTableDestroy(hash_table_t *table);
/*
******************************************************************************/

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
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Removes a value from the hash-table
*       Arguments: * 'table' - Hash-table to remove from
*                  * 'value' - Value to remove
*       Return: N\A
*       Complexity: O(1)
* 
*/      void HashTableRemove(hash_table_t *table, void *value);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Get the number of values in the hash-table
*       Arguments: 'table' - Hash-table to meassure
*       Return: The number of values in the hash-table
*       Complexity: O(k) (k = hash-table size)
* 
*/      size_t HashTableSize(const hash_table_t *table);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Check is a hash-table empty or not
*       Arguments: 'table' - Hash-table to check
*       Return: TRUE (1) if empty, FALSE (0) if not
*       Complexity: O(k) (k = hash-table size)
* 
*/      int HashTableIsEmpty(const hash_table_t *table);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Find value in a hash-table with it's equivalent value
*       Arguments: * 'table' - Hash-table to search
*                  * 'equivalent_value' - Equivalent value to search
*       Return: Returns the value or NULL if value not in hash-table
*       Complexity: O(1)
* 
*/      void *HashTableFind(const hash_table_t *table, void *equivalent_value);
/*
******************************************************************************/

/******************************************************************************
*
*       Description: Executes an operation function on every value
*       Arguments:
*       Return:
*       Complexity: O(k) (k = hash-table size)
*       Notes:
* 
*/      int HashTableForEach(hash_table_t *table, operation_func_t op_func, 
                             void *user_param);
/*
******************************************************************************/

#endif                          /* __HASH_TABLE_H__      */
