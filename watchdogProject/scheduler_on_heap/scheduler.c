/******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <time.h> /* time_t */
#include <assert.h>	/* assert */

#include "scheduler.h"
#include "uid.h"
#include "pqueue.h"

struct scheduler
{
	pqueue_t *pq; /* priority queue for schedule timers */
	int stop;     /* a flag to be raised when we want to stop running */
};

struct timer
{
	unique_id_t uid;    	/* unique timer id */
	time_t wake_time;	/* time to sleep after prev timer */
	size_t interval;		/* interval recieved from user */
	sch_task_func_t task;   /* task to be performed by timer */
	void *param;			/* parameter to be passed to task */
};

#define SUCCESS 0
#define FAIL 1

typedef struct timer timer_sec_t;

/******************************************************************************/

static int Interval_SecCmp(const void *data1, const void *data2, void *param);
static int Interval_IsMatch(const void *data1, const void *data2, void *param);

/******************************************************************************/

sch_t *SchCreate(void)
{
	sch_t *sch = NULL;
	
	sch = (sch_t *)malloc(sizeof(sch_t));
	
	if(!sch)
	{
		return (NULL);
	}

	sch->pq = PQCreate(Interval_SecCmp, NULL);

	if(!sch->pq)
	{
		free (sch);
		sch = NULL;
		
		return (NULL);
	}

	sch->stop = 0;

	return (sch);
}

/******************************************************************************/

void SchDestroy(sch_t *sch)
{
	assert(sch);

	while(!PQIsEmpty(sch->pq))
	{
		free(PQDequeue(sch->pq));
	}

	PQDestroy(sch->pq);
	sch->pq = NULL;

	free(sch);

	sch = NULL;
}

/******************************************************************************/

unique_id_t SchTimerStart(sch_t *sch, size_t interval_in_sec,
                                sch_task_func_t task, void* param)
{
	timer_sec_t *timer = NULL;
	time_t now = 0;
	now = time(NULL);
	
	assert(sch);

	if(-1 == now)
	{
		return (UIDGetBadUID());
	}

	/*creates a new task*/
	timer = (timer_sec_t *)malloc(sizeof(timer_sec_t));
	
	if(!timer)
	{
		return (UIDGetBadUID());
	}

	timer->uid = UIDCreate();

	if(UIDIsSame(timer->uid, UIDGetBadUID()))
	{
		free (timer);
		timer = NULL;

		return (UIDGetBadUID());
	}

	timer->wake_time = now + interval_in_sec;
	timer->interval = interval_in_sec;
	timer->task = task;
	timer->param = param;

	/*inserts the new task to the queue*/
	if(1 == PQEnqueue(sch->pq, timer))
	{
		free (timer);
		timer = NULL;
	}

	return (timer->uid);
}

/******************************************************************************/

void SchTimerCancel(sch_t *sch, unique_id_t uid, void *param)
{
	timer_sec_t *temp = NULL;

	assert(sch);

	temp = 	PQErase(sch->pq, &uid, Interval_IsMatch, param);

	free(temp);
	
	temp = NULL;
}

/******************************************************************************/

int SchRun(sch_t *sch)
{
	timer_sec_t *timer = NULL;
	int status = 0;
	time_t now = 0;
	
	assert(sch);

	sch->stop = 0;

	/*run as long as the pq is not empty or not asked to be stopped*/
	while (!PQIsEmpty(sch->pq) && !(sch->stop))
	{
		timer = PQPeek(sch->pq);
		sleep(timer->interval);
		timer = PQDequeue(sch->pq);
		status = timer->task(sch, timer->uid, timer->param);

		/*if the task needs to re-run*/ 
		if (1 == status)
		{
			now = time(NULL);

			if(now == -1)
			{
				return (FAIL);
			}

			timer->wake_time = now + timer->interval;
			
			if (PQEnqueue(sch->pq, timer))
			{
				return (FAIL);
			}
		}

		/*if the task has been failed*/
		else if (-1 == status)
		{
			free(timer);
			timer = NULL;
			SchStop(sch);

			return (FAIL);
		}

		/*if the task is finished */
		else
		{
			free (timer);
			timer = NULL;
		}
	}
	
	return (SUCCESS);
}

/******************************************************************************/

int SchStop(sch_t *sch)
{
	assert(sch);

	sch->stop = 1;

	return (sch->stop);
}

/******************************************************************************/

static int Interval_SecCmp(const void *data1, const void *data2, void *param)
{
	const timer_sec_t *timer1 = data1;
	const timer_sec_t *timer2 = data2;

	(void)param;

	if (timer1->interval > timer2->interval)
	{
		return (1);
	}
	
	else if (timer1->interval < timer2->interval)
	{
		return (-1);
	}
	
	return (0);
}

/******************************************************************************/

static int Interval_IsMatch(const void *data1, const void *data2, void *param)
{
	const timer_sec_t *timer = data1;
	const unique_id_t *uid2 = data2;

	(void)param;

	return (UIDIsSame(timer->uid, *uid2));
}

/******************************************************************************/





