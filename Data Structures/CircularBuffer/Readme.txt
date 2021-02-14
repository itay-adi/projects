
* Circular buffer is a data structure with limited capacity, allowing re-use of the same memory areas.
*
* Attributes:
* -	Capacity is a user given value
*  
* Main operations on Circular buffer:
* -	Create - create a new buffer according to a given capacity. O(1)
* -	Destroy -destroy a given buffer. O(1)
* -	Read - Read "count" bytes from a given buffer, and writes it to a given dest. O(n)
* -	Write - Write "count" bytes into a given buffer. O(n)
* -	IsEmpty - Check if a given buffer is empty. O(1)
* -	FreeSpace - Check how many free spaces a given buffer has, in bytes. O(1)
* -	Capacity - Get the capacity of a given buffer. O(1)
*


/*************************************************************/

Circular buffer implemintation consist 3 files:

c_buffer.h: a header file
c_buffer.c: functions implemintation
c_buffer_test.c for a functionality testing

/*************************************************************/
