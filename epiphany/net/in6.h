#ifndef _IN6_STUB
#define _IN6_STUB


/* Options for use with `getsockopt' and `setsockopt' at the IP level.
   The first word in the comment at the right is the data type used;
   "bool" means a boolean value stored in an `int'.  */
#define        IP_OPTIONS      4       /* ip_opts; IP per-packet options.  */
#define        IP_HDRINCL      3       /* int; Header is included with data.  */
#define        IP_TOS          1       /* int; IP type of service and precedence.  */
#define        IP_TTL          2       /* int; IP time to live.  */
#define        IP_RECVOPTS     6       /* bool; Receive all IP options w/datagram.  */
/* For BSD compatibility.  */
#define        IP_RECVRETOPTS  IP_RETOPTS       /* bool; Receive IP options for response.  */
#define        IP_RETOPTS      7       /* ip_opts; Set/get IP per-packet options.  */
#define IP_MULTICAST_IF 32      /* in_addr; set/get IP multicast i/f */
#define IP_MULTICAST_TTL 33     /* u_char; set/get IP multicast ttl */
#define IP_MULTICAST_LOOP 34    /* i_char; set/get IP multicast loopback */
#define IP_ADD_MEMBERSHIP 35    /* ip_mreq; add an IP group membership */
#define IP_DROP_MEMBERSHIP 36   /* ip_mreq; drop an IP group membership */
#define IP_UNBLOCK_SOURCE 37    /* ip_mreq_source: unblock data from source */
#define IP_BLOCK_SOURCE 38      /* ip_mreq_source: block data from source */
#define IP_ADD_SOURCE_MEMBERSHIP 39 /* ip_mreq_source: join source group */
#define IP_DROP_SOURCE_MEMBERSHIP 40 /* ip_mreq_source: leave source group */
#define IP_MSFILTER 41
# define MCAST_JOIN_GROUP 42    /* group_req: join any-source group */
# define MCAST_BLOCK_SOURCE 43  /* group_source_req: block from given group */
# define MCAST_UNBLOCK_SOURCE 44 /* group_source_req: unblock from given group*/
# define MCAST_LEAVE_GROUP 45   /* group_req: leave any-source group */
# define MCAST_JOIN_SOURCE_GROUP 46 /* group_source_req: join source-spec gr */
# define MCAST_LEAVE_SOURCE_GROUP 47 /* group_source_req: leave source-spec gr*/
# define MCAST_MSFILTER 48
# define IP_MULTICAST_ALL 49
# define IP_UNICAST_IF 50

# define MCAST_EXCLUDE   0
# define MCAST_INCLUDE   1

/* Options for use with `getsockopt' and `setsockopt' at the IPv6 level.
   The first word in the comment at the right is the data type used;
   "bool" means a boolean value stored in an `int'.  */
#define IPV6_ADDRFORM           1
#define IPV6_2292PKTINFO        2
#define IPV6_2292HOPOPTS        3
#define IPV6_2292DSTOPTS        4
#define IPV6_2292RTHDR          5
#define IPV6_2292PKTOPTIONS     6
#define IPV6_CHECKSUM           7
#define IPV6_2292HOPLIMIT       8

#define SCM_SRCRT               IPV6_RXSRCRT

#define IPV6_NEXTHOP            9
#define IPV6_AUTHHDR            10
#define IPV6_UNICAST_HOPS       16
#define IPV6_MULTICAST_IF       17
#define IPV6_MULTICAST_HOPS     18
#define IPV6_MULTICAST_LOOP     19
#define IPV6_JOIN_GROUP         20
#define IPV6_LEAVE_GROUP        21
#define IPV6_ROUTER_ALERT       22
#define IPV6_MTU_DISCOVER       23
#define IPV6_MTU                24
#define IPV6_RECVERR            25
#define IPV6_V6ONLY             26
#define IPV6_JOIN_ANYCAST       27
#define IPV6_LEAVE_ANYCAST      28
#define IPV6_IPSEC_POLICY       34
#define IPV6_XFRM_POLICY        35

/* Advanced API (RFC3542) (1).  */
#define IPV6_RECVPKTINFO        49
#define IPV6_PKTINFO            50
#define IPV6_RECVHOPLIMIT       51
#define IPV6_HOPLIMIT           52
#define IPV6_RECVHOPOPTS        53
#define IPV6_HOPOPTS            54
#define IPV6_RTHDRDSTOPTS       55
#define IPV6_RECVRTHDR          56
#define IPV6_RTHDR              57
#define IPV6_RECVDSTOPTS        58
#define IPV6_DSTOPTS            59
#define IPV6_RECVPATHMTU        60
#define IPV6_PATHMTU            61
#define IPV6_DONTFRAG           62

#define AF_UNSPEC 0

typedef unsigned char __u8;
typedef unsigned short __be16;
typedef unsigned int __be32;
typedef unsigned int __u32;
  
struct in6_addr {
	union {
		__u8		u6_addr8[16];
		__be16		u6_addr16[8];
		__be32		u6_addr32[4];
	} in6_u;
#define s6_addr			in6_u.u6_addr8
#define s6_addr16		in6_u.u6_addr16
#define s6_addr32		in6_u.u6_addr32
};

struct sockaddr_in6 {
	unsigned short int	sin6_family;    /* AF_INET6 */
	__be16			sin6_port;      /* Transport layer port # */
	__be32			sin6_flowinfo;  /* IPv6 flow information */
	struct in6_addr		sin6_addr;      /* IPv6 address */
	__u32			sin6_scope_id;  /* scope id (new in RFC2553) */
};

//struct sockaddr {
//	unsigned short int	sin_family;    /* AF_INET6 */
//	__be16			sin_port;      /* Transport layer port # */
//	__be32			sin_flowinfo;  /* IPv6 flow information */
//	struct in_addr		sin_addr;      /* IPv6 address */
//};
#endif
