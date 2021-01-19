/********************************************************
*		build my first vector							*
*		orpaz houta										*
*		reviewed by Gil Steinberg						*
*		12.4.2020										*
********************************************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

/* a handle to be used with this API
 * (App Programming Interface) */

typedef struct vector vector_t;

/*
* Function:  < VectorCreate >
* --------------------------
* creates a new vector by allocating memory and initialise the vector's members
*
* parameter: the capacity of the vector
*
*  returns: pointer to the new vector
*/
vector_t *VectorCreate(size_t capacity);

/*
* Function:  < VectorDestroy >
* ----------------------
* destroy the given 'vector' of type vector_t by freeing his memory
*
* parameter: pointer to a 'vector' of type vector_t
*
*  returns: <void>
*/
void VectorDestroy(vector_t *vector);

/*
* Function:  < VectorGetElemenAddress >
* -------------------------------------
* gets a specific element by its 'index'
* NOTE - trying to get an unset element will cause undefined behviour.
*
* parameter: pointer to a 'vector' of type vector_t
* parameter: an index to a requested element
*
*  returns: pointer to the requested element
*/
void *VectorGetElementAddress(const vector_t *vector, size_t index);

/*
* Function:  < VectorSetElementAddress >
* --------------------------------------
* sets a specific element by its 'index'
* NOTE - setting an element outside the vector will cause undefined behaviour
* and might be discarded incase of using 'VectorShrinkToFit'
*
* parameter: pointer to a 'vector' of type vector_t
* parameter: an index to a requested element
* parameter: pointer to element of type void to be set
*
*  returns: <void>
*/
void VectorSetElementAddress(vector_t *vector, size_t index, void *element);

/*
* Function:  < VectorReserve >
* ---------------------------
* changes the capacity of a given 'vector' to a chosen 'new_capacity'
*
* parameter: pointer to a 'vector' of type vector_t
* parameter: new desired capacity
*
*  returns: 0 incase of success, 1 if failed
*/
int VectorReserve(vector_t *vector, size_t new_capacity);

/*
* Function:  < VectorShrinkToFit >
* -----------------------------------
* shrinks the capacity of a given 'vector' to the number of set elements
* NOTE - set elements not within the area of the vector might not be inclouded
*
* parameter: pointer to a 'vector' of type vector_t
*
*  returns: 0 incase of success, 1 if failed
*/
int VectorShrinkToFit(vector_t *vector);

/*
* Function:  < VectorPushBack >
* -----------------------------
* sets a new element in the vector and extending the capacity incase
* of reaching the old one
*
* parameter: pointer to a 'vector' of type vector_t
* parameter: pointer to element of type void to be set
*
*  returns: 0 incase of success, 1 if failed
*/
int VectorPushBack(vector_t *vector, void *element);


/*
* Function:  < VectorPopBack >
* ----------------------------------
* releas the last element in the vector if the vector doesn't empty
*
* parameter: pointer to a 'vector' of type vector_t
*
*  returns: <void>
*/
void VectorPopBack(vector_t *vector);


/*
* Function:  < VectorSize >
* --------------------------
* checks what the size of a given 'vector'
*
* parameter: pointer to a 'vector' of type vector_t
*
* returns: the number of elements within the vector
*/
size_t VectorSize(const vector_t *vector);


/*
* Function:  < VectorCapacity >
* --------------------------
* brings the maximum number of elements a given vector can hold
* at the time the function is used
*
* parameter: pointer to a 'vector' of type vector_t
*
* returns: the capacity of the vector
*/
size_t VectorCapacity(const vector_t *vector);

#endif /* ifdef __VECTOR_H__ */
