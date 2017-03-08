/**
 * netlink_trace.c
 *
 */

#include "netlink_trace.h"

#ifdef NETLINK_TRACE
FILE *iproutefd = NULL;

// Now is global. We don't need to get or format it every time
// and we're trying to recreate hairy race conditions here.
// Hmm. I wonder if we could do multipath with a /whatever on the newgate

int replay_iproute(int operation, const unsigned char *src,
	           const unsigned char *dest,
 		   unsigned char src_plen, unsigned char dest_plen,
		   const unsigned char *gate,	int table, int metric, int ifindex,
 		   const unsigned char *newgate, int newtable, int newmetric, int newifindex)
{
	static struct timeval mynow;
	static int err = 0;
	static char buf[64];

	if(err != 0) return -1; // Don't try to reopen the file
	if(iproutefd == NULL) {
		iproutefd = fopen("/tmp/babel_replay.log","w");
      		if(iproutefd == NULL) { err++; return -1; }
	}
	if(timeval_compare(&mynow, &now) != 0) {
		mynow = now;
		snprintf(buf, sizeof buf, "%ld.%.6ld", mynow.tv_sec, mynow.tv_usec);
// arguably human readable would be easier on me
//		strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", mynow.tv_sec);
//              snprintf(buf, sizeof buf, "%s.%06ld", tmbuf, mynow.tv_usec);
	}
	char ifname[256];
	if(v4mapped(dest) && dest_plen > 96) {
	fprintf(iproutefd, "%s : ip route %s %s "
            "table %d metric %d dev %s via %s",
	    buf,
            operation == ROUTE_ADD ? "add" :
            operation == ROUTE_FLUSH ? "flush" :
	    operation == ROUTE_MODIFY ? "replace" : "???",
            format_prefix(dest, dest_plen),
		table, metric, if_indextoname(ifindex,ifname), format_address(gate));
	} else {
	fprintf(iproutefd, "%s : ip route %s %s from %s "
            "table %d metric %d dev %s via %s",
	    buf,
            operation == ROUTE_ADD ? "add" :
            operation == ROUTE_FLUSH ? "flush" :
	    operation == ROUTE_MODIFY ? "replace" : "???",
            format_prefix(dest, dest_plen), format_prefix(src, src_plen),
		table, metric, if_indextoname(ifindex,ifname), format_address(gate));
	}
	return 0;

}

int replay_iproute_status(int rc, int errv) {
	static int err = 0;
	int errno_safe = errno;
	if(err != 0) return -1; // Don't try to reopen the file
	if(iproutefd == NULL) {
		iproutefd = fopen("/tmp/babel_replay.log","w");
      		if(iproutefd == NULL) { err++; return -1; }
	}
	if(errno == 0) {
		fprintf(iproutefd, " # OK\n");
	} else {
		fprintf(iproutefd, " # rc=%d errno=%d\n", rc, errv);
	}
        errno = errno_safe;
	return rc;
}

#endif
