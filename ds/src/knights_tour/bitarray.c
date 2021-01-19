/****************************************************************
*	functions to use on bitarray of NUM_OF_BITS bits			*
*																*
*		orpaz houta												*
*		code review by niz the wiz								*
*		1.4.2020												*
****************************************************************/

#include <stddef.h> /* uint64_t */
#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT */
#include <stdint.h>

#include "bitarray.h"


#define MASK_BIT (uint64_t)(1)
#define NUM_OF_BITS (sizeof(uint64_t) * CHAR_BIT)
#define POSSIBLE_BYTE_VARS (256)

static unsigned char LUT_MIRROR[POSSIBLE_BYTE_VARS] = {0};
static unsigned char LUT_COUNT[POSSIBLE_BYTE_VARS] = {0};


bit_array_t BitArrSetAll(bit_array_t array)
{
	return array | ~0;
}

bit_array_t BitArrResetAll(bit_array_t array)
{
	return array & 0;
}

bit_array_t BitArrSetOn(bit_array_t array, uint64_t index)
{
	assert(NUM_OF_BITS > index);

	return (array | (MASK_BIT << index));
}

bit_array_t BitArrSetOff(bit_array_t array, uint64_t index)
{
	assert(NUM_OF_BITS > index && index > 0);

	return (array & ~(MASK_BIT << index));
}

bit_array_t BitArrSetBit(bit_array_t array, uint64_t index, int state)
{
	bit_array_t mask_array = state ^ ((array >> index) & MASK_BIT);

	assert(NUM_OF_BITS > index && index > 0);
	assert(0 == state || 1 == state);

	mask_array <<= index;

	return (array ^ mask_array);
}

bit_array_t BitArrFlip(bit_array_t array)
{
	return ~array;
}

bit_array_t BitArrFliptBit(bit_array_t array, uint64_t index)
{
	assert(NUM_OF_BITS > index && 0 < index);

	return array ^ (MASK_BIT << index);
}

bit_array_t BitArrRotR(bit_array_t array, uint64_t rotations)
{
	bit_array_t array_replica = array;
	rotations %= NUM_OF_BITS;

	return (array >> rotations) | (array_replica << (NUM_OF_BITS - rotations));
}

bit_array_t BitArrRotL(bit_array_t array, uint64_t rotations)
{
	bit_array_t array_replica = array;
	rotations %= NUM_OF_BITS;

	return (array << rotations) | (array_replica >> (NUM_OF_BITS - rotations));
}

uint64_t BitArrCountOn(bit_array_t array) /* kernighan's way */
{
	uint64_t count_on = 0;

	while(array)
	{
		array &= (array - MASK_BIT);
		count_on++;
	}

	return count_on;
}

static unsigned char* SetUpLUTCountOn()
{
	uint64_t i = 1 ;
	uint64_t j = 1 ;
	char count = '\0';

	for( ; POSSIBLE_BYTE_VARS > j ; ++j)
	{
		i = j;

		while (0 != i)
		{
			i = i & (i-1);
			++count;
		}

		LUT_COUNT[j] = count;
		count = '\0';
	}

	return LUT_COUNT;
}


uint64_t BitArrCountOnLUT(bit_array_t array)
{
	unsigned char one_byte = '\0';
	uint64_t count = 0;
	unsigned char *LUT_COUNT = SetUpLUTCountOn();

	while(array)
	{
	one_byte = (unsigned char)array;
	count += LUT_COUNT[one_byte];
	array >>= CHAR_BIT;
	}

	return count;
}

uint64_t BitArrCountOff(bit_array_t array)
{
	uint64_t count_on = 0;

	while(array)
	{
		array &= (array - MASK_BIT);
		count_on++;
	}

	return (NUM_OF_BITS - count_on);
}

int BitArrGetVal(bit_array_t array, uint64_t index)
{
	return ((array >> index) & MASK_BIT);
}

/* the beauty of the nibbles
bit_array_t BitArrMirror(bit_array_t array)
{
	/* for the sake of the line length /
	bit_array_t n = array;

	n = ((n & 0xFFFFFFFFFFFFFFFF) >> 32) | ((n & 0xFFFFFFFFFFFFFFFF) << 32);
	n = ((n & 0xFFFF0000FFFF0000) >> 16) | ((n & 0x0000FFFF0000FFFF) << 16);
	n = ((n & 0xFF00FF00FF00FF00) >> 8) | ((n &  0x00FF00FF00FF00FF) << 8);
	n = ((n & 0xF0F0F0F0F0F0F0F0) >> 4) | ((n &  0x0F0F0F0F0F0F0F0F) << 4);
	n = ((n & 0xCCCCCCCCCCCCCCCC) >> 2) | ((n &  0x3333333333333333) << 2);
	n = ((n & 0xAAAAAAAAAAAAAAAA) >> 1) | ((n &  0x5555555555555555) << 1);

	return n << 2 | n >> 62;
}
*/
bit_array_t ByteMirror(unsigned char byte)
{
	uint64_t count = 0;
	uint64_t steps = CHAR_BIT - 1;

	bit_array_t new_mask = 0;
	bit_array_t mask_start = MASK_BIT;
	bit_array_t mask_end = mask_start << steps;

	while ((CHAR_BIT / 2) > count)
	{
		new_mask = ((mask_start & byte) >> count)
				^ ((mask_end & byte) >> steps);

		byte ^= (new_mask << steps) | (new_mask << count);

		mask_start <<= 1;
		mask_end >>= 1;

		++count;
		--steps;
	}

	return byte;
}

static unsigned char* SetUpLUTMirror()
{
	uint64_t i = POSSIBLE_BYTE_VARS;

	for( ; 0 < i; --i)
	{
		LUT_MIRROR[i] = ByteMirror(i);
	}

	LUT_MIRROR[POSSIBLE_BYTE_VARS] = '\0';

	return LUT_MIRROR;
}

bit_array_t BitArrMirrorLUT(bit_array_t array)
{

	uint64_t shifts_remaining = NUM_OF_BITS;
	bit_array_t mirr_array = 0;
	unsigned char one_byte = (unsigned char)array;
	unsigned char *LUT_MIRROR = SetUpLUTMirror();

	while (array >> CHAR_BIT)
	{
		mirr_array <<= CHAR_BIT;
		mirr_array |= LUT_MIRROR[one_byte];
		one_byte = (unsigned char)array;
		array >>= CHAR_BIT;
		shifts_remaining -= CHAR_BIT;
	}

	return (mirr_array << shifts_remaining);
}

char *BitArrToString(bit_array_t array, char *str)
{
	int i = 0;

	assert(str != NULL);

	for(i = NUM_OF_BITS; i >= 0; --i)
	{
		str[NUM_OF_BITS - i] = (MASK_BIT & (array >> i)) + '0';
	}

	str[NUM_OF_BITS] = '\0';

	return str;
}
