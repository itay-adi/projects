#ifndef ILRD_CIRCULAR_BUFFER_H
#define ILRD_CIRCULAR_BUFFER_H

#include <unistd.h> /* ssize_t */
#include <stddef.h> /* size_t  */

typedef struct c_buffer c_buffer_t;

/*---------------------------------------------------------------------------*/

/* CBufferCreate:
*   - Creates a new circular buffer
* Args:
*   - capacity of the new c_buffer, in bytes
*  
* Return Value:
*   Pointer to c_buffer if succeeded
*   Null if failed
*/
c_buffer_t *CBufferCreate(size_t capacity);

/*---------------------------------------------------------------------------*/

/* CBufferDestroy:
*   - Destroys given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*     
*/
void CBufferDestroy(c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

/* CBufferRead:
*   - Reads data from given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*   - dest - The buffer to write to (must be large enough to contain the data) 
*   - count - number of bytes to read from buffer
* 
* Return Value:
*   -number of bytes read from buffer
*   -(-1) for error 
*   
* Comments:
*    -in case of an error, errno will be updated with the given case:
*        -(ENODATA)  No data available while trying to read.
*    -in case of an invalid dest - undefined behavior.
*/
ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count);

/*---------------------------------------------------------------------------*/

/* CBufferWrite:
*   - Writes a given number of bytes into the given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*   - src - source of data to write into buffer
*   - count - number of bytes to write into buffer
*
* Return Value:
*   -number of bytes to write into buffer
*   -(-1) for error
* 
* Comments:
*    -in case of an error, errno will be updated with the given case:
*       -(ENOBUFS) No buffer space available.
*    -in case of an invalid src - undefined behavior.
*/
ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count);

/*---------------------------------------------------------------------------*/

/* CBufferIsEmpty:
*   - checks if the buffer is empty or not
* 
* Args:
*   - c_buffer - pointer to c_buffer given by user
*  
* Return Value:
*   1 - empty (TRUE)
*   0 - not empty (FALSE)       
*/
int CBufferIsEmpty(const c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

/* CBufferFreeSpace:
*   - Returns the amount of free space a given buffer has, in bytes
* 
* Args:
*   - c_buffer - pointer to c_buffer given by user
*  
* Return Value:
*   number of free bytes in the buffer
*/
size_t CBufferFreeSpace(const c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

/* CBufferCapacity:
*   - Returns the capacity of a given buffer in bytes
* 
* Args:
*   - c_buffer - pointer to c_buffer given by user
*  
* Return Value:
*   Number of capacity in a given buffer in bytes
*/
size_t CBufferCapacity(const c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_CIRCULAR_BUFFER_H */
