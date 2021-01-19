/****************************************************************************
 * 						written by : orpaz houta							*
 *						review : Aviv Levanon								*
 * 						Last update : 21.4.20								*
 ***************************************************************************/

#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include "dllist.h"	/* iterator_t */

typedef struct sorted_list sorted_list_t;

typedef struct sorted_list_iterator
{
	iterator_t sort_iter;

#ifndef NDEBUG
	sorted_list_t *list;
#endif

}sortl_iterator_t;


/*
 * A user's function
 * ----------------
 * compares between two given 'priority1' & 'priority2' and determines
 * who has the highest priority and should be DePQueue first
 *
 * returns: int, (+) 'priority1' has higher priority
 * 				 (-) 'priority2' has higher priority
				 (0) they are even
 *
 * time complexity: O(1)
 */
typedef int (*is_before_func)(const void *data1, const void *data2,
														const void *param);
/*
 * A user's function
 * ----------------
 * activate some operation on elements values
 *
 * returns: int, (0) SUCCESS (+) ERROR
 *
 * time complexity: O(1)
 */
typedef int (*operation_func)(void *data, void *param);


/*
* Function: <SortedListCreate>
* --------------------
* creates a new empty sorted linked list of type sorted_list_t
*
* func: is_before_func - a user's function
*
* returns: sorted_list_t *, pointer to the list or NULL in case of error
*
* time complexity: O(1)
*/
sorted_list_t *SortedListCreate(is_before_func func, void *param);


/*
* Function: <SortedListDestroy>
* --------------------
* destroy the list and frees all its allocated memory
*
* list: sorted_list_t *, pointer to the list
*
* time complexity: O(n)
*/
void SortedListDestroy(sorted_list_t *list);


/*
* Function: <SortedListInsert>
* --------------------
* insert a new element to the list. the element will be put in the right
* position according to the directivs in the 'is_befor_func' of the list
*
* list: sorted_list_t *, pointer to the list
*
* data: void *, the data of the new element
*
* returns: sortl_iterator_t, the new element or an invalid iterator
* incase of failure
*
* time complexity: O(n)
*/
sortl_iterator_t SortedListInsert(sorted_list_t *list, void* data);


/*
* Function: <SortedListRemove>
* --------------------
* erase the given element 'iterator'
*
* iterator: sortl_iterator_t, the element to remove
*
* returns: An iterator to the element that followed the erased element.
* NOTE - if the operation erased the last element in the 'list' it will return
* 		 an invalid iterator (see note in SortedListEnd)
*
* time complexity: O(1)
*/
sortl_iterator_t SortedListRemove(sortl_iterator_t iterator);


/*
* Function: <SortedListSize>
* --------------------
* counts the number of elements in a given 'list' container
*
* list: const sorted_list_t *, pointer to the list
*
* returns: size_t, the number of elements in the 'list' container
*
* time complexity: O(n)
*/
size_t SortedListSize(const sorted_list_t *list);


/*
* Function: <SortedListIsEmpty>
* --------------------
* checks if a given  'list' container is empty
*
* list: const sorted_list_t *, pointer to the list
*
* returns: int, return 1 if empty and 0 if not empty
*
* time complexity: O(1)
*/
int SortedListIsEmpty(const sorted_list_t *list);


/*
* Function: <SortedListGetData>
* --------------------
* iterator: sortl_iterator_t, element to read it data from
*
* returns: void *, the data of a given 'itetator'
*
* time complexity: O(1)
*/
void *SortedListGetData(sortl_iterator_t iterator);


/*
* Function: <SortedListBegin>
* ---------------------------
* list: const sorted_list_t, pointer to the list
*
* returns: the first element of a given 'list' container
* NOTE - in case the 'list' is empty it will return
*		 an invalid iterator (see note in SortedListEnd)
*
* time complexity: O(1)
*/
sortl_iterator_t SortedListBegin(const sorted_list_t *list);


/*
* Function: <SortedListEnd>
* --------------------
* Returns the past-the-end element in the 'list' container.
* NOTE - The past-the-end element is the theoretical element that would follow
* 		 the last element in the list container. It is not valid iterator, and
*		 thus shall not be used as such.
*
* list: const sorted_list_t, pointer to the list
*
* returns: sortl_iterator_t, past-the-end element
*
* time complexity: O(1)
*/
sortl_iterator_t SortedListEnd(const sorted_list_t *list);

/*
* Function: <SortedListNext>
* --------------------
* iterator: sortl_iterator_t, the element comes befor the wanted one
*
* returns: sortl_iterator_t, the next element of a given 'iterator'
*
* time complexity: O(1)
*/
sortl_iterator_t SortedListNext(sortl_iterator_t iterator);


