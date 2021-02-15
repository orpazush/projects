/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Gil Mazliah (Gilio:)    						*
*					Last update : 2.6.20 									*
****************************************************************************/
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h>     /* size_t */

#include "dllist.h"   /* dllist_t */


typedef struct hash_table hash_t;

/*-------------------------A user's Functions--------------------------------*/
/*****************************************************************************
* activates some operation by the user's choise on elements values           *
*                                                                            *
* returns: int, (0) if succeed 												 *
* 		        or status set by the user if not			                 *
*****************************************************************************/
typedef int (*acion_func_t)(void *data1, void *param);

/*****************************************************************************
* compares between two given 'data1' & 'data2' according to the user's needs *
* this function should be compatible to the cind of data restored in the 	 *                                                                           *
* hash table                                                                 *
*                                                                            *
* returns: int, (0<) 'data1' is higher then 'data2'                          *
* 				(0>) 'data2' is higher then 'data1'                          *
*****************************************************************************/
typedef int (*cmp_func_t)(const void *data1, const void *data2, void *param);

/*****************************************************************************
* maps the data whithin the hash table and translates a given 'key' into 	 *
* a hash code which is used to index the hash table.						 *
* NOTE - The efficiency of many operations in the hash table depends on the  *
*		 efficiency of the hash function, so it should distribute the 	 	 *
*		 elements well to attein minimum collisions 						 *
*                                                                            *
* returns: size_t, the hash code of the given 'key'							 *
*****************************************************************************/
typedef size_t (*hash_func_t)(const void *key);
/*---------------------------------------------------------------------------*/


/*****************************************************************************
* Function:    HASHCreate                                                    *
* -------------------------------------------------------------------------- *
* creates a new empty hash table.					                         *
*                                                                            *
* compare: cmp_func_t - a user's function (see explenation above)			 *
*						used to find keys whithin the hash table			 *
* param: void *, for the 'cmp_func_t' use                                    *
* hash_code: hash_func_t - a user's function (see explenation above)		 *
*						   used to map the data whithin the hash table and 	 *
*						   get a direct access to the indexes				 *
* num_of_keys: size_t, the number of indexes whithin the table. this number  *
*			   should be compatible to the user's 'hash_func_t' 			 *
*                                                                            *
* returns: hash_t *, success - pointer to the new hash table                 *
* 					 error - (NULL) in case allocation failed                *
*                                                                            *
* time complexity: O(1)        			                                     *
*****************************************************************************/
hash_t *HashCreate(size_t num_of_keys, hash_func_t hash_code,
				   cmp_func_t compare, void *param);
/*****************************************************************************
* Function:    HASHDestroy                                                   *
* -------------------------------------------------------------------------- *
* destroys the hash table and frees all its allocated memory                 *
*                                                                            *
* hash_table: hash_t *, pointer to the hash table to destroy                 *
*                                                                            *
* returns: NONE                                                              *
*                                                                            *
* time complexity: O(n + k)                                                  *
*****************************************************************************/
void HashDestroy(hash_t *hash_table);

/*****************************************************************************
* Function:   HASHInsert                                                     *
* -------------------------------------------------------------------------- *
* inserts a new element to the hash table. the element will be put in the    *
* right position according to the return value of the 'hash_code'            *
*                                                                            *
* hash_table: hash_t *, pointer to the hash table                            *
* key: void *, the new element  					                         *
*                                                                            *
* returns: int, (0) success or (1) in case allocation failed                 *
*                                                                            *
* time complexity: W - O(1) 		                                         *
*****************************************************************************/
int HashInsert(hash_t *hash_table, void *key);

/*****************************************************************************
* Function:    HASHRemove                                                    *
* -------------------------------------------------------------------------- *
* erases an element from a given 'hash_table' according to it's associated	 *
* 'key' 																	 *
* NOTE - case the 'key' is not whithin the 'hash_table' it will search the   *
*        hash table but will erase nothing                                   *
*                                                                            *
* hash_table: hash_t *, pointer to the hash table                            *
* key: const void *, the key associated to the element to remove             *
*                                                                            *
* returns: NONE                                                              *
*                                                                            *
* time complexity: B - O(1)  W - O(n)   	                                 *
*****************************************************************************/
void HashRemove(hash_t *hash_table, const void *key);

/*****************************************************************************
* Function:    HASHFind                                                      *
* -------------------------------------------------------------------------- *
* search for a given element according to it's associated 'key' in a given   *
* 'hash_table'.																 *
*                                                                            *
* hash_table: hash_t *, pointer to the hash table                            *
* key: void *, the data to find in the hash table                            *
*                                                                            *
* returns: the data associated to the 'key' or NULL in case not found 	     *
*                                                                            *
* time complexity: B - O(1)  W - O(n)                                        *
*****************************************************************************/
void *HashFind(hash_t *hash_table, const void *key);

/*****************************************************************************
* Function:    HashSize                                                      *
* -------------------------------------------------------------------------- *
* counts the number of elements whithin a given 'hash_table'                 *
*                                                                            *
* hash_table: hash_t *, pointer to the hash table                            *
*                                                                            *
* returns: size_t, the number of elements in the 'hash_table'                *
*                                                                            *
* time complexity: O(n + k)                                                  *
*****************************************************************************/
size_t HashSize(const hash_t *hash_table);

/*****************************************************************************
* Function: HASHIsEmpty                                                      *
* -------------------------------------------------------------------------- *
* checks whether a given 'hash_table' is empty or not                        *
*                                                                            *
* hash_table: hash_t *, pointer to the hash table                            *
*                                                                            *
* returns: int, (1) if empty and (0) if not      		                     *
*                                                                            *
* time complexity: O(k)				                                         *
*****************************************************************************/
int HashIsEmpty(const hash_t *hash_table);

/*****************************************************************************
* Function:    HASHForEach                                                   *
* -------------------------------------------------------------------------- *
* executes a given 'action' upon all the elements whithin a given            *
* 'hash_table' 										                         *
* NOTE - in case of error the function will stop immedietely                 *
*                                                                            *
* hash_table: hash_t *, pointer to the hash table                            *
* action: acion_func_t, a user's function                                    *
* param: void *, a parameter to be used in 'action'       	                 *
*                                                                            *
* returns: int, return (0) in success 			                             *
*                       or the status returned from the 'action' function    *
*                                                                            *
* time complexity: O(n + k)                                                  *
*****************************************************************************/
int HashForEach(hash_t *hash_table, acion_func_t action, void *param);



#endif /* ifdef __HASH_TABLE_H__ */
/* (╯°□°）╯︵ ┻━┻ */
