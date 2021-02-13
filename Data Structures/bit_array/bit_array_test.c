/*
* File Name - bit_array_test.c
* Developer - Itay Adi Yosef
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc, free */
#include <stddef.h> /* size_t */

#include "bit_array.h"

/*------------------------------User declarations-----------------------------*/

static void BitArrSetAllTest(void);
static void BitArrResetAllTest(void);
static void BitArrToStringTest(void);
static void BitArrSetOnTest(void);
static void BitArrIsOffTest(void);
static void BitArrSetOffTest(void);
static void BitArrSetBitTest(void);
static void BitArrIsOnTest(void);
static void BitArrIsOffTest(void);
static void BitArrFlipTest(void);
static void BitArrMirrorTest(void);
static void BitArrRotRTest(void);
static void BitArrRotLTest(void);
static void BitArrCountOnTest(void);
static void BitArrCountOffTest(void);
static void BitArrCountOnLUTTest(void);
static void BitArrMirrorLUTTest(void);

/*------------------------------------main-----------------------------------*/

int main(void)
{
	BitArrSetAllTest();
	printf("-------------------------------------------\n");
	BitArrResetAllTest();
	printf("-------------------------------------------\n");
	BitArrToStringTest();
	printf("-------------------------------------------\n");
	BitArrSetOnTest();
	printf("-------------------------------------------\n");
	BitArrSetOffTest();
	printf("-------------------------------------------\n");
	BitArrSetBitTest();
	printf("-------------------------------------------\n");
	BitArrIsOnTest();
	printf("-------------------------------------------\n");
	BitArrIsOffTest();
	printf("-------------------------------------------\n");
	BitArrFlipTest();
	printf("-------------------------------------------\n");
	BitArrMirrorTest();
	printf("-------------------------------------------\n");
	BitArrMirrorLUTTest();
	printf("-------------------------------------------\n");
	BitArrRotRTest();
	printf("-------------------------------------------\n");
	BitArrRotLTest();
	printf("-------------------------------------------\n");
	BitArrCountOnTest();
	printf("-------------------------------------------\n");
	BitArrCountOnLUTTest();
	printf("-------------------------------------------\n");
	BitArrCountOffTest();
	printf("-------------------------------------------\n");

	return (0);
}




/*---------------------------------------------------------------------------*/

static void BitArrSetAllTest(void)
{
	bit_array_t arr = 200;
	
	arr = BitArrSetAll(arr);
	printf("Set All: %ld\n", arr);
}

/*---------------------------------------------------------------------------*/

static void BitArrResetAllTest(void)
{
	bit_array_t arr = 200;
	
	arr = BitArrResetAll(arr);
	printf("Reset All: %ld\n", arr);
}

/*---------------------------------------------------------------------------*/

static void BitArrToStringTest(void)
{
	char *arr = NULL;
	size_t val = 59;

	if(!(arr = (char *)calloc(8, sizeof(size_t))))
	{
		printf("Error");
	}

	arr = BitArrToString(val, arr);
	
	printf("To String: \n%s\n", arr);

	free(arr);
	arr = NULL;
}

/*---------------------------------------------------------------------------*/

static void BitArrSetOnTest(void)
{
	bit_array_t arr = 75000;	
	size_t index = 28;
	
	printf("Set On: \n");
	printf("Before: %ld, index is: %ld\n", arr, index);
	printf("After: %ld\n", BitArrSetOn(arr, index));
}

/*---------------------------------------------------------------------------*/

static void BitArrSetOffTest(void)
{
	bit_array_t arr = 18;	
	size_t index = 2;
	
	printf("Set Off: \n");
	printf("Before: %ld, index is: %ld\n", arr, index);
	printf("After: %ld\n", BitArrSetOff(arr, index));
}

/*---------------------------------------------------------------------------*/

static void BitArrSetBitTest(void)
{
	bit_array_t arr = 18;	
	size_t index = 2;
	int boolean_value = 0;

	printf("Set Bit: \n");
	printf("Before: %ld, index is: %ld, mode: %d\n", arr, index, boolean_value);
	printf("After: %ld\n", BitArrSetBit(arr, index, boolean_value));
}

/*---------------------------------------------------------------------------*/

static void BitArrIsOnTest(void)
{
	bit_array_t arr = 74591;
	size_t index = 1;

	printf("Is on: \n");
	printf("If the %ld bit of %ld is on, it will return 1, else 0: %d\n",
			index, arr, BitArrIsOn(arr, index));
}

/*---------------------------------------------------------------------------*/

static void BitArrIsOffTest(void)
{
	bit_array_t arr = 74591;
	size_t index = 1;

	printf("Is off: \n");
	printf("If the %ld bit of %ld is off, it will return 1, else 0: %d\n",
			index, arr, BitArrIsOff(arr, index));
}

/*---------------------------------------------------------------------------*/

static void BitArrFlipTest(void)
{
	bit_array_t arr = 74591;
	size_t index = 1;

	printf("Bit Flip: \n");
	printf("The original number: %ld, the index: %ld\n", arr, index);
	printf("%ld\n", BitArrFlip(arr, index));
}

/*---------------------------------------------------------------------------*/

static void BitArrMirrorTest(void)
{
	bit_array_t arr = 1;

	printf("Mirror: \n");
	printf("The original number: %lu\n", arr);
	printf("%lu\n", BitArrMirror(arr));
}

/*---------------------------------------------------------------------------*/

static void BitArrMirrorLUTTest(void)
{
	bit_array_t arr = 1;

	printf("Bits mirror with LUT: \n");
	printf("The original number: %lu\n", arr);
	printf("%lu\n", BitArrMirrorLUT(arr));
}

/*---------------------------------------------------------------------------*/

static void BitArrRotRTest(void)
{
    bit_array_t arr = 1;

	printf("Rotate Right: \n");
	printf("Before rotation: %lu\n", arr); 
    printf("After rotation: %lu\n",BitArrRotR(arr,350));
	
}

/*---------------------------------------------------------------------------*/

static void BitArrRotLTest(void)
{
    bit_array_t arr = 1;

	printf("Rotate Left: \n");
	printf("Before rotation: %lu\n", arr); 
    printf("After rotation: %lu\n",BitArrRotL(arr,1));
}

/*---------------------------------------------------------------------------*/

static void BitArrCountOnTest(void)
{
	bit_array_t arr = 57000;

	printf("Bits on: \n");
	printf("The number: %ld has %ld bits on\n", arr, BitArrCountOn(arr));
}

/*---------------------------------------------------------------------------*/

static void BitArrCountOnLUTTest(void)
{
	bit_array_t arr = 57000;
	printf("Bits on with LUT: \n");
	printf("The number: %ld has %ld bits on\n", arr, BitArrCountOnLUT(arr));
}

/*---------------------------------------------------------------------------*/

static void BitArrCountOffTest(void)
{
	bit_array_t arr = 1024;

	printf("Bits on: \n");
	printf("The number: %ld has %ld bits off\n", arr, BitArrCountOff(arr));
}

/*---------------------------------------------------------------------------*/













