#include <stddef.h> /* uint64_t */

/****************************************************************
*	imlementation of functions in bitarray			*
*								*
*		orpaz houta					*
*		cr by niz the wiz				*
*		1.4.2020					*
****************************************************************/

#ifndef __BITARRAY_H__ /* header guard */
#define __BITARRAY_H__
#include <stdint.h>

typedef uint64_t bit_array_t;

/*
* Function:  < BitArrSetAll >
* --------------------
* gets an array of bits 'array' and set all of her bits
*
* @param array - array of bits
* @return array which all of all of them 1
*/
bit_array_t BitArrSetAll(bit_array_t array);


/*
* Function:  < BitArrResetAll >
* --------------------
* gets an array of bits 'array' and reset all of her bits
*
* @param array - array of bits
* @return array of bits which all of them 0
*/
bit_array_t BitArrResetAll(bit_array_t array);


/*
* Function:  < BitArrSetOn >
* --------------------
* gets an array of bits 'array' and set a chosen bit 'index' to 1
*
* @param array - array of bits
* @param index - the index of the bit to set on
* @return the new bit array
*/
bit_array_t BitArrSetOn(bit_array_t array, uint64_t index);


/*
* Function:  < BitArrSetOff >
* --------------------
* gets an array of bits 'array' and set a chosen bit 'index' to 1
*
* @param array - array of bits
* @param index - the index of the bit to set off
* @return the new bit array
*/
bit_array_t BitArrSetOff(bit_array_t array, uint64_t index);


/*
* Function:  < BitArrSetBit >
* --------------------
* gets an array of bits 'array' and set a chosen bit 'index' to a chosen 'state'
*
* @param array - array of bits
* @param index - the index of the bit to set off
* @param state - the state to set the bit
* @return the new bit array
*/
bit_array_t BitArrSetBit(bit_array_t array, uint64_t index, int state);


/*
* Function:  < BitArrFlip >
* --------------------
* gets an array of bits 'array' and change all of her bits
*
* @param array - array of bits
* @return the opposite array
*/
bit_array_t BitArrFlip(bit_array_t array);


/*
* Function:  < BitArrFliptBit >
* --------------------
* gets an array of bits 'array' and flips a chosen bit 'index'
*
* @param array - array of bits
* @param index - the index of the bit to flip
* @return the new bit array
*/
bit_array_t BitArrFliptBit(bit_array_t array, uint64_t index);


/*
* Function:  < BitArrRotR >
* --------------------
* gets an array of bits 'array' and rotate it to the right
* a given number of times 'rotations'
*
* @param array - array of bits
* @param rotations - number of rotation to do
* @return the new bit array
*/
bit_array_t BitArrRotR(bit_array_t array, uint64_t rotations);


/*
* Function:  < BitArrRotL >
* --------------------
* gets an array of bits 'array' and rotate it to the left
* a given number of times 'rotations'
*
* @param array - array of bits
* @param rotations - number of rotation to do
* @return the new bit array
*/
bit_array_t BitArrRotL(bit_array_t array, uint64_t rotations);


/*
* Function:  < BitArrCountOn >
* --------------------
* gets an array of bits 'array' and counts the set bits
*
* @param array - array of bits
* @return the number of bits that are on
*/
uint64_t BitArrCountOn(bit_array_t array);


/*
* Function:  < BitArrCountOnLUT >
* --------------------
* gets an array of bits 'array' and counts the set bits using a lut 'LUT_COUNT'
*
* @param array - array of bits
* @return the mirror of the bit
*/
bit_array_t BitArrCountOnLUT(bit_array_t array);


/*
* Function:  < BitArrCountOff >
* --------------------
* gets an array of bits 'array' and counts the offset bits
*
* @param array - array of bits
* @return the number of bits that are off
*/
uint64_t BitArrCountOff(bit_array_t array);


/*
* Function:  < BitArrGetVal >
* --------------------
* gets an array of bits 'array' and checks the value of a chosen bit 'index'
*
* @param array - array of bits
* @param index - the index to check the bit
* @return the value of the bit
*/
int BitArrGetVal(bit_array_t array, uint64_t index);


/*
* Function:  < BitArrMirror >
* --------------------
* gets an array of bits 'array' and turn it bits to the value of there mirror
*
* @param array - array of bits
* @return the mirror of the bit
*/
bit_array_t BitArrMirror(bit_array_t array);


/*
* Function:  < BitArrMirrorLUT >
* --------------------
* gets an array of bits 'array' and turn it bits to the value of there mirror
* using a lut 'LUT_MIRROR'
*
* @param array - array of bits
* @return the mirror of the bit
*/
bit_array_t BitArrMirrorLUT(bit_array_t array);


/*
* Function:  < ToString >
* --------------------
* gets an array of bits 'array' and turn it to a string 'str'
*
* @param array - array of bits
* @return pointer to string which represent the bitarray
*/
char *BitArrToString(bit_array_t array, char *str);


#endif /* ifdef __BITARRAY_H__ */
