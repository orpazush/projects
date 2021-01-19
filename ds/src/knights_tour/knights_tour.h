/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Chanan Komar                              *
 *                      coding date - 17-06-2020                              *
 *----------------------------------------------------------------------------*
 * The Knights Tour Problem is a famouse Riddle which in the knight is placed *
 * on the first square of an empty board and moving according to the rules of *
 * chess, and must visit each square exactly once.                            *
 ******************************************************************************/

#ifndef __KNIGHTS_TOUR_H__
#define __KNIGHTS_TOUR_H__


/******************************************************************************
 * Function:  KnightsTour                                                     *
 * ---------------------------------------------------------------------------*
 * the function solves the Knights Tour Problem begins in the square in the   *
 * given 'row' and 'column' and document the steps of the knight's tour in    *
 * the given 'path'                                                           *
 * 																			  *
 * row - int, the row which from the tour begins                  			  *
 * column - int , the column which from the tour begins   				      *
 * path - int *, pointer to an array to be fill with the knight's steps of    *
 *               the solution.                                                *
 * NOTE - the path should hold at least the size of the board	   	      	  *
 * 																			  *
 * return - int, (0) if success (1) if failed                                 *
 *****************************************************************************/
int KnightsTour(int row, int column, int path[]);

#endif /* ifdef __KNIGHTS_TOUR_H__ */
