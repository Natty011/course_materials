/******************************************************************************
*	Version 1.0
*   date 02/02 16:00
******************************************************************************/
#ifndef __CALCULATOR_H__             /* __CALCULATOR_H__  */
#define __CALCULATOR_H__             /* __CALCULATOR_H__  */

typedef enum
{
    SUCCESS = 0,
    MATH_ERROR = 1,
    SYNTAX_ERROR = 2,
    SYSTEM_ERROR = 3
} status_t;

/*calculator.c, calculator_test.c, calculator.h*/

/******************************************************************************
*   Name: Calculate
*   Description: evaluates arithmetical expression.
*   Arguments: 	* 'expression' - an arithmetical expression to calculate
*				* 'result' - result of calculation. 
*   Return: * SUCCESS (0) if calulation succeeded.
*           * MATH_ERROR (1) if expression contaians eligal calculations.
*           * SYNTAX_ERROR (2) if expression contains syntax error.
*           * SYSTEM_ERROR (3) if system calls involved in calculation fail.
******************************************************************************/
status_t Calculate(const char* expression, double* result);
#endif                               /* __CALCULATOR_H__  */



