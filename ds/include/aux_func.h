#ifndef __AUX_FUNC_H__  /* __AUX_FUNC_H__   */
#define __AUX_FUNC_H__  /* __AUX_FUNC_H__   */

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
