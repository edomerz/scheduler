/*
	uuid
*/
#ifndef __UUID_H__
#define __UUID_H__

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

struct uuid
{
	size_t counter;
	pid_t pid;
	struct timeval tval;
}uuid;

typedef struct uuid uuid_t;

/* creates a uuid struct. return a pointer to it*/
uuid_t UuidCreate(void);

uuid_t UuidCreateNull(void);

/* check if 2 uuids are equal. returns 1 if equal, else 0*/
int UuidIsEqual(uuid_t uuid1, uuid_t uuid2);

#endif /* ifndef __UUID_H__*/
