
/***************************User's declarations********************************/
#include <stdio.h>
#include <stdlib.h>

#include "scheduler.h"

/************************Test function declarations****************************/

static void SchDestroyTest(sch_t *sch);
static void SchTimerStartTest(sch_t *sch, size_t interval_in_sec,
					   sch_task_func_t task, void* param);
static void SchTimerCancelTest(sch_t *sch, unique_id_t uid);
static void SchStopTest(sch_t *sch);
static void SchRunTest(sch_t *sch);

/**********************Test case function declarations*************************/

static void SchedulerTestCase(void);

/****************************Tasks declarations********************************/

int Task1(sch_t *sch, unique_id_t uid, void *param);
int Task2(sch_t *sch, unique_id_t uid, void *param);

/**********************************main****************************************/

int main(void)
{
	printf("----------------------------------------\n");
	SchedulerTestCase();
	printf("----------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

static void SchDestroyTest(sch_t *sch)
{
	SchDestroy(sch);

	printf("\nScheduler has been destroyed.\n");
}

/**********************************************************************/

static void SchTimerStartTest(sch_t *sch, size_t interval_in_sec,
					   sch_task_func_t task, void* param)
{
	if (UIDIsSame(SchTimerStart(sch, interval_in_sec, task, param),
				  UIDGetBadUID()))
	{
		printf("Cannot add the new task, please try again.\n");
	}

	else
	{
		printf("Task was added successfully.\n");
	}
}

/**********************************************************************/

static void SchTimerCancelTest(sch_t *sch, unique_id_t uid)
{
	SchTimerCancel(sch, uid, NULL);
	printf("\nTask has been cancelled\n");
}

/**********************************************************************/

static void SchStopTest(sch_t *sch)
{
	if(SchStop(sch))
	{
		printf("\nScheduler has been stopped.\n");
	}

	else
	{
		printf("\nScheduler was not been stopped.\n");
	}
}

/**********************************************************************/

static void SchRunTest(sch_t *sch)
{
	printf("\nSchedule is running.\n");
	
	if(!SchRun(sch))
	{
		printf("\nThe schedule is now empty\n");
	}

	else
	{
		printf("\nThe schedule is not empty yet.\n");
		
	}
}

/********************Test case function Implementations************************/

static void SchedulerTestCase(void)
{
	sch_t *sch = NULL;
	int *arr = NULL;
	unique_id_t uid = {0,0,0};
	
	arr = (int *)malloc(sizeof(int) * 2);

	arr[0] = 3;
	arr[1] = 4;
	
	/*creating the scheduler*/
	sch = SchCreate();

	/*insert tasks to the scheduler*/
	SchTimerStartTest(sch, 3, Task1, &arr[0]);
	SchTimerStartTest(sch, 2, Task2, &arr[1]);
	/*run the schedule*/
	SchRunTest(sch);

	/*insert 3 tasks and remove 1*/
	SchTimerStartTest(sch, 3, Task1, &arr[0]);
	uid = SchTimerStart(sch, 3, Task1, &arr[0]);
	SchTimerCancelTest(sch, uid);
	SchTimerStartTest(sch, 3, Task1, &arr[0]);
	/*run the schedule*/
	SchRunTest(sch);

	SchStopTest(sch);

	/*destroying the scheduler*/
	SchDestroyTest(sch);

	free(arr);
	arr = NULL;
}

/***************************Tasks implementation*******************************/

int Task1(sch_t *sch, unique_id_t uid, void *param)
{
	(void)sch;
	(void)uid;

	printf("Task1: alert after %d seconds\n", *(int *)param);

	return (0);
}

/**********************************************************************/

int Task2(sch_t *sch, unique_id_t uid, void *param)
{
	static size_t count = 3;
	(void)uid;
	(void)sch;
	
	if (3 == count)
	{
		printf ("Task2: alert after %d seconds.\n", *((int *)param));
		--count;
	}

	else if (2 == count)
	{
		printf("Task2: alert after %d seconds.\n", *((int *)param) * 2);
		--count;
	}

	else
	{
		printf("Task2: alert after %d seconds.\n", *((int *)param) * 3);
		--count;
	}

	return (count > 0);
}

/******************************************************************************/


















