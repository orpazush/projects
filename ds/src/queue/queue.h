/****************************************************************************
 * 					written by :orpaz houta									*
 * 					review : Gil Mazliah (Gilio):)							*
 * 					Last update : 5.4.20									*
 ***************************************************************************/

#ifndef __QUEUE_H__ 
#define __QUEUE_H__ 


typedef struct queue queue_t;

/*
* Function: QueueCreate 
* ----------------------
* creates a new empty queue of type queue_t 
*
* returns: queue_t *, pointer to the queue 
*
* time complexity: O(1)
*/
queue_t *QueueCreate(void);
 
 
/*
* Function: QueueDestroy 
* -----------------------
* frees all the memory allocated to the queue
*
* queue: queue_t *, pointer to the queue 
*
* returns: void
*
* time complexity: O(n)
*/
void QueueDestroy(queue_t *queue);
 
 
/*
* Function: EnQueue 
* -------------------------
* inserts a new element to the queue
*
* queue: queue_t *, pointer to the queue 
*
* data: void *, data to put in the new element
*
* returns: int, return 0 if succeed and 1 if failed 
*
* time complexity: O(1)
*/
int EnQueue(queue_t *queue, void *data);


/*
* Function: DeQueue 
* --------------------------
* removes the oldest element of the queue
* 
* queue: queue_t *, pointer to the queue 
*
* returns: void 
*
* time complexity: O(1)
*/
void DeQueue(queue_t *queue);


/*
* Function: QueuePeek
* -----------------------
* peeks the oldest element of a given 'queue'
* NOTE - trying to peek an empty queue might cause undefined behaviour
*
* returns: void *, pointer to the data of the oldest element
*
* time complexity: O(1)
*/
void *QueuePeek(const queue_t *queue);


/*
* Function: QueueSize
* -----------------------
* counts the number of elements in a given 'queue' 
*
* queue: const queue_t *, pointer to the queue 
*
* returns: size_t, the number of elements in the 'queue' 
*
* time complexity: O(n)
*/
size_t QueueSize(const queue_t *queue);


/*
* Function: QueueIsEmpty 
* --------------------------
* checks if a given 'queue' is empty 
*
* queue: const queue_t *, pointer to the queue 
*
* returns: int, return 1 if empty and 0 if not empty
*
* time complexity: O(1)
*/ 			
int QueueIsEmpty(const queue_t *queue);


/*
* Function: QueueAppend 
* --------------------------
* connects between to given queues, so that 'queue2' will be append to the end 
* of 'queue1' and they will become one queue as 'queue1'
* NOTE - after queueAppend 'queue2' will cease to exists as an individual
*
* queue1: queue_t *, pointer to the destination queue
*
* queue2: queue_t *, pointer to the queue to be appended 
*
* returns: void
*
* time complexity: O(1)
*/ 					
void QueueAppend(queue_t *queue1, queue_t *queue2);

#endif /* ifdef __QUEUE_H__ */ 


