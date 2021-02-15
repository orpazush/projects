/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Alex Sevostyanov                          *
 *                      coding date - 11-06-2020                              *
 ******************************************************************************/

#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /* size_t */

typedef struct trie trie_t;

/*****************************************************************************
* Function:   TrieCreate                                                     *
* -------------------------------------------------------------------------- *
* creates a new empty trie.                                                  *
*                                                                            *
* height: size_t, the depth of the 'trie', represent also the length of      *
*         the stored keys                                                    *
*                                                                            *
* returns: trie_t *, success - pointer to the Trie                           *
*                    error: (NULL) in case allocation failed                 *
*                                                                            *
* time complexity: O(1)                                                      *
*****************************************************************************/
trie_t *TrieCreate(size_t height);

/*****************************************************************************
* Function:   TrieDestroy                                                    *
* -------------------------------------------------------------------------- *
* destroys the trie and frees all its allocated memory                       *
*                                                                            *
* trie: trie_t *, pointer to the Trie to destroy                             *
*                                                                            *
* returns: NONE                                                              *
*                                                                            *
* time complexity: O(n)                                                      *
*****************************************************************************/
void TrieDestroy(trie_t *trie);

/*****************************************************************************
* Function:  TrieInsert                                                      *
* -------------------------------------------------------------------------- *
* inserts a new element 'path' to the trie.                        			 *
*                                                                            *
* trie: trie_t *, pointer to the trie                                        *
* path: size_t, the new element                                              *
*                                                                            *
* returns: int, (0) success or (1) in case allocation failed                 *
*                                                                            *
* time complexity: O(log n)                                                  *
*****************************************************************************/
int TrieInsert(trie_t *trie, size_t path);

/*****************************************************************************
* Function:    TrieRemove                                                    *
* -------------------------------------------------------------------------- *
* erases a given element 'path' from a given 'trie'                          *
*                                                                            *
* trie: trie_t *, pointer to the trie                                        *
* path: void *, the element to remove                                        *
*                                                                            *
* returns: int, (0) if the path was removed (1) the path wasn't in the 'trie'*
*                                                                            *
* time complexity: O(log n)                                                  *
*****************************************************************************/
int TrieRemove(trie_t *trie, const size_t path);

/*****************************************************************************
* Function:    TrieSize                                                      *
* -------------------------------------------------------------------------- *
* counts the number of elements whithin a given 'trie'                       *
*                                                                            *
* trie: const trie_t *, pointer to the trie                                  *
*                                                                            *
* returns: size_t, the number of elements in the 'trie'                      *
*                                                                            *
* time complexity: W - O(n)                                                  *
*****************************************************************************/
size_t TrieSize(const trie_t *trie);

/*****************************************************************************
* Function: IsInTrie                                                         *
* -------------------------------------------------------------------------- *
* checks whether a given 'request' is in the 'trie'                          *
*                                                                            *
* trie: const trie_t *, pointer to the trie                                  *
*                                                                            *
* returns: int, return (1) if it is in the 'trie' (0) if not                 *
*                                                                            *
* time complexity: O(log n)                                                  *
*****************************************************************************/
int IsInTrie(const trie_t *trie, const size_t request);

/*****************************************************************************
* Function:    TrieGetNext                                                   *
* -------------------------------------------------------------------------- *
* gets the first non exist in trie element which is bigger then 'request'    *
* NOTE - this function used only when knowing that the request is in the     *
*        'trie'. sending a request which is not in the 'trie' will cause     *
*         undefined behaviour                                                *
*                                                                            *
* trie: trie_t *, pointer to the trie                                        *
* path: void *, the path to find in the trie                                 *
*                                                                            *
* returns: int, return (1) if found and (0) if not                           *
*                                                                            *
* time complexity: O(log n)                                                  *
*****************************************************************************/
size_t TrieGetNext(const trie_t *trie, const size_t request);

/*****************************************************************************
* Function: TrieIsEmpty                                                      *
* -------------------------------------------------------------------------- *
* checks whether a given 'trie' is empty or not                              *
*                                                                            *
* trie: const trie_t *, pointer to the trie                                  *
*                                                                            *
* returns: int, return (1) if empty and (0) if not                           *
*                                                                            *
* time complexity: O(1)                                                      *
*****************************************************************************/
int TrieIsEmpty(const trie_t *trie);


#endif /* ifdef __TRIE_H__ */
