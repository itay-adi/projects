/* A Priority Queue is an extension of queue, in which every element has 
   a priority associated with it.
   
Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the pqueue.
-	Is based on priority queue

Main operations on Queue:
-   PQCreate - returns an pointer to an empty pqueue. O(1)
-   PQDestroy - destory a given pqueue. O(n)
-   PQSize - returns a count of total elements in a given pqueue. O(n)
-   PQIsEmpty - checks if a given pqueue is empty. O(1) 
-   PQEnqueue - Inserts a new element to a given pqueue, according to a 
                given priority. O(n)
-   PQDequeue - removes data from the start of a given pqueue. O(1)
-	PQPeek - retrieves data which is set on the start of a given pqueue. O(1)
-   PQClear - Clears all the elements from the pqueue. O(n)
-   PQErase - Finds the first element to match the given param, returns the 
			  data, and removes the element from the pqueue. O(n)
	

Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.
*/

/*************************************************************/

pqueue implemintation consist 3 files:

pqueue.h: a header file
pqueue.c: functions implemintation
pqueue_test.c for a functionality testing

/*************************************************************/
