/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg  						         *
 * 					Last update : 9.6.20									 *
 *---------------------------------------------------------------------------*
 * A heap data structure is a tree-based data structure that satisfies a     *
 * property called heap property. means that if A is a parent of B then the  *
 * key of A is ordered with respect to the key of B with the same ordering   *
 * applying across the heap. The element at the "top" of the heap (with no   *
 * parents) is called the root.                                              *
 ****************************************************************************/

 #include <assert.h>     /* assert */
 #include <malloc.h>     /* malloc */

 #include "vector.h"    /* vector_t, VectorCreate, VectorDestroy.. */
 #include "heap.h"

 /*---------------------------Structs & Enums--------------------------------*/
 struct heap
 {
     vector_t *container;
     cmp_func_t cmp;
 };

 enum status
 {
    SUCCESS,
    FAILURE
 };
/*---------------------------------------------------------------------------*/

/*----------------------------------Macros------------------------------------*/
 #ifndef NDEBUG
 #define PRINT_ERROR(str) fprintf(stderr, "ERROR( %s : %d ) -- %s\n",\
 								  __FILE__, __LINE__, str)
 #else
 #define PRINT_ERROR(str)
 #endif

 #define CAPACITY           (100)
 #define ROOT_INDEX         (0)

 #define GETDATA(x, i)      (VectorGetElementAddress(x,i))
 #define SETDATA(x, i, d)   (VectorSetElementAddress(x, i, d))
 #define PARENT(child)      ((child - 1) / 2)
 #define LEFTCHILD(parent)  ((parent * 2) + 1)
 #define RIGHTCHILD(parent) ((parent * 2) + 2)
 /*---------------------------------------------------------------------------*/

 /*---------------------------Static Functions--------------------------------*/
 static size_t _GetEldestOwner(size_t parent, cmp_func_t cmp, vector_t *container);
 static void _Swap(size_t index_a, size_t index_b, vector_t *container);
 static void _HeapifyDown(size_t i, cmp_func_t cmp, vector_t *container);
 static int _HeapifyUp(size_t i, cmp_func_t cmp, vector_t *container);
 /*---------------------------------------------------------------------------*/


 heap_t *HeapCreate(cmp_func_t cmp)
 {
     heap_t *new = NULL;

     assert(cmp);

     new = (heap_t *)malloc(sizeof(heap_t));
     if (!new)
     {
         PRINT_ERROR("malloc error in HeapCreate\n");

         return (NULL);
     }

     new->container = VectorCreate(CAPACITY);
     if (!new->container)
     {
         free(new);
         new = NULL;

         return (NULL);
     }

     new->cmp = cmp;

     return (new);
 }

 void HeapDestroy(heap_t *heap)
 {
     if (heap)
     {
         VectorDestroy(heap->container);

         heap->container = NULL;
         heap->cmp = NULL;

         free(heap);
         heap = NULL;
     }
 }

 int HeapPush(heap_t *heap, void *data)
 {
     assert(heap);

 /* VectorPushBack also return 0 if succeed */
 return ((VectorPushBack(heap->container, data)) ? FAILURE
          : _HeapifyUp(VectorSize(heap->container) - 1, heap->cmp,
                       heap->container));
 }

 void HeapPop(heap_t *heap)
 {
     assert(heap);

     _HeapifyDown(ROOT_INDEX, heap->cmp, heap->container);

     VectorPopBack(heap->container);
 }

 void *HeapPeek(const heap_t *heap)
 {
     assert(heap);

     return (VectorGetElementAddress(heap->container, ROOT_INDEX));
 }

 size_t HeapSize(const heap_t *heap)
 {
     assert(heap);

     return (VectorSize(heap->container));
 }

 int HeapIsEmpty(const heap_t *heap)
 {
     assert(heap);

     return (!VectorSize(heap->container));
 }

 void *HeapRemove(heap_t *heap, is_match_t is_match, const void *param)
 {
     size_t find = 0;
     void *data = NULL;

     assert(heap);

     for (find = 0; find < VectorSize(heap->container); ++find)
     {
         data = (GETDATA(heap->container, find));
         if (is_match(data, param))
         {
             _HeapifyDown(find, heap->cmp, heap->container);
             VectorPopBack(heap->container);

             return (data);
         }
     }

     return (NULL);
 }


 /*---------------------------Static Defintions-------------------------------*/
 static int _HeapifyUp(size_t i, cmp_func_t cmp, vector_t *container)
 {
     if (i)
     {
         if(0 < cmp(GETDATA(container, i), GETDATA(container, PARENT(i))))
         {
             _Swap(i, PARENT(i), container);
             _HeapifyUp(PARENT(i), cmp, container);
         }
     }

     return (SUCCESS);
 }

 static void _HeapifyDown(size_t i, cmp_func_t cmp, vector_t *container)
 {
     /* if 'i' has two children, set in 'i' the data of the 'eldest_owner'
        repeatedly until 'i' has less then two children */
    if (RIGHTCHILD(i) < VectorSize(container))
    {
        size_t eldest_owner = _GetEldestOwner(i, cmp, container);

        SETDATA(container, i, GETDATA(container, eldest_owner));
        _HeapifyDown(eldest_owner, cmp, container);
    }
    /* if 'i' is the parent of the last element in the heap set it's data in 'i' */
    else if (LEFTCHILD(i) < VectorSize(container))
    {
        SETDATA(container, i, GETDATA(container, LEFTCHILD(i)));
    }
    /* if 'i' has reached the end set in it the last element and use
        _HeapifyUp to make sure the heap property is kept */
    else
    {
        SETDATA(container, i, GETDATA(container, VectorSize(container) - 1));
        _HeapifyUp(i, cmp, container);
    }
}
/* swaps the data of two given 'index_a' & 'index_b' */
 static void _Swap(size_t index_a, size_t index_b, vector_t *container)
 {
    void *temp = GETDATA(container, index_a);
    SETDATA(container, index_a, GETDATA(container, index_b));
    SETDATA(container, index_b, temp);
 }

/* gets a 'parent' and return the index of it's bigger child (according to then
   cmp function) */
 static size_t _GetEldestOwner(size_t parent, cmp_func_t cmp, vector_t *container)
 {
    assert(parent < VectorSize(container));

    return ((0 < cmp(GETDATA(container, LEFTCHILD(parent)),
                     GETDATA(container, RIGHTCHILD(parent))))
             ? LEFTCHILD(parent) : RIGHTCHILD(parent));
 }
 /*---------------------------------------------------------------------------*/
