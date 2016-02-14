#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <time.h>

typedef struct scheduler scheduler_t;
typedef struct scheduler_task_id scheduler_task_id_t;

typedef enum 
{
	TASK_SUCCESS =  0;
	TASK_FAIL    = -1;
	TASK_FINISH  =  1;
}exit_status_t;

typedef exit_status_t (*do_func)(void *data);

/* Creates a new scheduler */
scheduler_t *SchedulerCreate();

/* Destroys a scheduler */
void SchedulerDestroy(scheduler_t *scheduler);

/* Returns 1 if the scheduler is empty, 0 otherwise */
int SchedulerIsEmpty(const scheduler_t *scheduler);

/* Adds a new task to the scheduler, in a priortised manner */
const scheduler_task_id_t *SchedulerInsertTask(scheduler_t *scheduler, 
											   do_func fp, 
											   void *data, 
											   time_t time_interval);

/*  Finds and removes the first task who is matching the criteria 
* in the user's is_match function. the user can't define the direction
* of the search in the scheduler. returns 0 for success, 1 otherwise */
int SchedulerRemove(scheduler_t *scheduler,  const scheduler_task_id_t *task_id);

/* clear the scheduler */
void SchedulerClear(scheduler_t *scheduler);

/* Runs all scheduler's tasks. returns 0 for success, 1 otherwise */
int SchedulerRun(scheduler_t *scheduler);

#endif /* __SCHEDULER_H__ */
