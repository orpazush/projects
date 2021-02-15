/****************************************************************************
 * 						written by: Orpaz Houta								*
 * 						review: Alex Sevostyanov							*
 * 						Last update: 26.4.20 								*
 ***************************************************************************/

#ifndef __PQUEUE_H__
#define __PQUEUE_H__

typedef struct pqueue pqueue_t;

/*
 * A user's function
 * ----------------
 * compares between two given 'priority1' & 'priority2' and determines
 * who has the highest priority and should be DePQueue first
 *
 * returns: int, (+) 'priority1' has higher priority
 * 				 (-) 'priority2' has higher priority
 *				 (0) they are even
 *
 * The function in O(1) complications.
 */
typedef int (*cmp_func)(const void *priority1, const void *priority2);


/*
 * A user's function
 * ----------------
 * the function use to found if there is a match between two given 'data1' &
 * 'data2' acording to the user needs.
 *
 * returns: int, (1) - found match, (0) - no match
 *
 * The function in O(1) complications.
 */
typedef int (*is_match_func)(const void *data1, const void *data2);


/*
 * Function: PQueueCreate
 * ----------------
 * creates a new empty priority Queue (pqueue)
 *
 * cmp: cmp_func - a user's function (see details in line 13)
 *
 * returns: pqueue_t *, pointer to the pqueue or NULL in case of error
 *
 * time complexity: O(1)
 */
pqueue_t *PQueueCreate(cmp_func cmp);


/*
 * Function: PQueueDestroy
 * ----------------
 * destroy the given pqueue and frees all its allocated memory
 *
 * pqueue: pqueue_t *, pointer to the pqueue
 *
 * time complexity: O(n)
 */
void PQueueDestroy(pqueue_t *pqueue);


/*
 * Function: EnPQueue
 * ----------------
 * inserts a new element contain a given 'data' to the pqueue. the position of
 * the new element will be according the priority determine in the 'cmp_func'
 *
 * pqueue: pqueue_t *, pointer to the pqueue
 *
 * data: void *, the data of the new element
 *
 * returns: int, SUCCESS or FAIL (0 or 1)
 *
 * time complexity: O(n)
 */
int EnPQueue(pqueue_t *pqueue, void *data);


/*
 * Function: DePQueue
 * ----------------
 * Removes the element with the highest priority in the given 'pqueue'
 *
 * pqueue: pqueue_t *, pointer to the pqueue
 *
 * returns: none
 *
 * The function in O(1) complications.
 */
void DePQueue(pqueue_t *pqueue);


/*
 * Function: PQueuePeek
 * ----------------
 * peeks on the element with the highest priority in the given 'pqueue'
 *
 * pqueue: const pqueue_t *, pointer to the pqueue
 *
 * returns: the data of the element with the highest priority
 *
 * The function in O(1) complications.
 */
void *PQueuePeek(const pqueue_t *pqueue);


/*
 * Function: PQueueSize
 * ----------------
 * counts the number of elements in a given 'pqueue' container
 *
 * pqueue: const pqueue_t *, pointer to the pqueue
 *
 * returns: size_t, the number of elements in the 'pqueue' container
 *
 * time complexity: O(n)
 */
size_t PQueueSize(const pqueue_t *pqueue);


/*
 * Function: PQueueIsEmpty
 * ----------------
 * checks whether a given 'pqueue' container is empty or not
 *
 * pqueue: const pqueue_t *, pointer to the pqueue
 *
 * returns: int, return 1 if empty and 0 if not
 *
 * time complexity: O(1)
 */
int PQueueIsEmpty(const pqueue_t *pqueue);


/*
 * Function: PQueueClear
 * ------------------------
 * gets 'pqueue' and removes all its element until it's empty
 *
 * pqueue: const pqueue_t *, pointer to the pqueue
 *
 * returns: none
 *
 * The function in O(n) complications.
 */
void PQueueClear(pqueue_t *pqueue);


/*
 * Function: PQueueErase
 * -------------------------
 * seeks a specific element according to a given 'is_match' function and 'param'
 * and erase the first found element from the given 'pqueue' container
 *
 * pqueue: const pqueue_t *, pointer to the pqueue
 *
 * is_match: match_func_t, a user's function -
 *
 * param: void *, to be used in the 'is_match'
 *
 * returns: the element's data befor he was erased or NULL in case of no match
 *
 * time complexity: O(1)
 */
void *PQueueErase(pqueue_t *pqueue, is_match_func is_match, void *param);

#endif /* ifdef __PQUEUE_H__ */
