#include <stdio.h>
/*#include "task.h"*/
#include "scheduler.h"
#include "scheduler_def.h"

#include <assert.h>

int DoFunc(void *data);

int main(int argc, char* argv[], char** envp)
{
	
	scheduler_t *s1 = NULL;
	uuid_t uid1;
	/*-----------SchedulerCreate_1----------*/
	printf("\n[%s %s %d]SchedulerCreate_1\n", __FILE__, __func__, __LINE__);
	
	s1 = SchedulerCreate();
	assert(s1);
	
	
	/*-----------SchedulerIsEmpty_1----------*/
	printf("\n[%s %s %d]SchedulerIsEmpty_1\n", __FILE__, __func__, __LINE__);
	
	printf("SchedulerIsEmpty(s1):%d\n", SchedulerIsEmpty(s1));
	
	
	/*-----------SchedulerInsertTask_1----------*/
	printf("\n[%s %s %d]SchedulerInsertTask_1\n", __FILE__, __func__, __LINE__);
	
	uid1 = SchedulerInsertTask(s1, &DoFunc, (void*)1, (time_t)2);
	printf("uid1.counter:%lu		expected result:1\n", uid1.counter);
	printf("uid1.tmal.tv_usec:%lu\n", uid1.tval.tv_usec);
	
	
	/*-----------SchedulerRemove_1----------*/
	printf("\n[%s %s %d]SchedulerRemove_1\n", __FILE__, __func__, __LINE__);
	
/*	printf("SchedulerRemove(s1, uid1):%d", SchedulerRemove(s1, uid1));*/


	/*-----------SchedulerRun_1----------*/
	printf("\n[%s %s %d]SchedulerRun_1\n", __FILE__, __func__, __LINE__);
	
	printf("SchedulerRun(s1):%d\n", SchedulerRun(s1));
	
	/*-----------SchedulerDestroy_1----------*/
	printf("\n[%s %s %d]SchedulerDestroy_1\n", __FILE__, __func__, __LINE__);
	
	SchedulerDestroy(s1);		
	
		
	return(0);
}

int DoFunc(void *data)
{
	printf("data:%lu\n", (size_t)data);

	return(0);
}
