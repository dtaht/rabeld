#ifndef _SCHED_STUB
#define _SCHED_STUB

int sched_yield(void);

typedef unsigned int __time_t;
typedef unsigned long __syscall_slong_t ;

// Epiphany does define this and I do wish we used it
//struct timespec
//  {
//    __time_t tv_sec;            /* Seconds.  */
//    __syscall_slong_t tv_nsec;  /* Nanoseconds.  */
//  };

struct timeval
  {
    __time_t tv_sec;            /* Seconds.  */
    __syscall_slong_t tv_usec;  /* Nanoseconds.  */
  };

#endif
