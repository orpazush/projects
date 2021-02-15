/*****************************************************************************
 * 					written by: Orpaz Houta									 *
 * 					review: Izik Avinoam									 *
 * 					Last update: 17.5.20									 *
 ****************************************************************************/
 #ifndef __BST_H__
 #define __BST_H__

 #include  <stddef.h>     /* size_t */

 typedef struct bst_node *bst_iterator_t;
 typedef struct bst bst_t;

 /*****************************************************************************
 * A user's function                                                          *
 * -------------------------------------------------------------------------- *
 * compares between two given 'data1' & 'data2' and set                       *
 * the key which determines the precedence of the elements in the tree.       *
 *                                                                            *
 * returns: int, (0<) 'data1' will place befor 'data2'                        *
 * 				 (0>) 'data2' will place befor 'data1'                        *
 *				 (0) they are even                                            *
 *****************************************************************************/
 typedef int (*cmp_func_t)(const void *data1, const void *data2, void *param);

 /*****************************************************************************
 * A user's function                                                          *
 * -------------------------------------------------------------------------- *
 * activate some operation on elements values                                 *
 *                                                                            *
 * returns: int, (0) SUCCESS else (status set by the user)                    *
 *****************************************************************************/
 typedef int (*callback_func_t)(void *data, const void *param);


 /*****************************************************************************
 * Function:    BSTCreate                                                     *
 * -------------------------------------------------------------------------- *
 * creates a new empty binary sorted (search) tree.                           *
 *                                                                            *
 * direct: cmp_func_t - a user's function (see explenation above)             *
 * param: void *, for extentions                                              *
 *                                                                            *
 * returns: bst_t *, pointer to the BST or NULL in case allocation failed     *
 *                                                                            *
 * time complexity: O(1)                                                      *
 *****************************************************************************/
 bst_t *BSTCreate(cmp_func_t direct, void *param);

 /*****************************************************************************
 * Function:    BSTDestroy                                                    *
 * -------------------------------------------------------------------------- *
 * destroy the tree and frees all its allocated memory                        *
 *                                                                            *
 * bst: bst_t *, pointer to the BST to destroy                                *
 *                                                                            *
 * returns: NONE                                                              *
 *                                                                            *
 * time complexity: O(n)                                                      *
 *****************************************************************************/
 void BSTDestroy(bst_t *bst);

 /*****************************************************************************
 * Function:    BSTSize                                                       *
 * -------------------------------------------------------------------------- *
 * counts the number of elements whithin a given 'bst' container              *
 *                                                                            *
 * bst: const bst_t *, pointer to the bst                                     *
 *                                                                            *
 * returns: size_t, the number of elements in the 'bst' container             *
 *                                                                            *
 * time complexity: O(n)                                                      *
 *****************************************************************************/
 size_t BSTSize(const bst_t *bst);

 /*****************************************************************************
 * Function: BSTIsEmpty                                                       *
 * -------------------------------------------------------------------------- *
 * checks whether a given 'bst' container is empty or not                     *
 *                                                                            *
 * bst: const bst_t *, pointer to the bst                                     *
 *                                                                            *
 * returns: int, return (1) if empty and (0) if not                           *
 *                                                                            *
 * time complexity: O(1)                                                      *
 *****************************************************************************/
 int BSTIsEmpty(const bst_t *bst);

 /*****************************************************************************
 * Function:   BSTInsert                                                      *
 * -------------------------------------------------------------------------- *
 * inserts a new element to the tree. the element will be put in the right    *
 * position according to the directivs in the 'cmp_func_t' of the tree        *
 * NOTE - the balance of the tree determines by the order of the user inserts *
 *        and can affect on the performance of other functions                *
 *                                                                            *
 * bst: bst_t *, pointer to the bst                                           *
 * data: void *, the data of the new element                                  *
 *                                                                            *
 * returns: bst_iterator_t, the new element or an invalid iterator            *
 *          incase of failure in allocation or double data                    *
 *                                                                            *
 * time complexity: B - O(1) A - O(log n) W - O(n)                            *
 *****************************************************************************/
 bst_iterator_t BSTInsert(bst_t *bst, void *data);

 /*****************************************************************************
 * Function:    BSTRemove                                                     *
 * -------------------------------------------------------------------------- *
 * erase a given 'data' from a given 'bst'                                    *
 * NOTE - case the 'data' is not whithin the 'bst' it will search the tree    *
 *        but will erase nothing                                              *
 *                                                                            *
 * bst: bst_t *, pointer to the bst                                           *
 * data: void *, the data to be remove                                        *
 *                                                                            *
 * returns: NONE                                                              *
 *                                                                            *
 * time complexity: B - O(1)   W - O(n)                                       *
 *****************************************************************************/
 void BSTRemove(bst_t *bst, void *data);

 /*****************************************************************************
 * Function:  BSTBegin                                                        *
 * -------------------------------------------------------------------------- *
 * bst: bst_t *, pointer to the bst                                           *
 *                                                                            *
 * returns: the first element of a given 'bst' container according to the key *
 *          that has been set in the 'cmp_func_t' given when create.          *
 * NOTE - in case the 'bst' is empty it will return                           *
 *        an invalid iterator (see BSTEnd)                                    *
 *                                                                            *
 * time complexity: B - O(1)   W - O(n)                                       *                                                  *
 *****************************************************************************/
 bst_iterator_t BSTBegin(const bst_t *bst);

 /*****************************************************************************
 * Function:    BSTEnd                                                        *
 * -------------------------------------------------------------------------- *
 * Returns the past-the-end element in the 'bst' container.                   *
 * NOTE - It is not valid iterator and doesn't hold any valid data thus       *
 *        should be used as a terminator and nothing more.                    *
 *      - using this iterator as a parameter in other functions will cause    *
 *        undefined behaviour                                                 *
 *                                                                            *
 * bst: bst_t *, pointer to the bst                                           *
 *                                                                            *
 * returns: bst_iterator_t, past-the-end element                              *
 *                                                                            *
 * time complexity: O(1)                                                      *
 *****************************************************************************/
 bst_iterator_t BSTEnd(const bst_t *bst);

 /*****************************************************************************
 * Function:    BSTPrev                                                       *
 * -------------------------------------------------------------------------- *
 * iter: bst_iterator_t, the element comes after the wanted one               *
 *                                                                            *
 * returns: bst_iterator_t, the previous element of a given 'iter' according  *
 *          to the key that provided by the user when the bst created.        *
 *          or an invalid iterator if the given 'iter' is the first.          *
 *                                                                            *
 * time complexity: B - O(1)   W - O(n)                                       *                                                  *
 *****************************************************************************/
 bst_iterator_t BSTPrev(bst_iterator_t iter);

 /*****************************************************************************
 * Function:    BSTNext                                                       *
 * -------------------------------------------------------------------------- *
 * iter: bst_iterator_t, the element comes befor the wanted one               *
 *                                                                            *
 * returns: bst_iterator_t, the next element of a given 'iter' according      *
 *          to the key that provided by the user when the bst created.        *
 * NOTE - it is the terminator incase of last elements                        *                                                                           *
 *                                                                            *
 * time complexity: B - O(1)   W - O(n)                                       *                                                  *
 *****************************************************************************/
 bst_iterator_t BSTNext(bst_iterator_t iter);

 /*****************************************************************************
 * Function:    BSTIterIsEqual                                                *
 * -------------------------------------------------------------------------- *
 * compare between two given 'iter1' and 'iter2'                              *
 *                                                                            *
 * iter1: bst_iterator_t, iterator to compare                                 *
 * iter2: bst_iterator_t, iterator to compare                                 *
 *                                                                            *
 * returns: int, return (1) if they are the same or (0) if not                *
 *                                                                            *
 * time complexity: O(1)                                                      *
 *****************************************************************************/
 int BSTIterIsEqual(bst_iterator_t iter1, bst_iterator_t iter2);

 /*****************************************************************************
 * Function:    BSTGetData                                                    *
 * -------------------------------------------------------------------------- *
 * iter: bst_iterator_t, 'iter' to read it's data                             *
 *                                                                            *
 * returns: void *, the data of a given 'iter'                                *
 *                                                                            *
 * The function in O(1) complications.                                        *
 *****************************************************************************/
 void *BSTGetData(bst_iterator_t iter);

 /*****************************************************************************
 * Function:    BSTFind                                                       *
 * -------------------------------------------------------------------------- *
 * search for a given 'data' in the 'bst'                                     *
 *                                                                            *
 * bst: bst_t *, pointer to the bst                                           *
 * data: void *, the data to find in the tree                                 *
 *                                                                            *
 * returns: bst_iterator_t, an iterator that holds the given 'data' or an     *
 *          invalid iterator if not found                                     *
 *                                                                            *
 * time complexity: B - O(1) A - O(log n) W - O(n)                            *
 *****************************************************************************/
 bst_iterator_t BSTFind(const bst_t *bst, const void *data);

 /*****************************************************************************
 * Function:    BSTForEach                                                    *
 * -------------------------------------------------------------------------- *
 * executes a given 'CallBack' function upon all the elements whithin a given *
 * range 'from' to 'to' (not incloude the 'to' itself).                       *
 * NOTE - in case of error the function will stop but some of the elements    *
 * 		  might be already changed                                            *
 * 	    - 'from' and 'to' are must be of the given 'bst' else undefined       *
 *        behaviour occures.                                                  *                  *
 *                                                                            *
 * bst: bst_t *, pointer to the bst                                           *
 * from: bst_iterator_t, the start of the range                               *
 * to: bst_iterator_t, the end of the range                                   *
 * callback: callback_func_t, a user's function                               *
 * param: void *, a parameter to be used in 'CallBack'                        *
 *                                                                            *
 * returns: int, return (0) in success else the status returned from          *
 *          the 'callback' function                                           *
 *                                                                            *
 * time complexity: O(n)                                                      *
 *****************************************************************************/
 int BSTForEach(bst_iterator_t from, bst_iterator_t to,
 				callback_func_t CallBack, void *param);

 #endif /* ifdef __BST_H__ */
