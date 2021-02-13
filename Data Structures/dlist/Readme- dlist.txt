/* 
 doubly linked list is a linear data structure, 
 each node contains, besides the next-node link,
 a second link field pointing to the 'previous' node in the sequence

Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the list and iterators to data as needed.

Main operations on DLL:
-   Begin - returns an iterator to the first element in the list. O(1)
-   End - returns an iterator to the end of the list. O(1)
-   Next - returns an iterator to the next element. O(1)
-   prev - returns an iterator to the previeus element in the list. O(1)
-   GetData - retrieves data from current iterator. O(1) 
-   SetData - sets data in current iterator. O(1)
-   Is_Equal - checks if two iterators are identical. O(1)
-   Insert - inserts data before given iterator. O(1)
-   Remove - removes given iterator. O(1)
-   size - counts the elements in the list. O(n)
-   pushfront - insert data to begnining the of the list O(1) 
-   pushback - insert data to end the of the list O(1)
-   popfront - remove data from  the begining of the list O(1)
-   popback -remove data from  the end of the list O(1)
-   Find - finds data stored in list. O(n)
-   ForEach - performs an operation given by the user on all elements in the
	list. O(n)
-	splice - slices the range from src list and appends to the dest list before 
	the iterator where O(1)

Generally, in case of errors will return the end of the list. User should
compare the results with the end of the list to determine errors. 
Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.


/*************************************************************/

Circular buffer implemintation consist 3 files:

dlist.h: a header files
dlist.c: functions implemintation
dlist_test.c for a functionality testing

/*************************************************************/
