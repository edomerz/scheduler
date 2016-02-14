#ifndef __SRT_LIST_H__
#define __SRT_LIST_H__

#include <stdio.h>

typedef struct srt_list_adt srt_list_t;
typedef struct srt_list_node *srt_iter_t;

/* perform an operation on 'element'. */
typedef int (*srt_list_action_func)(void *element, void *param);

/* pointer to function that return 1 if data1 preceeds data2 */
typedef int (*srt_list_is_before_func)(const void *data1, const void *data2);


/* creates a list */
srt_list_t *SrtListCreate(srt_list_is_before_func fp);

/* destroys a list */
void SrtListDestroy(srt_list_t *list);

/* returns number of elements in list */
size_t SrtListSize(const srt_list_t *list);

/* returns 1 if 'list' is empty, else 0 */
int SrtListIsEmpty(const srt_list_t *list);

/* returns iterator to first/last element of list */
srt_iter_t SrtListBegin(const srt_list_t *list);
srt_iter_t SrtListEnd(const srt_list_t *list);

/* returns iterators to next/previous element of 'iter' */
srt_iter_t SrtListNext(const srt_iter_t iter);
srt_iter_t SrtListPrev(const srt_iter_t iter);

/* checks if 2 iterator point to same element. returns 1 if true, else 0 */
int SrtListIsSameIter(const srt_iter_t iter1, const srt_iter_t iter2);

/* returns data of 'iter' */
void *SrtListGetData(srt_iter_t iter);

/* inserts a new element in a sorted manner, assign it with 'data' and 
   return iterator to it */
srt_iter_t SrtListInsert(srt_list_t *list, void *data);

/* remove element pointed by iterator, returns iterator to next element */
srt_iter_t SrtListRemove(srt_iter_t iter);

/* removes first/last element of list, and returns it's data */
void *SrtListPopFront(srt_list_t *list);
void *SrtListPopBack(srt_list_t *list);

/* from the range 'begin' to 'end', return the first element containing 'data'.
   return 'end' if not found */
srt_iter_t SrtListFind(const srt_list_t *list, srt_iter_t begin, srt_iter_t end, const void *data);

/* send each element in range: 'begin'-'end' to function fp, or until fp failes (excluding 'end')  */
/* according to action_func. returns exit status upon failure, 0 otherwise          */
int SrtListForeach(srt_iter_t begin, srt_iter_t end, srt_list_action_func fp, void *data);

/* cut and paste all elements from 'src' list to 'dest' in a sorted manner */
void SrtListMerge(srt_list_t *dest, srt_list_t *src);

#endif /* ifndef __SRT_LIST_H__ */
