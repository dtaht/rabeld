#ifndef _IFADDRS_STUB
#define _IFADDRS_STUB
// Might as well stick this here
typedef int sig_atomic_t;

// this is not in newlib - I'd had fun with it renaming it to core-X

int gethostname(char *name, size_t len);
#endif
