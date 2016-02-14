#include <assert.h>
#include <stdlib.h>
#include "sorted_list.h"
#include "dlist.h"

struct srt_list_adt
{
	dlist_t *pdlist;
	srt_list_is_before_func fp1;
};


/*typedef struct srt_list_adt srt_list_t;*/
/*typedef struct srt_iter_t ;*/

/* perform an operation on 'element'. */
/*typedef int (*srt_list_action_func)(void *element, void *param);*/

/* pointer to function that return 1 if data1 precedes data2 */
/*typedef int (*srt_list_is_before_func)(const void *data1, const void *data2);*/


/* creates a list */
srt_list_t *SrtListCreate(srt_list_is_before_func fp)
{
	srt_list_t *srt_list = (assert(fp), (srt_list_t*)malloc(sizeof(srt_list_t))); /* check if fp is legit */
	assert(srt_list);
	
	srt_list->pdlist = DListCreate();
	if(!srt_list->pdlist)
	{
		free(srt_list);
		return(NULL);
	}
	srt_list->fp1 = fp;
	
	return(srt_list);
}

/* destroys a list */
void SrtListDestroy(srt_list_t *list)
{
	DListDestroy(list->pdlist);
	free(list);
}

/* returns number of elements in list */
size_t SrtListSize(const srt_list_t *list)
{
	return(DListSize(list->pdlist));
}

/* returns 1 if 'list' is empty, else 0 */
int SrtListIsEmpty(const srt_list_t *list)
{
	return(DListIsEmpty(list->pdlist));
}

/* returns iterator to first/last element of list */
srt_iter_t SrtListBegin(const srt_list_t *list)
{
	return((srt_iter_t)DListBegin(list->pdlist));
}
srt_iter_t SrtListEnd(const srt_list_t *list)
{
	return((srt_iter_t)DListEnd(list->pdlist));
}

/* returns iterators to next/previous element of 'iter' */
srt_iter_t SrtListNext(const srt_iter_t iter)
{
	if(!iter)
	{
		return(NULL);
	}
	return((srt_iter_t)DListNext((dlist_iter_t)iter));
}
srt_iter_t SrtListPrev(const srt_iter_t iter)
{
	if(!iter)
	{
		return(NULL);
	}
	return((srt_iter_t)DListPrev((dlist_iter_t)iter));
}

/* checks if 2 iterator point to same element. returns 1 if true, else 0 */
int SrtListIsSameIter(const srt_iter_t iter1, const srt_iter_t iter2)
{
	return(DListIsSameIter((dlist_iter_t)iter1, (dlist_iter_t)iter2));
}

/* returns data of 'iter' */
void *SrtListGetData(srt_iter_t iter)
{
	return(DListGetData((dlist_iter_t)iter));
}

/* inserts a new element in a sorted manner, assign it with 'data' and 
   return iterator to it */
srt_iter_t SrtListInsert(srt_list_t *list, void *data)
{
	
	srt_iter_t first = (assert(list), SrtListBegin(list));  /* first element of the list */
	void *element_data = SrtListGetData(first); 			/*	holds the data to be compared to the new data*/
	
	srt_iter_t new_element = NULL;
	
	/* insert to an empty list */ 
	if(SrtListIsEmpty(list))
	{
		new_element = (srt_iter_t)DListPushBack(list->pdlist, data);
		return(new_element);
	}
	
	/*	 not an empty list, find the 1st element that should come after the new data to insert*/
	while( !(list->fp1(data, element_data)) && (!SrtListIsSameIter(first, SrtListEnd(list))) )
	{
		first = SrtListNext(first);
		element_data = SrtListGetData(first);
	}
	
	/* inserting to the end of the list */
	if(SrtListIsSameIter(first, SrtListEnd(list)))
	{
		return((srt_iter_t)DListPushBack(list->pdlist, data));	
	}
	
	new_element = (srt_iter_t)DListInsertBefore(list->pdlist, (dlist_iter_t)first, data);
	assert(new_element);						/* DEBUG!!!!!!!!!!!!!!!!!!! */
	
	return(new_element);
}

/* remove element pointed by iterator, returns iterator to next element */
srt_iter_t SrtListRemove(srt_iter_t iter)
{
	assert(iter);
	
	return((srt_iter_t)DListRemove((dlist_iter_t)iter));
}

/* removes first/last element of list, and returns it's data */
void *SrtListPopFront(srt_list_t *list)
{
	return(DListPopFront(list->pdlist));
}
void *SrtListPopBack(srt_list_t *list)
{
	return(DListPopBack(list->pdlist));
}


typedef struct help_t
{
	const void *data;
	srt_list_is_before_func fp1;
}help_t;

