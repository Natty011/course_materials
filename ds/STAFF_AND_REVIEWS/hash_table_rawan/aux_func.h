#ifndef __AUX_FUNC_H__  /* __AUX_FUNC_H__   */
#define __AUX_FUNC_H__  /* __AUX_FUNC_H__   */


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
*   Description: Function callback for finding elements in a linked list
*   Arguments: 	* 'check_data' - Node element data to check
*				* 'user_param' - Optional user parameter
*   Return: Boolean value ( true = 1 or false = 0 )
* 
*  
*/	typedef int( *match_func_t )(void* check_data , void* user_param );
/* 
******************************************************************************/

/******************************************************************************
* 
*   Description: Function callback to modify all elements of the linked list
*   Arguments: 	* 'data' - Node element data
*				* 'user_param' - Optional user parameter 
*   Complexity: O(n)
*   Return: Boolean value ( success = 0 or fail = 1 )
* 
*
*/  typedef int( *operation_func_t )(void* data , void* user_param );
/*
******************************************************************************/

#endif                  /* __AUX_FUNC_H__ */
