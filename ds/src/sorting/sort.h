/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gilio & shachar						         *
 * 					Last update : 9.6.20									 *
 ****************************************************************************/

 #ifndef __SORT_H__
 #define __SORT_H__

/*-------------------------A user's Function---------------------------------*/
 /****************************************************************************
 * Taking two pointers as arguments (both converted to const void *). The    *
 * function defines the order of the elements by returning (in a stable and  *                                                                           *
 * transitive manner)                                                        *
 *                                                                           *
 * returns: int, (0<) 'data1' is respectively grater then 'data2'            *
 * 			     (0>) 'data2' is respectively grater then 'data1'            *
 *               (0) thay are equal                                          *
 *****************************************************************************/
 typedef int (*compare_t)(const void* data1, const void* data2);
 /*---------------------------------------------------------------------------*/

 /****************************************************************************
  * Function: BubbleSort													 *
  * -------------------------------------------------------------------------*
  * gets an array 'to_sort' and it's size 'array_size'	and sort it.		 *
  * NOTE - the sorting is inplace and stable                    			 *
  *																			 *
  * to_sort: int *, the array to be sorted					     			 *
  * array_size: size_t, the size of the array 'to_sort'						 *
  *																			 *
  * returns: NONE															 *
  *																			 *
  * complications|   worst case |   best case	               				 *
  *	time -       |  	O(n^2)  |	  O(n)                                   *
  * space - O(1)                                                             *
  ****************************************************************************/
 void BubbleSort(int to_sort[], size_t array_size);


 /****************************************************************************
  * Function: InsertSort													 *
  * -------------------------------------------------------------------------*
  * gets an array 'to_sort' and it's size 'array_size'	and sort it.		 *
  * NOTE - the sorting is inplace and stable                    			 *
  *																			 *
  * to_sort: int *, the array to be sorted					     			 *
  * array_size: size_t, the size of the array 'to_sort'						 *
  *																			 *
  * returns: NONE															 *
  *																			 *
  * complications|   worst case |   best case	               				 *
  *	time -       |  	O(n^2)  |	  O(n)                                   *
  * space - O(1)                                                             *
  ****************************************************************************/
 void InsertSort(int to_sort[], size_t array_size);


 /****************************************************************************
  * Function: SelectionSort													 *
  * -------------------------------------------------------------------------*
  * gets an array 'to_sort' and it's size 'array_size'	and sort it.		 *
  * NOTE - the sorting is inplace and stable                    			 *
  *																			 *
  * to_sort: int *, the array to be sorted					     			 *
  * array_size: size_t, the size of the array 'to_sort'						 *
  *																			 *
  * returns: NONE															 *
  *																			 *
  * complications|   worst case |   best case	               				 *
  *	time -       |  	O(n^2)  |	  O(n^2)                                 *
  * space - O(1)                                                             *
  ****************************************************************************/
 void SelectionSort(int to_sort[], size_t array_size);


 /****************************************************************************
  * Function: CountingSort													 *
  * -------------------------------------------------------------------------*
  * gets an array 'to_sort' and it's size 'array_size'	and sort it.		 *
  * NOTE - the sorting is stable but not inplace                  			 *
  *																			 *
  * to_sort: int *, the array to be sorted					     			 *
  * array_size: size_t, the size of the array 'to_sort'						 *
  *																			 *
  * returns: NONE															 *
  *																			 *
  * complications|   worst case |   best case	               				 *
  *	time -       |  	O(n+K)  |	  O(n+K)                                 *
  * space - O(n + K) o(k) - if not stable                                    *
  ****************************************************************************/
 void CountingSort(int to_sort[], size_t array_size, size_t max_range);


 /****************************************************************************
  * Function: RadixSort					    								 *
  * -------------------------------------------------------------------------*
  * gets an array 'to_sort' and it's size 'array_size'	and sort it.		 *
  * NOTE - the sorting is stable but not inplace                  			 *
  *																			 *
  * to_sort: int *, the array to be sorted					     			 *
  * array_size: size_t, the size of the array 'to_sort'						 *
  *																			 *
  * returns: NONE															 *
  *																			 *
  * complications|   worst case |   best case	               				 *
  *	time -       |  	O(n*K)  |	  O(n*K)                                 *
  * space - O(n + K)                                                         *
  ****************************************************************************/
 void RadixSort(int to_sort[], size_t array_size, size_t digits);

 /****************************************************************************
  * Function: MergeSort					    								 *
  * -------------------------------------------------------------------------*
  * gets an array 'to_sort' and it's size 'array_size'	and sort it.		 *
  * NOTE - the sorting is stable but not inplace                  			 *
  *																			 *
  * to_sort: int *, the array to be sorted					     			 *
  * array_size: size_t, the size of the array 'to_sort'						 *
  *																			 *
  * returns: int, (0) if suceed (1) if malloc failed						 *
  *																			 *
  * complications|   worst case  |   best case	               				 *
  *	time -       | O(n(log(n)))  |	 O(n(log(n)))                            *
  * space - O(n)                                                             *
  ****************************************************************************/
 int MergeSort(int to_sort[], size_t array_size);

 /****************************************************************************
  * Function: Qsort			      		    								 *
  * -------------------------------------------------------------------------*
  * Sorts the elements of the array pointed to by 'base'. in each element    *
  * is of 'bytes' long, using the cmp function to determine the order .      *
  *																			 *
  * NOTE - the sorting is stable but not inplace                  			 *
  *																			 *
  * base: void *, Pointer to the first object of the array to be sorted		 *
  * elements: size_t, Number of elements in the array pointed to by 'base'.	 *
  * size: size_t, Size in bytes of each element in the array.				 *
  * cmp: compare_t, a user's function that compares two elements.(see above) *
  *																			 *
  * returns: NONE															 *
  *																			 *
  * complications|  worst case  |   best & average case	      				 *
  *	time -       |  O(n ^ 2)    |	(n log (n))                              *
  *	space - O(1)                                                             *
  ****************************************************************************/
 void QuickSort(void *base, size_t size, size_t bytes, compare_t cmp);


 int RecurBinarySearch(int sorted_array[], size_t array_size, int to_find);
 int IterBinarySearch(int sorted_array[], size_t array_size, int to_find);


 #endif
