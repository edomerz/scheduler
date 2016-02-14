
#include "task.h"
/*#include "scheduler_def.h"*/


/*struct task_adt*/
/*{*/
/*	do_func DoFunc;*/
/*	void *data;*/
/*	time_t time_interval;*/
/*	time_t elapsed_time;*/
/*	uuid_t uid;*/
/*};*/


int IsBefore(const void *task1, const void *task2)
{
	return( ((task_t*)task1)->elapsed_time <= ((task_t*)task2)->elapsed_time );
}

task_t *TaskCreate(do_func DoFunc, void *data, time_t time_interval)
{
	task_t *task = (task_t*)malloc(sizeof(task_t));
	assert(task);
	
	task->DoFunc = DoFunc;
	task->data = data;
	task->time_interval = time_interval;
	
	task->elapsed_time = time_interval + time(0);
	task->uid = UuidCreate();
	
	return(task);
}

void TaskDestroy(task_t *task)
{
	free(task);
}

int TaskRun(task_t *current_task)
{
	time_t cur_time = (assert(current_task), 0);
	
	printf("\n[%s %s %d]\n", __FILE__, __func__, __LINE__); /* DEBUG !!! */
	
	if(current_task->elapsed_time > (cur_time = time(NULL)))
	{
		sleep(current_task->elapsed_time - cur_time);
	}
	
	return(current_task->DoFunc(current_task->data));
}

int TaskCompere(const void *task1, const void *task2)
{
	return(UuidIsEqual(((task_t*)task1)->uid, ((task_t*)task2)->uid) );
}




