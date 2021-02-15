/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Yonathan Bardugo								*
*					Last update : 23.5.20 									*
****************************************************************************/

 #ifndef __FSM_H__
 #define __FSM_H__

 #include "stack.h"

/*******************************************************************************
* Function:  calculate  |  Time complexity O(n) |  Memory complexity O(1)	   *
* ---------------------------------------------------------------------------- *
* take a string of arithmetic operations end calculates it					   *
*																			   *
* result - double *, will hold the result of the giving string				   *
* to_calculate - char *, the string to be calculate							   *
* 																			   *
* return - int, (0) if success                                                 *
* ERROR - (-1) - MATH_ERROR                                                    *
*  		- (-2) - SYNTAX_ERROR                                                  *
*       - (-3) - MALLOC_ERROR                                                  *
*******************************************************************************/
 int Calculate(double *result, char *to_calculate);

 #endif /* ifdef __FSM_H__ */
