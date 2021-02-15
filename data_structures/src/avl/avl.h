/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Izik Avinoam    								*
*					Last update : 2.6.20 									*
****************************************************************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct avl avl_t;

/* The options to travers the tree in 'AVLForEach' function. */
typedef enum order
{
    PREORDER,
    INORDER,
    POSTORDER
}order_t;

/*****************************************************************************
* A user's function                                                          *
* -------------------------------------------------------------------------- *
* activates some operation on elements values                                *
*                                                                            *
* returns: int, (0) if succeed or (+) status set by the user                 *
*****************************************************************************/
typedef int (*callback_func_t)(void *data1, void *param);

/*****************************************************************************
* A user's function                                                          *
* -------------------------------------------------------------------------- *
* compares between two given 'data1' & 'data2' and set                       *
* the key which determines the precedence of the elements in the tree.       *
*                                                                            *
* returns: int, (0<) 'data1' will place before 'data2'                        *
* 				(0>) 'data2' will place before 'data1'                        *
*****************************************************************************/
typedef int (*cmp_func_t)(const void *data1, const void *data2, void *param);


/*****************************************************************************
* Function:    AVLCreate                                                     *
* -------------------------------------------------------------------------- *
* creates a new empty balanced binary (search) tree.                         *
*                                                                            *
* cmp: cmp_func_t - a user's function (see explenation above)                *
* param: void *, for extentions                                              *
*                                                                            *
* returns: avl_t *, pointer to the AVL or error                              *
* error: (NULL) in case allocation failed                                    *
*                                                                            *
* time complexity: O(1)                                                      *
*****************************************************************************/
avl_t *AVLCreate(cmp_func_t cmp, void *param);


/*****************************************************************************
* Function:    AVLDestroy                                                    *
* -------------------------------------------------------------------------- *
* destroys the tree and frees all its allocated memory                       *
*                                                                            *
* avl: avl_t *, pointer to the AVL to destroy                                *
*                                                                            *
* returns: NONE                                                              *
*                                                                            *
* time complexity: O(n)                                                      *
*****************************************************************************/
void AVLDestroy(avl_t *avl);


/*****************************************************************************
* Function:    AVLRemove                                                     *
* -------------------------------------------------------------------------- *
* erases a given 'data' from a given 'avl'                                   *
* NOTE - case the 'data' is not whithin the 'avl' it will search the tree    *
*        but will erase nothing                                              *
*      - trying to remove data which exist in the tree more then twice will  *
*        cause undefined behaviour                                           *
*      - Be aware that after removing an element the place of other elements *
*		 in the tree may change.                                   			 *
*                                                                            *
* avl: avl_t *, pointer to the avl                                           *
* data: void *, the data to remove                                           *
*                                                                            *
* returns: NONE                                                              *
*                                                                            *
* time complexity: W - O(log n)                                              *
*****************************************************************************/
void AVLRemove(avl_t *avl, const void *data);


/*****************************************************************************
* Function:   AVLInsert                                                      *
* -------------------------------------------------------------------------- *
* inserts a new element to the tree. the element will be put in the right    *
* position according to the directivs in the 'cmp_func_t' of the tree        *
* NOTE - Be aware that after insert a new element the place of other elements*
*		 in the tree may change.                                   			 *
*                                                                            *
* avl: avl_t *, pointer to the avl                                           *
* data: void *, the data of the new element                                  *
*                                                                            *
* returns: int, (0) success or (1) in case allocation failed                 *
*                                                                            *
* time complexity: W - O(log n)                                              *
*****************************************************************************/
int AVLInsert(avl_t *avl, void *data);


/******************************************************************************
 * Function:  AVLHeight                                                       *
 * ----------------                                                           *
 * avl: const avl_t *, pointer to the avl                                     *
 *                                                                            *
 * returns: size_t, the longest branch of the AVLSize                         *
 * NOTE - this is a self balance tree so it's hight can be at most            *
 *        1.44*log(n + 2) - 0.328                                             *
 *      - sending an empty avl as parameter will cause undefined behaviour    *
 *                                                                            *
 * time complexity: O(1)                                                      *
 ******************************************************************************/
size_t AVLHeight(const avl_t *avl);


/*****************************************************************************
* Function:    AVLSize                                                       *
* -------------------------------------------------------------------------- *
* counts the number of elements whithin a given 'avl'                        *
*                                                                            *
* avl: const avl_t *, pointer to the avl                                     *
*                                                                            *
* returns: size_t, the number of elements in the 'avl'                       *
*                                                                            *
* time complexity: O(n)                                                      *
*****************************************************************************/
size_t AVLSize(const avl_t *avl);


/*****************************************************************************
* Function: AVLIsEmpty                                                       *
* -------------------------------------------------------------------------- *
* checks whether a given 'avl' is empty or not                               *
*                                                                            *
* avl: const avl_t *, pointer to the avl                                     *
*                                                                            *
* returns: int, return (1) if empty and (0) if not                           *
*                                                                            *
* time complexity: O(1)                                                      *
*****************************************************************************/
int AVLIsEmpty(const avl_t *avl);


/*****************************************************************************
* Function:    AVLFind                                                       *
* -------------------------------------------------------------------------- *
* search for a given 'data' in the 'avl'                                     *
*                                                                            *
* avl: avl_t *, pointer to the avl                                           *
* data: void *, the data to find in the tree                                 *
*                                                                            *
* returns: the found 'data' or NULL in case not found                        *
*                                                                            *
* time complexity: W - O(log n)                                              *
*****************************************************************************/
void *AVLFind(const avl_t *avl, const void *data);


/*****************************************************************************
* Function:    AVLForEach                                                    *
* -------------------------------------------------------------------------- *
* executes a given 'func' upon all the elements whithin a given              *
* tree 'avl' in a specific 'order' by the user choise.                       *
* NOTE - in case of error the function will stop immedietely                 *
*      - the order of the elements does not                               	 *
*		 changes after using that function on the elements. 	             *
*		 Its the user responsibility to make sure that the 		             *
*		 hierarchy between the elements preserved.			                 *
*                                                                            *
* avl: avl_t *, pointer to the avl                                           *
* func: callback_func_t, a user's function                                   *
* param: void *, a parameter to be used in 'CallBack'                        *
* order: order_t, specifies the order in which func will operate on the      *
* elements (see enum order_t above)                                          *
*                                                                            *
* returns: int, return (0) in success else error                             *
* error: (-1) NO_SUCH_ORDER                                                  *
*        or the status returned from the 'callback' function                 *
*                                                                            *
* time complexity: O(n)                                                      *
*****************************************************************************/
int AVLForEach(avl_t *avl, callback_func_t func, void* param, order_t order);

#endif /* __AVL_H__ */
