/*
* File Name - bit_array.h
* Developer - Itay Adi Yosef
*/
   
#include <stddef.h> /* size_t */ 
#include <stdlib.h> /* calloc, free */
#include <assert.h> /* assert */

#define BITS_IN_BYTE 8
#define BYTE_SIZE 8
#define INT_ASCII 48
#define BIT_INDEX_MIN 1
#define BIT_INDEX_MAX (sizeof(size_t) * BITS_IN_BYTE)
#define PORTABLE_1 (~(size_t)0X0)
#define MAX_NUMBER_IN_BYTE 256

typedef size_t bit_array_t;
 
/*Function which creates mask in order to use the logic operands*/
static bit_array_t BitArrCreateMask(size_t index);

/*Function which returns the bit mirror of an unsigned char (8bit)*/
unsigned char MirrorByte(unsigned char ch);         
  
/*---------------------------------------------------------------------------*/

bit_array_t BitArrSetAll(bit_array_t arr)
{
	return (arr | ~0);
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrResetAll(bit_array_t arr)
{
	return (arr & 0);
}

/*---------------------------------------------------------------------------*/

char *BitArrToString(bit_array_t arr, char *dest)
{
	int i = 0;

	assert(dest);

	dest[BIT_INDEX_MAX - 1] = '\0';

	/*fill the string with the chars*/
	for(i = (BIT_INDEX_MAX - 1); i >= 0 ; --i)
	{
		dest[i] = (arr % 2 + INT_ASCII);
		arr /= 2;
	}

	return(dest);
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrSetOn(bit_array_t arr, size_t index)
{
	bit_array_t mask = 0;
    
	mask = BitArrCreateMask(index);

    return (arr | mask);
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrSetOff(bit_array_t arr, size_t index)
{
	bit_array_t mask = 0;
    
    mask = BitArrCreateMask(index);
	
    return (arr & (~mask));
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrSetBit(bit_array_t arr, size_t index, int boolean_value)
{
	bit_array_t mask = 0;
    
    mask = BitArrCreateMask(index);
	boolean_value <<= index - 1;
	
    return ((arr & (~mask)) | boolean_value);
}


/*---------------------------------------------------------------------------*/

static bit_array_t BitArrCreateMask(size_t index)
{
	bit_array_t mask = (size_t)1 << (index - 1);

    return (mask);
}

/*---------------------------------------------------------------------------*/

int BitArrIsOn(bit_array_t arr, size_t index)
{
	arr >>= (index - (size_t)1);
	
	return (arr & 1); 
}

/*---------------------------------------------------------------------------*/

int BitArrIsOff(bit_array_t arr, size_t index)
{
	arr >>= (index - (size_t)1);

	return ((arr ^ 1) & 1);
}


/*---------------------------------------------------------------------------*/

bit_array_t BitArrFlip(bit_array_t arr, size_t index)
{
    return (arr ^ ((size_t)1 << (index - 1)));
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrMirror(bit_array_t arr)
{
	if(sizeof(arr) == BYTE_SIZE)
	{
		/*Swaps groups of 32bit*/
		arr = ((arr >> 32) & 0x00000000FFFFFFFF) |
			   (arr & 0x00000000FFFFFFFF) << 32;
	}

	/*Swaps groups of 16bit*/
	arr = ((arr >> 16) & 0x0000FFFF0000FFFF) | (arr & 0x0000FFFF0000FFFF) << 16;
	/*Swaps groups of 8bit*/
	arr = ((arr >> 8) & 0x00FF00FF00FF00FF) | (arr & 0x00FF00FF00FF00FF) << 8;
	/*Swaps groups of 4bit*/
	arr = ((arr >> 4) & 0x0F0F0F0F0F0F0F0F) | (arr & 0x0F0F0F0F0F0F0F0F) << 4;
	/*Swaps groups of 2bit*/
	arr = ((arr >> 2) & 0x3333333333333333) | (arr & 0x3333333333333333) << 2;
	/*Swaps groups of 1bit*/
	arr = ((arr >> 1) & 0x5555555555555555) | (arr & 0x5555555555555555) << 1;

	return (arr);
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrRotR(bit_array_t arr, size_t num_to_shift)
{
    return ((arr >> num_to_shift) | (arr << (BIT_INDEX_MAX - num_to_shift)));
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrRotL(bit_array_t arr, size_t num_to_shift)
{    
	return ((arr << num_to_shift) | (arr >> (BIT_INDEX_MAX - num_to_shift)));
}

/*---------------------------------------------------------------------------*/
/*
size_t BitArrCountOn(size_t arr)
{
    arr = (arr & 0x55555555) + ((arr >>1)  & 0x55555555); 
	arr = (arr & 0x33333333) + ((arr >>2)  & 0x33333333); 
	arr = (arr & 0x0F0F0F0F) + ((arr >>4)  & 0x0F0F0F0F); 
	arr = (arr & 0x00FF00FF) + ((arr >>8)  & 0x00FF00FF); 
	arr = (arr & 0x0000FFFF) + ((arr >>16) & 0x0000FFFF);
	arr = (arr & 0x00000000FFFFFFFF) + ((arr >> 32) & 0x00000000FFFFFFFF);
	
	return (arr);
}*/

size_t BitArrCountOn(bit_array_t arr)
{
    arr -= (arr >> 1) & 0x5555555555555555;
    arr = (arr & 0x3333333333333333) + ((arr >> 2) & 0x3333333333333333); 
    arr = (arr + (arr >> 4)) & 0x0F0F0F0F0F0F0F0F;

    return ((arr * 0x0101010101010101) >> 56);
}

/*---------------------------------------------------------------------------*/

size_t BitArrCountOff(size_t arr)
{
	size_t count_bits = 0;
	
	count_bits = BitArrCountOn(arr);
	
	return (BIT_INDEX_MAX - count_bits);
}

/*---------------------------------------------------------------------------*/

size_t BitArrCountOnLUT(bit_array_t arr)
{
	static size_t LUT[MAX_NUMBER_IN_BYTE] = {0}; /* For 8 bit lookup */
	size_t i = 0;
	size_t count = 0;
	size_t mask = 0xFF;

	if(!LUT[1])
	{
		for (i = 0; i < MAX_NUMBER_IN_BYTE; ++i)
		{
			LUT[i] = LUT[i/2] + (i & 1);
		}
	}
	
	while(arr)
	{
		count += LUT[arr & mask];
		arr >>= BITS_IN_BYTE;
	} 
	
	return(count);
}

/*---------------------------------------------------------------------------*/

bit_array_t BitArrMirrorLUT(bit_array_t arr)
{
	static size_t LUT[MAX_NUMBER_IN_BYTE] = {0};
	size_t i = 0;
	size_t count = 0;
	unsigned char mask = 0xFF;
	
	if(!LUT[1])
	{
		for (i = 0; i < MAX_NUMBER_IN_BYTE; ++i)
		{
			LUT[i] = MirrorByte(i);
		}
	}
	
	for (i = 0; i < (BITS_IN_BYTE - 1); ++i)
	{
		count += LUT[arr & mask];		
		count <<= BITS_IN_BYTE;
		arr >>= BITS_IN_BYTE;
	}

	return(count);
}

/*---------------------------------------------------------------------------*/

unsigned char MirrorByte(unsigned char ch)
{
    ch = (ch & 0xF0) >> 4 | (ch & 0x0F) << 4;
    ch = (ch & 0xCC) >> 2 | (ch & 0x33) << 2;
    ch = (ch & 0xAA) >> 1 | (ch & 0x55) << 1;
   
   return (ch);
}

/*---------------------------------------------------------------------------*/






