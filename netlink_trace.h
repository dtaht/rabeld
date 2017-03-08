/**
 * netlink_trace.h
 */

#ifndef NETLINK_TRACE_H
#define NETLINK_TRACE_H

#ifdef NETLINK_TRACE

extern FILE *iproutefd;

extern int replay_iproute_status(int rc, int errv);
int replay_iproute(int operation, const unsigned char *src,
	           const unsigned char *dest,
 		   unsigned char src_plen, unsigned char dest_plen,
		   const unsigned char *gate,	int table, int metric, int ifindex,
 		   const unsigned char *newgate, int newtable, int newmetric, int newifindex)

#else
static inline int replay_iproute_status(int rc, int errv) { return 0; }

static inline int replay_iproute(int operation, const unsigned char *src, const unsigned char *dest,
 		   const unsigned char src_plen, const unsigned char dest_plen,
		   const unsigned char *gate,	int table, int metric, int ifindex,
		const unsigned char *newgate, int newtable, int newmetric, int newifindex) {
   	return 0;
}

#endif
#endif