/*
* Function: <SortedListPrev>
* --------------------
* iterator: sortl_iterator_t, the element comes after the wanted one
*
* returns: sortl_iterator_t, the previous element of a given 'iterator'
*
* time complexity: O(1)
*/
sortl_iterator_t SortedListPrev(sortl_iterator_t iterator);


/*
* Function: <SortedListIsEqual>
* --------------------
* compare between two given nodes pointed by 'iterator1' and 'iterator2'
*
* iterator1: sortl_iterator_t, iterator to compare
*
* iterator2: sortl_iterator_t, iterator to compare
*
* returns: int, return 1 if thay are the same or 0 if not
*
* time complexity: O(1)
*/
int SortedListIsEqual(sortl_iterator_t iterator1, sortl_iterator_t iterator2);


/*
* Function: <SortedListPopFront>
* --------------------
* removes the first element of the list
*
* list: sorted_list_t, pointer to the list
*
* returns: the data of the element befor it poped
*
* time complexity: O(1)
*/
void *SortedListPopFront(sorted_list_t *list);

/*
* Function: <SortedListPopBack>
* --------------------
* removes the last element to a given list
*
* list: sorted_list_t, pointer to the list
*
* returns: the data of the element befor it poped
*
* time complexity: O(1)
*/
void *SortedListPopBack(sorted_list_t *list);


/*
* Function: <SortedListForEach>
* --------------------
* runs an operation 'operate' on all the elements of a given
* range 'from' to 'to', every element in it turn will be change by the 'operate'
* until the end of the range or case of error.
* NOTE - in case of error the function will stop but some of the elements
* 		 might already be changed.
* 	   - 'from' and 'to' are must be of the same list, the function does not
* 		 protect from case they are not and it might cause an unwanted results.
*
* from: sortl_iterator_t, the start of the range
*
* to: sortl_iterator_t, the end of the range
*
* operate: action_func_t,
*
* param: void *, a parameter to be used in 'operate'
*
* returns: int, return SUCCESS or FAIL (0 or 1)
*
* time complexity: O(n)
*/
int SortedListForEach(sortl_iterator_t from, sortl_iterator_t to,
										 operation_func operate,void *param);


/*
* Function: <SortedListFind>
* --------------------
* gets range begins in 'from' and end with 'to', and seeks for iterator contains
* the same data as the 'param'.
* NOTE - 'from' and 'to' are must be of the same list, the function does not
* 		 protect from case they are not and it might cause an unwanted results.
*
* from: sortl_iterator_t, the start of the range
*
* to: sortl_iterator_t, the end of the range
*
* list: sorted_list_t, pointer to the list
*
* param: void *, the parameter to be compare with
*
* returns: sortl_iterator_t, the first match found or the end of the range if no
* found match
*
* time complexity: O(n)
*/
sortl_iterator_t SortedListFind(sortl_iterator_t from,
			sortl_iterator_t to, sorted_list_t *list, void *data_to_find);


/*
* Function: <SortedListFindIf>
* --------------------
* gets range begins in 'from' and end with 'to', and runs on it the given
* function 'is_match' until it find the first match.
* NOTE - 'from' and 'to' are must be of the same list, the function does not
* 		 protect from case they are not and it might cause an unwanted results.
*
* from: sortl_iterator_t, the start of the range
*
* to: sortl_iterator_t, the end of the range
*
* is_match: match_func_t, a user's function - the function should match the
* prototype 'int func_name(const void *data, const void *param)' and should
* return int as follow: * (1) - found match, (0) - no match or (-) error
*
* param: void *, the parameter to be compare with
*
* returns: sortl_iterator_t, the first match found or the end of the range if no
* found match
*
* time complexity: O(n)
*/
sortl_iterator_t SortedListFindIf(sortl_iterator_t from, sortl_iterator_t to,
											match_func_t is_match, void *param);


/*
* Function: <SortedListMerge>
* --------------------
* Merges 'list2' into 'list1' by transferring all of its elements at their
* respective ordered positions into the container. This effectively removes all
* the elements in list2 (which becomes empty), and inserts them into their
* ordered position within the container of list1 The operation is performed
* without constructing nor destroying any element, they are transferred.
* NOTE - both containers shall be already ordered by the same sorting
* 		 function 'is_befor_func'.
*
* list1: sorted_list_t *, the destination list to insert to
*
* list2: sorted_list_t *, list to be insert into 'list1'
*
* time complexity: O(n+m)
*/
void SortedListMerge(sorted_list_t *list1, sorted_list_t *list2);


#endif /* ifdef __SORTED_LIST_H__ */
