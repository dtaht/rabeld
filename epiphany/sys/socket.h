#ifndef _SOCKET_STUB
#define _SOCKET_STUB
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/in6.h>

#define PF_INET 2
#define AF_INET PF_INET

#define PF_INET6 10
#define AF_INET6 PF_INET6

// FIXME (but these were "special" for the parallella

#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_UNIX 3
#define INET6_ADDRSTRLEN 16

// more stuff

/* For setsockopt(2) */
#define SOL_SOCKET      1

#define SO_DEBUG        1
#define SO_REUSEADDR    2
#define SO_TYPE         3
#define SO_ERROR        4
#define SO_DONTROUTE    5
#define SO_BROADCAST    6
#define SO_SNDBUF       7
#define SO_RCVBUF       8
#define SO_SNDBUFFORCE  32
#define SO_RCVBUFFORCE  33
#define SO_KEEPALIVE    9
#define SO_OOBINLINE    10
#define SO_NO_CHECK     11
#define SO_PRIORITY     12
#define SO_LINGER       13
#define SO_BSDCOMPAT    14
#define SO_REUSEPORT    15
#ifndef SO_PASSCRED /* powerpc only differs in these */
#define SO_PASSCRED     16
#define SO_PEERCRED     17
#define SO_RCVLOWAT     18
#define SO_SNDLOWAT     19
#define SO_RCVTIMEO     20
#define SO_SNDTIMEO     21
#endif

/* Security levels - as per NRL IPv6 - don't actually do anything */
#define SO_SECURITY_AUTHENTICATION              22
#define SO_SECURITY_ENCRYPTION_TRANSPORT        23
#define SO_SECURITY_ENCRYPTION_NETWORK          24

#define SO_BINDTODEVICE 25

/* Socket filtering */
#define SO_ATTACH_FILTER        26
#define SO_DETACH_FILTER        27
#define SO_GET_FILTER           SO_ATTACH_FILTER

#define SO_PEERNAME             28
#define SO_TIMESTAMP            29


int socket(int domain, int type, int protocol);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int shutdown(int sockfd, int how);
int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);


extern int getsockopt(int sockfd, int level, int optname,
		      void *optval, socklen_t *optlen);

extern int setsockopt(int sockfd, int level, int optname,
		      void *optval, socklen_t optlen);

struct iovec
{
        void *iov_base; /* BSD uses caddr_t (1003.1g requires void *) */
        size_t iov_len; /* Must be size_t (1003.1g) */
};


/* Structure describing messages sent by
   `sendmsg' and received by `recvmsg'.  */
struct msghdr
  {
    void *msg_name;             /* Address to send to/receive from.  */
    socklen_t msg_namelen;      /* Length of address data.  */

    struct iovec *msg_iov;      /* Vector of data to send/receive into.  */
    size_t msg_iovlen;          /* Number of elements in the vector.  */

    void *msg_control;          /* Ancillary data (eg BSD filedesc passing). */
    size_t msg_controllen;      /* Ancillary data buffer length.
                                   !! The type should be socklen_t but the
                                   definition of the kernel is incompatible
                                   with this.  */

    int msg_flags;              /* Flags on received message.  */
  };

/* Structure used for storage of ancillary data object information.  */
struct cmsghdr
  {
    size_t cmsg_len;            /* Length of data in cmsg_data plus length
                                   of cmsghdr structure.
                                   !! The type should be socklen_t but the
                                   definition of the kernel is incompatible
                                   with this.  */
    int cmsg_level;             /* Originating protocol.  */
    int cmsg_type;              /* Protocol specific type.  */
    __extension__ unsigned char __cmsg_data __flexarr; /* Ancillary data.  */
  };

struct mmsghdr
  {
    struct msghdr msg_hdr;      /* Actual message header.  */
    unsigned int msg_len;       /* Number of received or sent bytes for the
                                   entry.  */
  };

ssize_t send(int sockfd, const void *buf, size_t len, int flags);

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);

int listen(int sockfd, int backlog);

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t recvmsg(int sockfd, const struct msghdr *msg, int flags);


#endif
