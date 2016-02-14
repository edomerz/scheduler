#ifndef __TASK_H__
#define __TASK_H__

#include <stdio.h>

#include "scheduler_def.h"
/*#include "scheduler.h"*/

struct task_adt
{
	do_func DoFunc;
	void *data;
	time_t time_interval;
	time_t elapsed_time;
	uuid_t uid;
};
typedef struct task_adt task_t;



task_t *TaskCreate(int (*do_func)(void *data), void *data, time_t time_interval);

void TaskDestroy(task_t *task);

int TaskRun(task_t *current_task);

/* compers 2 task according to a predetermined criteria*/
int TaskCompere(const void *task1, const void *task2);






#endif /* ifndef __TASK_H__*/
