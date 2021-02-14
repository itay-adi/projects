Singly linked list is a linear data structure where each element points to the 
next, and memory is not continguous.

Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the list and iterators to data as needed.

Main operations on SLL:
-   Begin - returns an iterator to the first element in the list. O(1)
-   End - returns an iterator to the end of the list. O(1)
-   Next - returns an iterator to the next element. O(1)
-   GetData - retrieves data from current iterator. O(1) 
-   SetData - sets data in current iterator. O(1)
-   Is_Equal - checks if two iterators are identical. O(1)
-	InsertAfter - inserts data after given iterator. O(1)
-   Insert - inserts data before given iterator. O(1)
-   Remove - removes given iterator. O(1)
-   Count - counts the elements in the list. O(n)
-   Find - finds data stored in list. O(n)
-   ForEach - performs an operation given by the user on all elements in the
	list. O(n)
-	Append - appends the src list to the end of dest list.

Generally, in case of errors will return the end of the list. User should
compare the results with the end of the list to determine errors. 
Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.

/*************************************************************/

slist implemintation consist 6 files:

slist.h, slist_additional.h: two header files
slist.c, slist_additional.c: functions implemintation
slist_test.c for a functionality testing

/*************************************************************/
