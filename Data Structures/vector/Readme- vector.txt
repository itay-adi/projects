Stack is a LIFO policy structure.

Dynamic vector is a random access dynamic array.

Attributes:
-   Capacity is a user given value
-   Can hold pointers to any type of data, including structs
-   All Operations are amortized O(1)

Main operations on vector:
-	Get element - Retrieves the value of the element at a specific index
-   Push back - adds an element to the end of the size of the vector
-   Pop back - removes the last element that was not yet removed
-   Set element- sets the value of the element at a specific index
-   Reserve - reallocates memory to the new capacity
-   Shrink to fit - shrinks capacity of the memory to the current size

/*************************************************************/

Stack implemintation consist 3 files:

vector.h: a header file
vector.c: function implemintations
vector_test.c for a functionality testing

/*************************************************************/
