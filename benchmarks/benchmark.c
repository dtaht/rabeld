/**
 * benchmark.c
 * Some tests for correctness and speed for ipv6 prefix comparisons
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <rand.h>
#include <memory.h>
#include <endian.h>
#include <arpa/inet.h>
#ifdef HAVE_NEON
#include <arm_neon.h>
inline static uint32_t is_not_zero(uint32x4_t v)
{
    uint32x2_t tmp = vorr_u32(vget_low_u32(v), vget_high_u32(v));
    return vget_lane_u32(vpmax_u32(tmp, tmp), 0);
}
#endif

#define MAX_PREFIX 1024

typedef struct {
	unsigned char prefix[16];
	unsigned char plen;
} prefix_table; // Fixme, try aligned and unaligned


// Memcmp returns -1,0,1. 0 for equality

static inline int v6_equal (const unsigned char *p1,
                            const unsigned char *p2) {
       return memcmp(p1,p2,16) == 0;

}

// If I get more ambitious I'll try 128 bit xmm and neon
// What I think I want to do is use NOTEQUAL!

static inline int v6_equal2 (const unsigned char *p1,
                                   const unsigned char *p2)
{
#ifdef  HAVE_64BIT_ARCH
        const unsigned long *up1 = (const unsigned long *)p1;
        const unsigned long *up2 = (const unsigned long *)p2;

        return !((up1[0] ^ up2[0]) | (up1[1] ^ up2[1]));
#else
#ifdef  HAVE_NEON
	uint32x4_t up1 = vld1q_u32((const unsigned int *) p1);
        uint32x4_t up2 = vld1q_u32((const unsigned int *) p2);
	return !is_not_zero(veorq_u32(up1,up2));
#else
        const unsigned int *up1 = (const unsigned int *)p1;
        const unsigned int *up2 = (const unsigned int *)p2;
	return !((up1[0] ^ up2[0]) |
                (up1[1] ^ up2[1]) |
                (up1[2] ^ up2[2]) |
                (up1[3] ^ up2[3]));
#endif
#endif
}

static inline int v6_equal8 (const unsigned char *p1,
                                   const unsigned char *p2)
{
#ifdef  HAVE_64BIT_ARCH
        const unsigned long *up1 = (const unsigned long *)p1;
        const unsigned long *up2 = (const unsigned long *)p2;
        return (up1[0] ^ up2[0]) == 0UL;
#else
        const unsigned int *up1 = (const unsigned int *)p1;
        const unsigned int *up2 = (const unsigned int *)p2;
	return ((up1[0] ^ up2[0]) |
                (up1[1] ^ up2[1]))  == 0;
#endif
}

static inline int v6_equal12 (const unsigned char *p1,
                                   const unsigned char *p2)
{
#ifdef  HAVE_64BIT_ARCH2
        const unsigned long *up1 = (const unsigned long *)p1;
        const unsigned long *up2 = (const unsigned long *)p2;
        const unsigned int *ip1 = (const unsigned int *) (&p1[8]);
        const unsigned int *ip2 = (const unsigned int *)(&p2[8]);
        return ((up1[0] ^ up2[0]) | (ip1[0] ^ ip2[0])) == 0UL;
#else
        const unsigned int *up1 = (const unsigned int *)p1;
        const unsigned int *up2 = (const unsigned int *)p2;
	return ((up1[0] ^ up2[0]) |
                (up1[1] ^ up2[1]) |
		(up1[2] ^ up2[2]))  == 0;
#endif
}

// These make sense as inlines but we want to fool the compiler

extern const unsigned char v4prefix[16];
extern const unsigned char llprefix[16];

static inline int
linklocal(const unsigned char *address)
{
    const unsigned short *up1 = (const unsigned short *) address;
    return up1[0] == htobe16(0xfe80);
}

static inline int
v4mapped(const unsigned char *address)
{
    return memcmp(address, v4prefix, 12) == 0;
}

static inline int
v4mapped2(const unsigned char *address)
{
#ifdef  HAVE_64BIT_ARCH
    const unsigned long *up1 = (const unsigned long *) address;
    const unsigned int *up2 = (const unsigned int *) (&address[8]);
    // Fixme Address extend?
    return ((up1[0] ^ 0) | (up2[0] ^ htobe32(0xffff))) == 0UL;
#else
    const unsigned int *up1 = (const unsigned int *) address;
    return ((up1[0] ^ 0) | (up1[1] ^ 0) | (up1[2] ^ htobe32(0xffff))) == 0;
#endif
}

// If you call this from a thread the result will be even more random
// if you aren't using __thread! Which is kind of ok, but..
// C11 defines _Thread_local. Linux __thread;

unsigned char *random_prefix() {
	static __thread unsigned int a[4] = {0};
	a[0] = random();
	a[1] = random();
	a[2] = random();
	a[3] = random();
	return (unsigned char *) a;
}

// I can imagine this also blowing up on people without the __thread

const char *
format_prefix(const unsigned char *prefix, unsigned char plen)
{
    static __thread char buf[4][INET6_ADDRSTRLEN + 4] = {0};
    static __thread int i = 0;
    int n;
    i = (i + 1) % 4; // WTF in a 64 bit arch? Let you call this 4 times?
    if(plen >= 96 && v4mapped(prefix)) {
        inet_ntop(AF_INET, prefix + 12, buf[i], INET6_ADDRSTRLEN);
        n = strlen(buf[i]);
        snprintf(buf[i] + n, INET6_ADDRSTRLEN + 4 - n, "/%d", plen - 96);
    } else {
        inet_ntop(AF_INET6, prefix, buf[i], INET6_ADDRSTRLEN);
        n = strlen(buf[i]);
        snprintf(buf[i] + n, INET6_ADDRSTRLEN + 4 - n, "/%d", plen);
    }
    return buf[i];
}

const char *
format_prefix2(const unsigned char *prefix, unsigned char plen)
{
    static __thread char buf[4][INET6_ADDRSTRLEN + 4];
    static __thread int i = 0;
    int n;
    i = (i + 1) % 4;
    if(plen >= 96 && v4mapped2(prefix)) {
        inet_ntop(AF_INET, prefix + 12, buf[i], INET6_ADDRSTRLEN);
        n = strlen(buf[i]);
        snprintf(buf[i] + n, INET6_ADDRSTRLEN + 4 - n, "/%d", plen - 96);
    } else {
        inet_ntop(AF_INET6, prefix, buf[i], INET6_ADDRSTRLEN);
        n = strlen(buf[i]);
        snprintf(buf[i] + n, INET6_ADDRSTRLEN + 4 - n, "/%d", plen);
    }
    return buf[i];
}


int main() {
	int count = 0;
	int count2 = 0;
	int i = 0;
	int err = 0;
	prefix_table *p = calloc(MAX_PREFIX,16);
	for(int i = 0; i<MAX_PREFIX; i++) {
		memcpy(p[i].prefix,random_prefix(),16);
	}
	// Give us two exact hits

	memcpy(p[MAX_PREFIX/2].prefix,llprefix,16);
	memcpy(p[MAX_PREFIX/3].prefix,v4prefix,16);

	// Check to see if we are formatting prefixes correctly
	// Heh. I just learned something - if we call format_prefix twice, we might overwrite stuff
        // And that could be what I'm doing wrong in all those debug statements
        // and format_prefix seems to buffer 4 times so you can call it 4 times!
	// clever. But a little scary....

	printf("v4mapped print %s, ll print %s\n",format_prefix(p[MAX_PREFIX/2].prefix,
								p[MAX_PREFIX/2].plen),
						format_prefix(p[MAX_PREFIX/3].prefix,
							p[MAX_PREFIX/3].plen));
	printf("v4mapped2 print %s, ll print %s\n",format_prefix2(p[MAX_PREFIX/2].prefix,
								p[MAX_PREFIX/2].plen),
						format_prefix2(p[MAX_PREFIX/3].prefix,
							p[MAX_PREFIX/3].plen));
	count = 0;
	for(i = 0; i<MAX_PREFIX; i++) {
		if(v4mapped(p[i].prefix)) count++;
	}
	printf("v4mapped: %d\n",count);
	count2 = 0;
	for(i = 0; i<MAX_PREFIX; i++) {
		if(v4mapped2(p[i].prefix)) count2++;
	}
	printf("v4mapped2: %d\n",count);
	printf("v4mapped and v4mapped2 are %s\n", count == count2 ? "equal" : "not equal" );
	if(count != count2) err++;

	count = 0;
	for(i = 0; i<MAX_PREFIX; i++) {
		if(v6_equal(llprefix,p[i].prefix)) count++;
	}
	for(i = 0; i<MAX_PREFIX; i++) {
		if(v6_equal(v4prefix,p[i].prefix)) count++;
	}
	printf("v6_equal: %d\n",count);

	count2 = 0;
	for(i = 0; i<MAX_PREFIX; i++) {
		if(v6_equal2(llprefix,p[i].prefix)) count2++;
	}
	for(i = 0; i<MAX_PREFIX; i++) {
		if(v6_equal2(v4prefix,p[i].prefix)) count2++;
	}
	printf("v6_equal2: %d\n",count);
	printf("v6_equal and v6_equal2 are %s\n", count == count2 ? "equal" : "not equal" );
	if(count != count2) err++;
	printf("Total errors: %d\n", err);
	return(err);
}

/* Fun notes:

As of this commit, I must be smashing the stack, which is not something I can detect!!!

d@dancer:~/git/rabeld/benchmarks$ ./bench_Os
v4mapped: 1
v4mapped2: 1
v4mapped and v4mapped2 are equal
v6_equal: 2046
v6_equal2: 2046
v6_equal and v6_equal2 are not equal
Total errors: 1

*/
