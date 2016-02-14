#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "scheduler.h"
#include "task.h"
#include "priority_queue.h"

int TaskCompere(const void *task1, const void *task2);
int IsBefore(const void *task1, const void *task2);

struct scheduler
{
	p_queue_t *pq;
	task_t *CurrentTask;
};

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *s = (scheduler_t*)malloc(sizeof(scheduler_t));
	assert(s);
	
	s->pq = PriorityQueueCreate(IsBefore);
	if(!s->pq)
	{
		free(s);
		
		return(NULL);
	}
	
	s->CurrentTask = NULL;
	
	return(s);
}

void SchedulerDestroy(scheduler_t *s)
{
	assert(s);
	SchedulerClear(s);
	
	PriorityQueueDestroy(s->pq);
	
	free(s);
}

int SchedulerIsEmpty(const scheduler_t *s)
{
	assert(s);
	
	return(PriorityQueueIsEmpty(s->pq));
}

uuid_t SchedulerInsertTask(scheduler_t *s, do_func fp, void *data, time_t time_interval)
{
	task_t *task = (assert(s), assert(fp), NULL);
	
	task = TaskCreate(fp, data, time_interval);
	if(!task)										/* failed TaskCreate */
	{
		return(UuidCreateNull());
	}
	
	if(!PriorityQueueEnqueue(s->pq, (void*)task))	/* failed Enqueue */
	{
		TaskDestroy(task);
		
		return(UuidCreateNull());
	}
	
	return(task->uid);	
}

/* clear the scheduler */
void SchedulerClear(scheduler_t *s)
{
	void *poped_task = (assert(s), NULL);
	
	while(!PriorityQueueIsEmpty(s->pq))
	{
		poped_task = PriorityQueueDequeue(s->pq);
		
		TaskDestroy(poped_task);
	}
	
	return;
}

int SchedulerRun(scheduler_t *s)
{
	int ret = (assert(s), 1);
	exit_status_t exit;
	
	while(!SchedulerIsEmpty(s))
	{
		s->CurrentTask = PriorityQueueDequeue(s->pq);
		
		exit = TaskRun(s->CurrentTask);
		
		if(exit == 0)
		{
/*			TaskUpdate(s->CurrentTask);*/
			
			PriorityQueueEnqueue(s->pq, (void*)(s->CurrentTask));
			
			s->CurrentTask = NULL;
		}
		else
		{
			TaskDestroy(s->CurrentTask);
			s->CurrentTask = NULL;
		}
	}
	return(ret = 0);
}

int IsMatch(const void *task, const void *task_param)
{
	return(UuidIsEqual( ((task_t*)task)->uid, *((uuid_t*)task_param) ));
}

int SchedulerRemove(scheduler_t *s, uuid_t uid)
{
	void *ret = (assert(s), NULL);
	
	ret = PriorityQueueRemove(s->pq, &IsMatch, (void*)(&uid));
	
	TaskDestroy(ret);
	
	return( ret == NULL ? 1 : 0);
}


