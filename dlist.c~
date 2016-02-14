#include <assert.h>
#include <stdlib.h>
#include "dlist.h"

/*using assert at the beginning*/
/*int i = (assert(i), 10);*/
/*with no degub, meainig no assert, assert turn into*/
/*int i = ( (0), 10);*/

typedef struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
}dlist_node;

typedef struct dlist_adt
{
	dlist_node head;
	dlist_node tail;
}dlist_adt;




/* typedef struct dlist dlist_t; */
/* typedef struct dlist_node *dlist_iter_t; */

/*typedef int(*is_match_func)(const void *data, const void *seek);*/
/*typedef int(*action_func)(void *data, void *param);*/

/*creates a new node*/
dlist_iter_t DListCreateNode(void *data)
{
	dlist_iter_t node = (dlist_iter_t)malloc(sizeof(dlist_node));
	if(!node)
	{
		return(NULL);
	}
	
/*	*(size_t**)&node->data = (size_t)data;*/
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	
	return(node);
}

/* Creates a new list and returns a pointer to it. */
dlist_t *DListCreate(void)
{
	dlist_t *list = (dlist_t *)malloc(sizeof(dlist_t));
	assert(list);

	printf("\nFILE:%s, func:%s, LINE:%d \n", __FILE__, __func__, __LINE__); /* DEBUG!!! */
	printf("sizeof(dlist_t):%lu\n", sizeof(dlist_t));
		
	list->head.prev = NULL;
/*	list->head.next = NULL;*/
	list->head.next = &list->tail;
	
	list->tail.next = NULL;
/*	list->tail.prev = NULL;*/
	list->tail.prev = &list->head;	
	
	return(list);
}

/* Destroys a list. */
void DListDestroy(dlist_t *dlist)
{
	dlist_iter_t cur = DListBegin(dlist);
	dlist_iter_t end = DListEnd(dlist);
	
	/*dlist_iter_t last_ptr = DListEnd(dlist); dlist->tail.prev;*/
	dlist_iter_t tmp = NULL;
	
	if(DListIsEmpty(dlist))/* if empty list, free dlist struct only( nothing else to free) */
	{
		free(dlist);
		return;
	}
	
	while(!DListIsSameIter(cur, end))
	{
		tmp = cur;
		cur = DListNext(cur);
		free(tmp);
	}
	
/*	for(tmp = last_ptr->prev; (last_ptr) && (last_ptr != &dlist->head); tmp = tmp->prev)*/
/*	{*/
/*		free(last_ptr);*/
/*		last_ptr = tmp;*/
/*	}*/
	free(dlist);
}

/* Returns the number of elements inside the list. */
size_t DListSize(const dlist_t *dlist)
{
	size_t count = 0;
	dlist_iter_t s = DListBegin(dlist); /* dlist->head.next;*/
	dlist_iter_t e = DListEnd(dlist);
	
	while(!DListIsSameIter(s, e))
	{
		++count;
		s = DListNext(s);
	}
	return(count);
}

/* Checks if the list is empty. If true returns 1, else - returns 0. */
int DListIsEmpty(const dlist_t *dlist)
{
	return(DListSize(dlist) == 0);
}

/* Returns an iterator to the first/last element of a list. */
dlist_iter_t DListBegin(const dlist_t *dlist)
{
	return(dlist->head.next);
}
dlist_iter_t DListEnd(const dlist_t *dlist)
{
	return((dlist_iter_t)(&dlist->tail));
}

/* Returns an iterator to the succeeding/preceding element of item. */
dlist_iter_t DListNext(const dlist_iter_t item)
{
	return(item->next);
}
dlist_iter_t DListPrev(const dlist_iter_t item)
{
	return(item->prev);
}

/* Checks if two iterators point to the same element. */
/*If true returns 1, else - returns 0. */
int DListIsSameIter(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	return(iter1 == iter2);
}

/* Returns the data of item. */
void *DListGetData(dlist_iter_t item)
{
	return(item->data);
}

/* Inserts a new element before 'where',  assign it with 'data'*/
/*   and returns an iterator to it. */
dlist_iter_t DListInsertBefore(dlist_t *dlist, dlist_iter_t where, void *data)
{
	dlist_iter_t nn = (assert(where), DListCreateNode(data));

	/* where == NULL */
/*	if(!where)*/
/*	{*/
/*		return(DListEnd(dlist));*/
/*	}*/
	
	nn->next = where;
	nn->prev = DListPrev(where);
	
	where->prev->next = nn;
	where->prev = nn;
	
	return(nn);
}

/* cut & paste the elements in the range 'begin'-'end' to before 'where'.  */
/*   Returns an iterator to first spliced element. */
dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t begin, dlist_iter_t end)
{
	
	dlist_iter_t bp = (assert(begin), DListPrev(begin));/*begin->prev;*/
	dlist_iter_t wp = (assert(where), DListPrev(where)); /* where->prev;*/
	assert(end);
	
	begin->prev = wp;
	where->prev = end->prev;
	
	bp->next = end;
	wp->next = begin;
	
	end->prev->next = where;
	end->prev = bp;
	
	return(begin);
}

/* Removes the element. return the element->next */
dlist_iter_t DListRemove(dlist_iter_t element)
{
	dlist_iter_t ret = (assert(element), DListNext(element));
/*	ret = element->next;*/
	element->prev->next = DListNext(element);
	element->next->prev = DListPrev(element);
	
	free(element);
	
	return(ret);
}

/* Inserts a new element to the beginning/end of the list, assign it with data*/
/*and return it */
dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	return(DListInsertBefore(dlist, DListBegin(dlist), data));
}

dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	return(DListInsertBefore(dlist, DListEnd(dlist), data));
}

/*  Removes the first/last element of the list. return the poped data */
void *DListPopFront(dlist_t *dlist)
{
	void *ret = (assert(dlist), DListGetData(DListBegin(dlist)));
	
	DListRemove(DListBegin(dlist));

	return(ret);
}
void *DListPopBack(dlist_t *dlist)
{
	dlist_iter_t poped = (assert(dlist), DListPrev(DListEnd(dlist)));
	void *ret = DListGetData(poped);
	
	DListRemove(poped);
	
/*	if(!poped)*/
/*	{*/
/*		return(NULL);*/
/*	}*/
/*	*/
/*	dlist->tail.prev = poped->prev;*/
/*	poped->prev->next = &dlist->tail;*/
/*	ret = poped->data;*/
/*	*/
/*	free(poped);*/
	return(ret);
}

/* Finds 'seek' inside a list, using the function pointed by 'fp'.*/
/*Returns an iterator to the element found or 'end' */
dlist_iter_t DListFind(dlist_iter_t begin, dlist_iter_t end, is_match_func fp, const void *seek)
{
	int status = 0;
	while(!DListIsSameIter(begin, end))
	{
		status = fp(DListGetData(begin), seek);
		if(status)
		{
			return(begin);
		}
		begin = DListNext(begin);
	}
	return(begin);
}

/* Performs an action deteremined by 'action_func' on each element of the range 'begin' to 'end'. */
/*   DListForEach stops upon fp failure. DListForEach returns fp exit status. */
int DListForEach(dlist_iter_t begin, dlist_iter_t end, action_func fp, void *param)
{
	int status = -1;
	
	while( (!DListIsSameIter(begin, end)) && (status))
	{
		status = fp(DListGetData(begin), param);
		begin = DListNext(begin);
	}
	return(status);
}
