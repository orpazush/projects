/****************************************************************************
 *					written by : orpaz houta								*
 *					review : chanan komar									*
 *					Last update : 12.4.20									*
 ***************************************************************************/

#ifndef __SLLIST_H__ 
#define __SLLIST_H__ 

typedef struct sllist_node *iterator_t;

typedef struct list list_t;

/* refernce to the user function */
typedef int (*match_func_t)(const void *data, void *param);
/* refernce to the user function */
typedef int (*action_func_t)(void *data, void *param);

enum status{SUCCESS, FAILURE};
/*
* Function: SLListCreate 
* --------------------------
* creates a new empty linked list of type list_t 
*
* returns: list_t *, pointer to the list 
*
* time complexity: O(1)
*/
list_t *SLListCreate(void); 


/*
* Function: SLListDestroy 
* ----------------------
* frees all the allocated memory to the list
*
* list: list_t *, pointer to the first element of the list 
*
* returns: void
*
* time complexity: O(n)
*/
void SLListDestroy(list_t *list); 


/*
* Function: SLListInsert 
* --------------------------
* insert a new element before the given iterator 'where'
*
* where: iterator_t, the location of the new element 
*
* data: void *, the data that we want to put in 
*
* returns: iterator_t, return pointer to the new element 
*
* time complexity: O(1)
*/
iterator_t SLListInsert(iterator_t where, void *data); 


/*
* Function: SLListRemove 
* --------------------------
* removes the given element 'who' from the list
* NOTE - it is not possible to remove from the end of the list, in case of
* trying the function will return NULL
*
* who: iterator_t, the element to be remove 
*
* returns: iterator_t, pointer to the next element or NULL incase list is empty 
*
* time complexity: O(1)
*/
iterator_t SLListRemove(iterator_t who); 


/*
* Function: SLListBegin 
* -----------------------
* return the first element of a given 'list'
*
* list: const list_t, pointer to the list
*
* returns: iterator_t, return the first element of the list 
*
* time complexity: O(1)
*/
iterator_t SLListBegin(const list_t *list); 


/*
* Function: SLListEnd 
* -----------------------
* return the last element of a given 'list'
*
* list: const list_t, pointer to the list
*
* returns: iterator_t, return the last element of the list 
*
* time complexity: O(1)
*/
iterator_t SLListEnd(const list_t *list); 


/*
* Function: SLListIterIsEqual 
* -------------------------
* compare between data of two given nodes pointed by 'iterator1' and 'iterator2'
*
* iterator1: const iterator_t, element to compare 
*
* iterator2: const iterator_t, element to compare 
*
* returns: int, return SUCCESS or FAIL (0 or 1 ) 
*
* time complexity: O(1)
*/
int SLListIterIsEqual(const iterator_t iterator1, const iterator_t iterator2); 


/*
* Function: SLListNext 
* -----------------------
* iterator: const iterator_t, pointer to the iterator befor the wanted one
*
* returns: iterator_t, the next element of a given 'iterator' 
*
* time complexity: O(1)
*/
iterator_t SLListNext(const iterator_t iterator); 


/*
* Function: SLListGetData 
* -----------------------
* iterator: const iterator_t, element to read it data from
* NOTE - trying to get an unset element might cause undefined behaviour
*
* returns: void *, the data of a given 'itetator'
*
* time complexity: O(1)
*/
void *SLListGetData(const iterator_t iterator); 


/*
* Function: SLListSetData
* ----------------------------------
* sets a new given 'data' in a certain element pointed by 'iterator' 
* NOTE - it is not possible to set an empty list
* 
* iterator: const iterator_t,pointer to the element to set its data 
*
* data: void *,the data value to set 
*
* returns: void
*
* time complexity: O(1)
*/
void SLListSetData(iterator_t iterator, void *data); 


/*
* Function: SLListToFind 
* --------------------------
* get range, function and parameter and return the first element whose data 
* is equal to the parameter
*
* from: const iterator_t, the start of the range 
*
* to: const iterator_t, the end of the range
*
* is_match: match_func_t, function from the user 
*
* param: void *, the parameter to be compare with 
*
* returns: iterator_t, the first element of the range which its data equal to 
* the 'param' or the end of the range if the param not exist 
*
* time complexity: O(n)
*/
iterator_t SLListFind(const iterator_t from, const iterator_t to, 
 					 match_func_t is_match, void *param);

/*
* Function: SLListCount
* ----------------------------------
* counts the number of iterators in a given linked list 'list' 
*
* list: const list_t *, pointer to the list 
*
* returns: size_t, the number of elements in the 'list' 
*
* time complexity: O(n)
*/
size_t SLListCount(const list_t *list); 


/*
* Function: SLListForEach
* ----------------------------------
* make a requested operation 'action_func_t' to all the nodes of a given range
*
* from: const iterator_t, pointer to the start of the range 
*
* to: const iterator_t, pointer to the end of the range
*
* is_action: action_func_t, function from the user to make on the nodes
*
* param: void *, the parameter to decide if to make the 'action_func_t'
* on every element within the range 
*
* returns: int, return SUCCESS or FAIL (0 or 1)
*
* time complexity: O(n)
*/
int SLListForEach(iterator_t from, iterator_t to, action_func_t is_action, 
		  void *param);
 
/* Function: SLListIsEmpty
* ----------------------------------
* checks if a given 'list' is empty 
*
* list: const list_t *, pointer to the list 
*
* returns: int, return 1 if empty and 0 if not empty
*
* time complexity: O(1)
*/ 									 
int SLListIsEmpty(const list_t *list);


/* Function: SLListAppend
* ----------------------------------
* connects between to given lists, so that 'list2' will be append to the end 
* of 'list1' and they will become one list as 'list1'
* NOTE - after SLListAppend list2 will not be available to use
*
* list1: list_t *, pointer to the destination list
*
* list2: list_t *, pointer to the list to be appended 
*
* returns: void
*
* time complexity: O(1)
*/ 					
void SLListAppend(list_t *list1, list_t *list2);


#endif /* ifdef __SLLIST_H__ */ 

