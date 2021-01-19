/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg  						         *
 * 					Last update : 9.6.20									 *
 *---------------------------------------------------------------------------*
 * A heap data structure is a tree-based data structure that satisfies a     *
 * property called heap property. means that if A is a parent of B then the  *
 * key of A is ordered with respect to the key of B with the same ordering   *
 * applying across the heap. The element at the "top" of the heap (with no   *
 * parents) is called the root.                                              *
 ****************************************************************************/
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;
/*-------------------------A user's Functions--------------------------------*/
/*****************************************************************************
* the function use to found if there is a match between two given 'data1' &  *
* 'data2' acording to the user needs.                                        *
*                                                                            *
* returns: int, (1) - found match, (0) - no match                            *
*                                                                            *
* The function in O(1) complications.                                        *
*****************************************************************************/
typedef int (*is_match_t)(const void *data, const void *param);

/*****************************************************************************
* compares between two given 'data1' & 'data2' according to the user's needs *
* this function should be compatible to the cind of data restored in the 	 *                                                                           *
* heap                                                                       *
*                                                                            *
* returns: int, (0<) 'data1' is higher then 'data2'                          *
* 				(0>) 'data2' is higher then 'data1'                          *
*****************************************************************************/
typedef int (*cmp_func_t)(const void *data1, const void *data2);
/*---------------------------------------------------------------------------*/


/******************************************************************************
 * Function:  HeapCreate                                                      *
 * -------------------------------------------------------------------------- *
 * creates a new empty heap data structure                                    *
 *                                                                            *
 * cmp: cmp_func_t - a user's function (see details above)                    *
 *                                                                            *
 * returns: heap_t *, pointer to the heap or NULL in case of error            *
 *                                                                            *
 * time complexity: O(1)                                                      *
 ******************************************************************************/
heap_t *HeapCreate(cmp_func_t cmp);


/******************************************************************************
 * Function:  HeapDestroy                                                     *
 * -------------------------------------------------------------------------- *
 * destroy the given heap and frees all its allocated memory                  *
 * NOTE - nothing will happen if sending a NULL as a parameter                *
 *                                                                            *
 * heap: heap_t *, pointer to the heap                                        *
 *                                                                            *
 * time complexity: O(n)                                                      *
 ******************************************************************************/
void HeapDestroy(heap_t *heap);


/******************************************************************************
 * Function:  HeapPush                                                        *
 * -------------------------------------------------------------------------- *
 * inserts a new element contain a given 'data' to the 'heap'. the position of*
 * the new element will be according the order determines by the 'cmp_func_t' *
 * (given as parameter when create)                                           *
 * NOTE - the function might rearrange the elements within the heap so the    *
 *        the heap property will be kept                                      *
 *                                                                            *
 * heap: heap_t *, pointer to the heap                                        *
 * data: void *, the data of the new element                                  *
 *                                                                            *
 * returns: int, (0) if succeed or (1) if allocation failed                   *
 *                                                                            *
 * time complexity:  O(log n)                                                 *
 ******************************************************************************/
int HeapPush(heap_t *heap, void *data);


/******************************************************************************
 * Function:  HeapPop                                                         *
 * -------------------------------------------------------------------------- *
 * Removes the data of the root (the element on top) of a given 'heap'        *
 * NOTE - the function might rearrange the elements within the heap so the    *
 *        the heap property will be kept                                      *
 *      - in case of empty list, undefined behaviour will occure              *
 *                                                                            *
 * heap: heap_t *, pointer to the heap                                        *
 *                                                                            *
 * returns: none                                                              *
 *                                                                            *
 * time complexity:  O(log n)                                                 *
 ******************************************************************************/
void HeapPop(heap_t *heap);


/******************************************************************************
 * Function:  HeapPeek                                                        *
 * -------------------------------------------------------------------------- *
 * peeks on the data of the root (the element on top) of a given 'heap'       *
 * NOTE - sending this function an empty heap will cause undefined behaviour  *
 *                                                                            *
 * heap: const heap_t *, pointer to the heap                                  *
 *                                                                            *
 * returns: void *, the data of the root                                      *
 *                                                                            *
 * time complexity:  O(1)                                                     *
 ******************************************************************************/
void *HeapPeek(const heap_t *heap);


/******************************************************************************
 * Function:  HeapSize                                                        *
 * -------------------------------------------------------------------------- *
 * counts the number of elements in a given 'heap' container                  *
 *                                                                            *
 * heap: const heap_t *, pointer to the heap                                  *
 *                                                                            *
 * returns: size_t, the number of elements in the 'heap' container            *
 *                                                                            *
 * time complexity: O(1)                                                      *
 ******************************************************************************/
size_t HeapSize(const heap_t *heap);


/******************************************************************************
 * Function:  HeapIsEmpty                                                     *
 * -------------------------------------------------------------------------- *
 * checks whether a given 'heap' container is empty or not                    *
 *                                                                            *
 * heap: const heap_t *, pointer to the heap                                  *
 *                                                                            *
 * returns: int, return (1) if empty and (0) if not                           *
 *                                                                            *
 * time complexity: O(1)                                                      *
 ******************************************************************************/
int HeapIsEmpty(const heap_t *heap);


/******************************************************************************
 * Function:  HeapRemove                                                      *
 * -------------------------------------------------------------------------- *
 * seeks a specific element according to a given 'is_match' function and      *
 * 'param', and erase the first found element from the given 'heap' container *
 * NOTE - the function might rearrange the elements within the heap so the    *
 *        the heap property will be kept                                      *
 *      - if the given 'heap' is empty or no element found match the functoin *
 *        will erase nothing and return NULL                                  *
 *                                                                            *
 * heap: heap_t *, pointer to the heap                                        *
 * is_match: match_func_t, a user's function (see above)                      *
 * param: const void *, to be used in the 'is_match'                          *
 *                                                                            *
 * returns: the element's data befor he was erased or NULL in case of no match*
 *          or empty heap                                                     *
 *                                                                            *
 * time complexity: O(log n)                                                  *
 ******************************************************************************/
void *HeapRemove(heap_t *heap, is_match_t is_match, const void *param);


#endif /* __HEAP_H__ */
