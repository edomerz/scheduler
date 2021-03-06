#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "dlist.h"
#include "sorted_list.h"
#include "priority_queue.h"

struct priority_queue_adt
{
	dlist_t *pdlist;
	int (*is_before)(const void *data1, const void *data2);
};

/*typedef struct priority_queue_adt p_queue_t;*/

/* creates a new priority queue, with the user's function for priortising it's entries */
p_queue_t *PriorityQueueCreate(int (*is_before)(const void *data1, const void *data2))
{
	p_queue_t *pq = (p_queue_t*)SrtListCreate(is_before);
	if(!pq)
	{
		return(NULL);
	}	
	
	return(pq);
}

/* destroy priority queue */
void PriorityQueueDestroy(p_queue_t *pq)
{
	SrtListDestroy((srt_list_t *)pq);
}

/*  Inserts a new element to the queue in priortized manner */
int PriorityQueueEnqueue(p_queue_t *pq, void *data)
{
	if(!SrtListInsert((srt_list_t*)pq, data))
	{
		return(0);
	}
	return(1);
}

/* pops element from the queue. returns the popped data */
/* returns NULL if queue is empty  */
void *PriorityQueueDequeue(p_queue_t *pq)
{
	return(SrtListPopFront((srt_list_t *)pq));	
}

/*  returns the data found in the next element to be popped 
*  returns NULL if queue is empty */
void *PriorityQueuePeek(const p_queue_t *pq)
{
	return(SrtListGetData(SrtListBegin((srt_list_t *)pq)));
}

/* returns the number of elements in the queue */
size_t PriorityQueueSize(const p_queue_t *pq1)
{
	return(SrtListSize((srt_list_t *)pq1));
}

/* returns 1 if queue is empty, 0 otherwise */
int PriorityQueueIsEmpty(const p_queue_t *pq)
{
	return(SrtListIsEmpty((srt_list_t*)pq));
}

/* clears all the elements from the queue */
void PriorityQueueClear(p_queue_t *pq)
{
	while(!PriorityQueueIsEmpty(pq))
	{
		SrtListPopFront((srt_list_t*)pq);	
	}
	return;
}

/*  finds and removes the first element who is matching the criteria 
* in the user's is_match function. the user can't define the direction
* of the search in the queue */
void *PriorityQueueRemove(p_queue_t *pq, 
						  int (*is_match)(const void *data, const void *param), 
						  void *param)
{
	srt_iter_t cur = ((assert(pq), SrtListBegin((srt_list_t*)pq)));
	srt_iter_t end = SrtListEnd((srt_list_t*)pq);
	int status = 0;
	
	assert(is_match);
	
	while((!SrtListIsSameIter(cur, end)))
	{
		status = is_match(SrtListGetData(cur), param);
		if(status)
		{
			SrtListRemove(cur);
			return(SrtListGetData(cur));
		}
		cur = SrtListNext(cur);
	}	
	return(NULL);
}
