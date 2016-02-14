#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h>
 
typedef struct priority_queue_adt p_queue_t;

/* creates a new priority queue, with the user's function for priortising it's entries */
p_queue_t *PriorityQueueCreate(int (*is_before)(const void *data1, const void *data2));

/* destroy priority queue */
void PriorityQueueDestroy(p_queue_t *p_queue);

/*  Inserts a new element to the queue in priortized manner */
int PriorityQueueEnqueue(p_queue_t *p_queue, void *data);

/* pops element from the queue. returns the popped data */
/* returns NULL if queue is empty  */
void *PriorityQueueDequeue(p_queue_t *p_queue);

/*  returns the data found in the next element to be popped 
*  returns NULL if queue is empty */
void *PriorityQueuePeek(const p_queue_t *p_queue);

/* returns the number of elements in the queue */
size_t PriorityQueueSize(const p_queue_t *p_queue);

/* returns 1 if queue is empty, 0 otherwise */
int PriorityQueueIsEmpty(const p_queue_t *p_queue);

/* clears all the elements from the queue */
void PriorityQueueClear(p_queue_t *p_queue);

/*  finds and removes the first element who is matching the criteria 
* in the user's is_match function. the user can't define the direction
* of the search in the queue */
void *PriorityQueueRemove(p_queue_t *p_queue, 
						  int (*is_match)(const void *data, const void *param), 
						  void *param);
						  
#endif /* PRIORITY_QUEUE__ */
