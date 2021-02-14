/* a heap is a specialized tree-based data structure which is essentially an 
almost complete. Heap stores the max/min value in its root.

-------------------------------------------------------------------------------

heapify:
heap util file, contains funtions to support Heap DS.

Util functions include:
-   HeapifyUp - re-arranges the array to have a heap property, going bottom-up
-   HeapifyDown - re-arranges the array to a have heap property, going up-bottom

-------------------------------------------------------------------------------

Heap is based on:
-vector
-heap sort

-------------------------------------------------------------------------------

Operations on heap:
-   Push - adds an element to the heap.
-   Pop - removes the top element of the heap.
-   Peek - displays the first element of heap which is the min / max value
-   Remove - removes given element from the heap
    a pointer to it.

-------------------------------------------------------------------------------

heap implemintation consist 3 files:

heap.h, heapify.h: two header files
heap.c, heapify.c: functions implemintation
heap_test.c for a functionality testing
heap_sort.c: sorting algoritm using the heapifies

-------------------------------------------------------------------------------
