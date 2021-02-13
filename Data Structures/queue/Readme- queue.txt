/* A Queue is a linear structure which follows a particular order in which
   the operations are performed. The policy is First In First Out (FIFO). 

Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the queue
-	Based on the slist implementation

Main operations on Queue:
-   QCreate - returns an pointer to an empty queue. O(1)
-   QDestory - destory a given queue. O(n)
-   QSize - returns a count of total elements in a given queue. O(n)
-   QIsEmpty - checks if a given queue is empty. O(1) 
-   QEnqueue - inserts data to the end of a given queue. O(1)
-   QDequeue - removes data from the start of a given queue. O(1)
-	QPeek - retrieves data which is set on the start of a given queue. O(1)
-   QAppend - appends the start of source queue with end of destination queue.
	O(1)

Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.

/* C file
#include "slist.h"

*/

/*************************************************************/

queue implemintation consist 3 files:

queue.h: a header files
queue.c: functions implemintation
queue_test.c for a functionality testing

/*************************************************************/
