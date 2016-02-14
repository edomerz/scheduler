#include "uuid.h"

static size_t c = 0;

uuid_t UuidCreate(void)
{
	uuid_t u;
	
	u.counter = ++c;
	u.pid = getpid();
	gettimeofday(&u.tval, NULL);
	
	return(u);
}

uuid_t UuidCreateNull(void)
{
	uuid_t u_null;
	
	u_null.counter = 0;
	u_null.pid = 0;
	u_null.tval.tv_sec = 0;
	u_null.tval.tv_usec = 0;
	
	return(u_null);
}

int UuidIsEqual(uuid_t u1, uuid_t u2)
{
	return((u1.counter == u2.counter) && (u1.pid == u2.pid) &&
		   (u1.tval.tv_sec == u2.tval.tv_sec) && 
		   (u1.tval.tv_usec == u2.tval.tv_usec));
}