static int IsBefore(const void *data1, const void *data2)
{
/*	the data we seek(held in the struct of data2), is smaller then item on the list*/
/*	which only grows*/
	int smaller = ((help_t*)data2)->fp1(((help_t*)data2)->data, data1);
	
/*	the item on our list is smaller then the one we seek, move along the list*/
	int larger = ((help_t*)data2)->fp1(data1, ((help_t*)data2)->data);

	if(smaller) /* no need to look any further */
	{
		return(1);
	}
	if(!smaller && !larger)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
/* from the range 'begin' to 'end', return the first element containing 'data'.
   return 'end' if not found */
srt_iter_t SrtListFind(const srt_list_t *list, srt_iter_t begin, srt_iter_t end, const void *data)
{
	srt_iter_t ret_node = NULL;
	help_t h;
	h.data = data;
	h.fp1 = list->fp1;
	
	/* gets the recived node, either found a node with same data, or, seek data is smaller
	then returned node(no need to look along the rest of the list*/
	ret_node = (srt_iter_t)DListFind((dlist_iter_t)begin, (dlist_iter_t)end, &IsBefore, &h);
	
	return((list->fp1(data, DListGetData((dlist_iter_t)ret_node))) ? (SrtListEnd(list)) : (ret_node));
}
/* send each element in range: 'begin'-'end' to function fp, or until fp fails (excluding 'end')  */
/* according to action_func. returns exit status upon failure, 0 otherwise          */
int SrtListForeach(srt_iter_t begin, srt_iter_t end, srt_list_action_func fp, void *data)
{
	return(DListForEach((dlist_iter_t)begin, (dlist_iter_t)end, fp, data)); 
}
int max_reverse(const void *data1, const void *data2)
{
	if((size_t)data1 > (size_t)data2)
	{
		return(1);
	}
	return(0);
}
/* cut and paste all elements from 'src' list to 'dest' in a sorted manner */
/* if data is the same, splice after the existing one */
void SrtListMerge(srt_list_t *dest, srt_list_t *src)
{
/*	srt_list_is_before_func is_before = dest->fp1;  sorting function */
/*	*/
/*	srt_iter_t dest_where = SrtListBegin(dest);*/
/*	srt_iter_t src_begin = SrtListBegin(src);*/
/*	srt_iter_t src_curr = SrtListNext(src_begin);*/
/*	srt_iter_t src_list_end = SrtListEnd(src);*/
/*	*/
/*	while(src_begin != src_list_end)*/
/*	{*/
/*		while(!is_before(SrtListGetData(src_begin), SrtListGetData(dest_where))*/
/*		 									 && dest_where != SrtListEnd(dest))*/
/*		{*/
/*			dest_where = SrtListNext(dest_where);*/
/*		}*/
/*		while(is_before(SrtListGetData(dest_where), SrtListGetData(src_curr)))*/
/*		{*/
/*			src_curr = SrtListNext(src_curr);*/
/*		}*/
/*		src_curr = SrtListNext(src_curr);*/
/*		*/
/*		DListSplice((dlist_iter_t)dest_where, */
/*					(dlist_iter_t)src_begin, */
/*					(dlist_iter_t)src_curr);*/
/*		src_begin = src_curr;*/
/*	}*/
/*	return;*/
	srt_iter_t where = SrtListBegin(dest),
		  dest_begin = SrtListBegin(dest),
			dest_end = SrtListEnd(dest),
		   src_begin = SrtListBegin(src),
  			 src_cur = SrtListBegin(src),
  			 src_end = SrtListEnd(src);
/*  	help_t h;*/
	assert(dest);
	assert(src);

  	while(src_begin != src_end)
  	{
/*  		h.data = SrtListGetData(src_begin);*/
/*  		h.fp1 = dest->fp1;*/
  		
  		where = SrtListFind(dest, dest_begin, dest_end, SrtListGetData(src_begin));
  		where = (srt_iter_t)DListFind( (dlist_iter_t)dest_begin, 
  									   (dlist_iter_t)dest_end, 
  									   &max_reverse, 
  									   SrtListGetData(src_begin) );
  	
		while( (SrtListGetData(where) == SrtListGetData(src_cur)) && (!SrtListIsSameIter(where,dest_end)) ) 
		{
			where = SrtListNext(where);
		}	
		
/*		h.data = SrtListGetData(where);*/
/*		h.fp1 = src->fp1;*/
	
		src_cur = SrtListFind(src, src_cur, src_end, SrtListGetData(where));
		src_cur = (srt_iter_t)DListFind( (dlist_iter_t)src_cur, 
										 (dlist_iter_t)src_end, 
										  &max_reverse, 
										 SrtListGetData(where) );
		
		DListSplice((dlist_iter_t)where, 
					(dlist_iter_t)src_begin, 
					(dlist_iter_t)src_cur);
		
		src_begin = src_cur; 
	}	
	return;
}
/* cut & paste the elements in the range 'begin'-'end' to before 'where'.  */
/*   Returns an iterator to first spliced element. */
/*dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t begin, dlist_iter_t end)*/
