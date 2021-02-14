*  scheduler is a tool used for creating schedulered tasks recurring or
*   non-recurring.
*
*  Tasks can create other tasks, cancel them or add conditional-cancel rules 
*
*  Is based on:
*	UID
*   Priority Queue
*
*
*  Attributes:
* -	Grows by demand.
* -	User has a pointer to the scheduler.
*
* Main operations on scheduler:
* -   SchCreate - Creates an empty scheduler
* -   SchDestroy - Destroys asch given scheduler
* -   SchRun - Hands control over to the app and timers start running, 
*     until scheduler is empty.
* -   SchStop - Stops a running scheduler
*
* -   Timer Start - Starts a new timer in the scheduler
* -   Timer Cancel - Cancels an existing task in the scheduler 
