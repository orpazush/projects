/****************************************************************************
 *					written by : Orpaz Houta								*
 * 					review : Tali Rephael									*
 * 					Last update : 19.4.20									*
 ***************************************************************************/

#ifndef __DLLIST_H__
#define __DLLIST_H__


typedef struct dllist_node *iterator_t;

typedef struct dllist dllist_t;

typedef int (*match_func_t)(const void *data, const void *param);

typedef int (*action_func_t)(void *data, void *param);

/*
* Function: DLListCreate
* --------------------
* creates a new empty doubly linked list of type dllist_t
*
* returns: dllist_t *, pointer to the list
*
* time complexity: O(1)
*/
dllist_t *DLListCreate(void);


/*
* Function: DLListDestroy
* --------------------
* destroy the list and frees all its allocated memory
*
* list: dllist_t *, pointer to the list
*
* returns: void
*
* time complexity: O(n)
*/
void DLListDestroy(dllist_t *list);


/*
* Function: DLListInsert
* --------------------
* insert a new element before a given iterator 'where'
*
* where: iterator_t, the location to put new element
*
* data: void *, the data of the new element
*
* returns: iterator_t, the new element
*
* time complexity: O(1)
*/
iterator_t DLListInsert(iterator_t where, void *data);


/*
* Function: DLListRemove
* --------------------
* erase the given element 'who'
*
* who: iterator_t, the element to remove
*
* returns: An iterator to the element that followed the erased element.
* NOTE - if the operation erased the last element in the 'list' it will be
* The an invalid iterator (see note in DLListEnd)
*
* time complexity: O(1)
*/
iterator_t DLListRemove(iterator_t who);


/*
* Function: DLListIsEmpty
* --------------------
* checks if a given  'list' container is empty
*
* list: const dllist_t *, pointer to the list
*
* returns: int, return 1 if empty and 0 if not empty
*
* time complexity: O(1)
*/
int DLListIsEmpty(const dllist_t *list);

/*
* Function: DLListSize
* --------------------
* counts the number of elements in a given  'list' container
*
* list: const dllist_t *, pointer to the list
*
* returns: size_t, the number of elements in the  'list' container
*
* time complexity: O(n)
*/
size_t DLListSize(const dllist_t *list);

/*
* Function: DLListBegin
* --------------------
* list: const dllist_t, pointer to the list
*
* returns: the first element of a given 'list' container
*
* time complexity: O(1)
*/
iterator_t DLListBegin(const dllist_t *list);


/*
* Function: DLListEnd
* --------------------
* Returns the past-the-end element in the  'list' container.
* NOTE - The past-the-end element is the theoretical element that would follow
* the last element in the list container. It is not valid iterator, and
* thus shall not be used as such.
*
* list: const dllist_t, pointer to the list
*
* returns: iterator_t, return the last element of the list
*
* time complexity: O(1)
*/
iterator_t DLListEnd(const dllist_t *list);

/*
* Function: DLListNext
* --------------------
* iterator: iterator_t, the element comes befor the wanted one
*
* returns: iterator_t, the next element of a given 'iterator'
*
* time complexity: O(1)
*/
iterator_t DLListNext(iterator_t iterator);

/*
* Function: DLListPrev
* --------------------
* iterator: iterator_t, the element comes after the wanted one
*
* returns: iterator_t, the previous element of a given 'iterator'
*
* time complexity: O(1)
*/
iterator_t DLListPrev(iterator_t iterator);

/*
* Function: DLListIsSameIterator
* --------------------
* compare between two given nodes pointed by 'iterator1' and 'iterator2'
*
* iterator1: iterator_t, iterator to compare
*
* iterator2: iterator_t, iterator to compare
*
* returns: int, return 1 if thay are the same or 0 if not
*
* time complexity: O(1)
*/
int DLListIsSameIterator(iterator_t iterator1, iterator_t iterator2);

/*
* Function: DLListGetData
* --------------------
* iterator: iterator_t, element to read it data from
* NOTE - trying to get an unset element will cause undefined behaviour
*
* returns: void *, the data of a given 'itetator'
*
* time complexity: O(1)
*/
void *DLListGetData(iterator_t iterator);

/*
* Function: DLListSetData
* --------------------
* sets a new given 'data' in a certain element pointed by 'iterator'
* NOTE - trying to set an empty list will cause undefined behaviour
*
* iterator: iterator_t, pointer to the element to set its data
*
* data: void *,the data value to set
*
* returns: void
*
* time complexity: O(1)
*/
void DLListSetData(iterator_t iterator, void *data);

