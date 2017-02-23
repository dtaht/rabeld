#ifndef _INET_STUB
#define _INET_STUB

// FIXME ENDIAN

#define ntohl(a) a

typedef long unsigned int socklen_t;

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
const char *inet_pton(int af, const char *src, void *dst);
#endif
