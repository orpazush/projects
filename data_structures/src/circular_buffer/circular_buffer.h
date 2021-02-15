/****************************************************************************
* 					written by : orpaz houta								*
* 					review : yana Gorikhovski								*
*					Last update : 14.4.20 									*
****************************************************************************/

#ifndef __CIRCULAR_BUFFER_H__ 
#define __CIRCULAR_BUFFER_H__ 

typedef struct buffer buffer_t;

/*
* Function: BufCreate 
* ------------------------- 
* creates a new empty buffer of type buffer_t 
*
* returns: buffer_t *, pointer to the buffer 
*
* time complexity: O(1)
 */
buffer_t *BufCreate(size_t capacity);
 
 
/*
* Function: BufDestroy 
* -----------------------
* frees all the allocated memory to the buffer
*
* buffer: buffer_t *, pointer to the buffer 
*
* returns: void
*
* time complexity: O(1)
*/
void BufDestroy(buffer_t *buffer);
 
 
/*
 * Function: BufRead
* ----------------------
* attempts to read up to 'count_byte' bytes from a given 'buffer' into a given 
* destination starting at 'dest'
* NOTE - ones the buffer is empty the function will stop read.
*
* buffer:buffer_t *, pointer to buffer
*
* dest:void *, pointer of the target address to copy to 
*
* count_byte:size_t, number of bytes to read
*
* returns: ssize_t, the number of bytes read in case of success or -1 in case 
* of error (errno will be set appropriately)
*
* time complexity: O(n) 
*/
ssize_t BufRead(buffer_t *buffer, void *dest, size_t count_byte);


/*
* Function: BufWrite 
* ---------------------
* attempts to write up to 'count_byte' bytes from a given source starting at
* 'src' into a given 'buffer' 
* NOTE - ones the buffer is full the function will stop write.
*
* buffer:buffer_t *, pointer to buffer
*
* src:const void *, pointer of the address to write from 
*
* count_byte:size_t, number of bytes to write 
*
* returns: ssize_t, the number of written bytes in case of success or -1 in case 
* of error (errno will be set appropriately) 
*
* time complexity: O(n) 
*/
ssize_t BufWrite(buffer_t *buffer, const void *src, size_t count_byte);


/*
* Function: BufAvailableSpace 
* ------------------------------
* checks how many more space left in the buffer
*
* buffer:const buffer_t *, pointer to buffer
*
* returns: size_t, the number of unused bytes in the buffer
*
* time complexity: O(1) 
*/
size_t BufAvailableSpace(const buffer_t *buffer);


/*
* Function: BufCapacity
* -----------------------
* buffer:const buffer_t *, pointer to buffer 
*
* returns: size_t the maximum number of bytes the buffer can hold 
*
* time complexity: O(1) 
*/
size_t BufCapacity(const buffer_t *buffer);


/*
* Function: BufIsEmpty 
* ----------------------
* checks if a given 'buffer' is empty 
*
* buffer: const buffer_t *, pointer to the buffer 
*
* returns: int, return 1 if empty and 0 if not
*
* time complexity: O(1)
*/ 							
int BufIsEmpty(const buffer_t *buffer);


#endif /* ifdef __CIRCULAR_BUFFER_H__*/ 


