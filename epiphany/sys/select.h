#ifndef _SELECT_STUB
#define _SELECT_STUB
#include <netinet/in.h>
#include <net/in6.h>

// FIXME

int select(int nfds, fd_set *readfds, fd_set *writefds,
		  fd_set *exceptfds, struct timeval *timeout);


#endif
