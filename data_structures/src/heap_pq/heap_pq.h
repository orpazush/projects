/****************************************************************************
 * 						written by: Orpaz Houta								*
 * 						review: Alex Sevostyanov							*
 * 						Last update: 26.4.20 								*
 ***************************************************************************/

#ifndef __HEAP_PQ_H__
#define __HEAP_PQ_H__

typedef struct heap_pq heap_pq_t;

/*
 * A user's function
 * ----------------
 * compares between two given 'priority1' & 'priority2' and determines
 * who has the highest priority and should be HeapDePQ first
 *
 * returns: int, (0<) 'priority1' has higher priority
 * 				 (0<) 'priority2' has higher priority
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
 * Function: HeapPQCreate
 * ----------------
 * creates a new empty priority Queue (heap_pq)
 *
 * cmp: cmp_func - a user's function (see details in line 13)
 *
 * returns: heap_pq_t *, pointer to the heap_pq or NULL in case of error
 *
 * time complexity: O(1)
 */
heap_pq_t *HeapPQCreate(cmp_func cmp);


/*
 * Function: HeapPQDestroy
 * ----------------
 * destroy the given heap_pq and frees all its allocated memory
 *
 * heap_pq: heap_pq_t *, pointer to the heap_pq
 *
 * time complexity: O(n)
 */
void HeapPQDestroy(heap_pq_t *heap_pq);


/*
 * Function: HeapEnPQ
 * ----------------
 * inserts a new element contain a given 'data' to the heap_pq. the position of
 * the new element will be according the priority determine in the 'cmp_func'
 *
 * heap_pq: heap_pq_t *, pointer to the heap_pq
 *
 * data: void *, the data of the new element
 *
 * returns: int, SUCCESS or FAIL (0 or 1)
 *
 * time complexity: O(n)
 */
int HeapEnPQ(heap_pq_t *heap_pq, void *data);


/*
 * Function: HeapDePQ
 * ----------------
 * Removes the element with the highest priority in the given 'heap_pq'
 *
 * heap_pq: heap_pq_t *, pointer to the heap_pq
 *
 * returns: none
 *
 * The function in O(1) complications.
 */
void HeapDePQ(heap_pq_t *heap_pq);


/*
 * Function: HeapPQPeek
 * ----------------
 * peeks on the element with the highest priority in the given 'heap_pq'
 *
 * heap_pq: const heap_pq_t *, pointer to the heap_pq
 *
 * returns: the data of the element with the highest priority
 *
 * The function in O(1) complications.
 */
void *HeapPQPeek(const heap_pq_t *heap_pq);


/*
 * Function: HeapPQSize
 * ----------------
 * counts the number of elements in a given 'heap_pq' container
 *
 * heap_pq: const heap_pq_t *, pointer to the heap_pq
 *
 * returns: size_t, the number of elements in the 'heap_pq' container
 *
 * time complexity: O(n)
 */
size_t HeapPQSize(const heap_pq_t *heap_pq);


/*
 * Function: HeapPQIsEmpty
 * ----------------
 * checks whether a given 'heap_pq' container is empty or not
 *
 * heap_pq: const heap_pq_t *, pointer to the heap_pq
 *
 * returns: int, return 1 if empty and 0 if not
 *
 * time complexity: O(1)
 */
int HeapPQIsEmpty(const heap_pq_t *heap_pq);


/*
 * Function: HeapPQClear
 * ------------------------
 * gets 'heap_pq' and removes all its element until it's empty
 *
 * heap_pq: const heap_pq_t *, pointer to the heap_pq
 *
 * returns: none
 *
 * The function in O(n) complications.
 */
void HeapPQClear(heap_pq_t *heap_pq);


/*
 * Function: HeapPQErase
 * -------------------------
 * seeks a specific element according to a given 'is_match' function and 'param'
 * and erase the first found element from the given 'heap_pq' container
 *
 * heap_pq: const heap_pq_t *, pointer to the heap_pq
 *
 * is_match: match_func_t, a user's function -
 *
 * param: void *, to be used in the 'is_match'
 *
 * returns: the element's data befor he was erased or NULL in case of no match
 *
 * time complexity: O(1)
 */
void *HeapPQErase(heap_pq_t *heap_pq, is_match_func is_match, void *param);

#endif /* ifdef __HEAP_PQ_H__ */
