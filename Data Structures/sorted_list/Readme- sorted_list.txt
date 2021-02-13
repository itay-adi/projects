/*
 sorted list is a linear data structure, where elements are sorted according
 to a criterion determined by the user.
Policy: Sort at insert
		Stable sort
		User provides a function to sort by

Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the list and iterators to data as needed.
-	Is based on dlist

Main operations on Sorted List:
-	Begin - returns an iterator to the first element in the list. O(1)
-	End - returns an iterator to the end of the list. O(1)
-	Next - returns an iterator to the next element. O(1)
-	Prev - returns an iterator to the previeus element in the list. O(1)
-	GetData - retrieves data from current iterator. O(1) 
-	Is_Equal - checks if two iterators are identical. O(1)
-	Insert - sorted insert to the list. O(n)
-	Remove - removes given iterator. O(1)
-	Size - counts the elements in the list. O(n)
-	PopFront - remove data from  the begining of the list O(1)
-	PopBack -remove data from  the end of the list O(1)
-	FindIf - finds data stored in list. O(n)
-	Find - finds where requested data is in the list. O(n)
-	ForEach - performs an operation given by the user on all elements in the
	range. O(n)
-	Merge - merges dest and src, two lists sorted based on the same
	criterion, into dest. Dest will be sorted after merge. O(n)

Generally, in case of errors will return the end of the list. User should
compare the results with the end of the list to determine errors. 
Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.

/*************************************************************/

slist implemintation consist 3 files:

sorted_list.h: a header file
sorted_list.c: functions implemintation
sorted_list.c for a functionality testing

/*************************************************************/