/*
* Function: DLListPopFront
* --------------------
* removes the first element of the list
*
* list: dllist_t, pointer to the list
*
* returns: the data of the element befor it poped
*
* time complexity: O(1)
*/
void *DLListPopFront(dllist_t *list);


/*
* Function: DLListPopBack
* ----------------------
* removes the last element to a given list
*
* list: dllist_t, pointer to the list
*
* returns: the data of the element befor it poped
*
* time complexity: O(1)
*/
void *DLListPopBack(dllist_t *list);

/*
* Function: DLListPushFront
* --------------------
* inserts a new element to the begining of a given  'list' container
*
* list: dllist_t, pointer to the list
*
* data: void *, the data of the new element
*
* returns: iterator_t, return the new element
*
* time complexity: O(1)
*/
iterator_t DLListPushFront(dllist_t *list, void *data);

/*
* Function: DLListPushBack
* --------------------
* Adds a new element contain the given 'data' at the end of the list container,
* after its current last element.
*
* list: dllist_t, pointer to the list
*
* data: void *, the data of the new element
*
* returns: iterator_t, return the new element
*
* time complexity: O(1)
*/
iterator_t DLListPushBack(dllist_t *list, void *data);

/*
* Function: DLListFind
* --------------------
* gets range begins in 'from' and end with 'to', and runs on it the given
* function 'is_match' until it find the first match.
*
* from: iterator_t, the start of the range
*
* to: iterator_t, the end of the range
*
* is_match: match_func_t, a user's function - the function should match the
* prototype 'int is_match(const void *data, const void *param)' and should
* return int as the follows: (1) - found match, (0) - no match
* or (negative number) in case of error
*
* param: void *, the parameter to be compare with
*
* returns: iterator_t, the first match found or the end of the range if no
* found match
*
* time complexity: O(n)
*/
iterator_t DLListFind(iterator_t from, iterator_t to,
 								match_func_t is_match, const void *param);

/*
* Function: DLListForEach
* -----------------------
* runs an operation 'operate' upon all the elements in a given
* range 'from' to 'to', every element in it turn will be change by the 'operate'
* until the end of the range or case of error.
* NOTE 	- in case of error the function will stop but some of the elements
*         might already have been changed.
* 		- 'from' and 'to' are must be of the same list, the function does not
* protect from case they are not and it might cause an unwanted results.
*
* from: iterator_t, the start of the range
*
* to: iterator_t, the end of the range
*
* is_action: action_func_t, function from the user
*
* param: void *, a parameter to be used in 'is_action'
*
* returns: int, return (0) SUCCESS or the return value of is_action in case
                of error
*
* time complexity: O(n)
*/
int DLListForEach(iterator_t from, iterator_t to,
									action_func_t is_action, void *param);

/*
* Function: DLListSplice
* ----------------------
* Transfers a given range of elements 'from' to 'to' from one containor and
* place them in a new containor Befor a given 'where'
* This effectively inserts those elements into the new container and removes
* them from the last, altering the sizes of both containers.
* NOTE 	- the range includes all the elements between 'from' and 'to',
* including the element pointed by 'from' but not the one pointed by 'to'.
* 		- 'from' and 'to' are must be of the same list, the function does not
* protect from case they are not and it might cause an unwanted results.
*
* from: iterator_t, the start of the range
*
* to: iterator_t, the end of the range
*
* where: iterator_t, the position in the new containor to insert the elements
*
* returns: iterator_t, the last element of the range 'to'
*
* time complexity - O(1)
*/
iterator_t DLListSplice(iterator_t where, iterator_t from, iterator_t to);

/*
* Function: DLListMultiFind
* --------------------
* runs the function 'is_match' on a given range begins in 'from' and end with
* 'to' and copies all the found matches to a given 'found_list'
* NOTE- 'from' and 'to' are must be of the same list, the function does not
* protect from case they are not and it might cause an unwanted results.
*
* element whose the 'is_match' found as match
*
* from: iterator_t, the start of the range
*
* to: iterator_t, the end of the range
*
* is_match: match_func_t, a user's function - the function should match the
* prototype 'int is_match(const void *data, const void *param)' and should
* return int as follow: * (1) - found match, (0) - no match
* or (negative number) in case of error
*
* param: void *, a parameter to be used in 'is_match'
*
* returns: int, return (0) - if no error occured, (1) - error in DLListMultiFind
* (negative number) - the return value of is_match in case of error
*
* time complexity - O(n)
*/
int DLListMultiFind(iterator_t from, iterator_t to, match_func_t is_match,
									const void *param, dllist_t *found_list);

#endif /* ifdef __DLLIST_H__ */
/* (╯°□°）╯︵ ┻━┻ */
