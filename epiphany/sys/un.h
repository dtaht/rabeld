#ifndef _UNSTUB
#define _UN_STUB
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/in6.h>
#define AF_UNIX 3
#define PF_UNIX 3
typedef sin6_addr sockaddr_un;
#endif
