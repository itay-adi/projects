
BitArray is an array of 32 / 64 bits. 

Operations on bits: 
-	Set ON / OFF - idividually by index, or all at once
-	Flipped - change ON to OFF and vice versa, for each bit individually
-	Rotated left / right by a given number of bits
-	Get each bit's value (0 / 1)

Operations on array:
-	Mirroring the whole array
-	Count number of ON / OFF bits in array
-	Export to string
 	 
API supports both 32bit and 64bit systems. Array has number of bits as in the 
WORD in the machine: on 64bit systems, array will be 64 bits long. 
On 32bit systems, will be 32 bits long.

/*************************************************************/

BitArray implemintation consist 3 files:

bit_array.h: a header file
bit_array.c: functions implemintation
bit_array_test.c for a functionality testing

/*************************************************************/
