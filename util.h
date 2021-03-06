/*
Copyright (c) 2007, 2008 by Juliusz Chroboczek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef _BABEL_UTIL
#define _BABEL_UTIL
#include <endian.h>

#if defined(HAVE_NEON)
#ifndef HAVE_64BIT_ARCH
#define CACHELINE_ALIGN __attribute__((aligned(32)))
#else
#define CACHELINE_ALIGN __attribute__((aligned(64)))
#endif

#else
#if defined(HAVE_64BIT_ARCH)
#define CACHELINE_ALIGN __attribute__((aligned(64)))
#else
#define CACHELINE_ALIGN __attribute__((aligned(32)))
#endif
#endif

// I have no idea why these horrid macros exist but I suppose i will
// find out - unaligned access probably. Which we don't care about,
// except on mips and maybe arms. This is a single instruction...

#if 0

#define DO_NTOHS(_d, _s) (_d) = be16toh(_s)
#define DO_NTOHL(_d, _s) (_d) = be32toh(_s)
#define DO_HTONS(_d, _s) (_d) = htobe16(_s)
#define DO_HTONL(_d, _s) (_d) = htobe32(_s)

#else
#define DO_NTOHS(_d, _s) \
    do { unsigned short _dd; \
         memcpy(&(_dd), (_s), 2); \
         _d = ntohs(_dd); } while(0)
#define DO_NTOHL(_d, _s) \
    do { unsigned int _dd; \
         memcpy(&(_dd), (_s), 4); \
         _d = ntohl(_dd); } while(0)
#define DO_HTONS(_d, _s) \
    do { unsigned short _dd; \
         _dd = htons(_s); \
         memcpy((_d), &(_dd), 2); } while(0)
#define DO_HTONL(_d, _s) \
    do { unsigned _dd; \
         _dd = htonl(_s); \
         memcpy((_d), &(_dd), 4); } while(0)
#endif

static inline int
seqno_compare(unsigned short s1, unsigned short s2)
{
    if(s1 == s2)
        return 0;
    else
        return ((s2 - s1) & 0x8000) ? 1 : -1;
}

static inline short
seqno_minus(unsigned short s1, unsigned short s2)
{
    return (short)((s1 - s2) & 0xFFFF);
}

static inline unsigned short
seqno_plus(unsigned short s, int plus)
{
    return ((s + plus) & 0xFFFF);
}

/* Returns a time in microseconds on 32 bits (thus modulo 2^32,
   i.e. about 4295 seconds). */
static inline unsigned int
time_us(const struct timeval t)
{
    return (unsigned int) (t.tv_sec * 1000000 + t.tv_usec);
}

int roughly(int value);
void timeval_minus(struct timeval *d,
                   const struct timeval *s1, const struct timeval *s2);

static inline unsigned timeval_minus_msec(const struct timeval *s1, const struct timeval *s2)
    {
    if(s1->tv_sec < s2->tv_sec)
        return 0;

    /* Avoid overflow. */
    if(s1->tv_sec - s2->tv_sec > 2000000)
        return 2000000000;

    if(s1->tv_sec > s2->tv_sec)
        return
            (unsigned)((unsigned)(s1->tv_sec - s2->tv_sec) * 1000 +
                       ((int)s1->tv_usec - s2->tv_usec) / 1000);

    if(s1->tv_usec <= s2->tv_usec)
        return 0;

    return (unsigned)(s1->tv_usec - s2->tv_usec) / 1000u;

}

// The fact that after all these years I cannot tell
// the difference between true and false is mindboggling.
// In C true is represented by any numeric value not equal to 0
// and false is represented by 0. Essentially, memcmp returns
// false if two things are equal!
 
static inline int v6_equal2 (const unsigned char *p1,
                            const unsigned char *p2) {
       return memcmp(p1,p2,16) == 0;

}

static inline int v6_nequal2 (const unsigned char *p1,
                            const unsigned char *p2) {
       return memcmp(p1,p2,16) ;

}

// If I get more ambitious I'll try 128 bit xmm and neon
// I want to get away from the comparison here
// if I make this a size_t instead, what happens?

#ifndef HAVE_NEON
static inline size_t v6_nequal (const unsigned char *p1,
                                   const unsigned char *p2)
{
#ifdef  HAVE_64BIT_ARCH
        const unsigned long *up1 = (const unsigned long *)p1;
        const unsigned long *up2 = (const unsigned long *)p2;

        return ((up1[0] ^ up2[0]) | (up1[1] ^ up2[1]));
#else
        const unsigned int *up1 = (const unsigned int *)p1;
        const unsigned int *up2 = (const unsigned int *)p2;
	return ((up1[0] ^ up2[0]) |
                (up1[1] ^ up2[1]) |
                (up1[2] ^ up2[2]) |
                (up1[3] ^ up2[3]));
#endif
}
static inline size_t v6_nequal8 (const unsigned char *p1,
                                   const unsigned char *p2)
{
#ifdef  HAVE_64BIT_ARCH
        const unsigned long *up1 = (const unsigned long *)p1;
        const unsigned long *up2 = (const unsigned long *)p2;
        return (up1[0] ^ up2[0]);
#else
        const unsigned int *up1 = (const unsigned int *)p1;
        const unsigned int *up2 = (const unsigned int *)p2;
	return ((up1[0] ^ up2[0]) |
                (up1[1] ^ up2[1]));
#endif
}

// FIXME not ready yet

static inline size_t v6_nequal12 (const unsigned char *p1,
                                   const unsigned char *p2)
{
#ifdef  HAVE_64BIT_ARCH
        const unsigned long *up1 = (const unsigned long *)p1;
        const unsigned long *up2 = (const unsigned long *)p2;
        const unsigned int *ip1 = (const unsigned int *) (&p1[8]);
        const unsigned int *ip2 = (const unsigned int *)(&p2[8]);
        return ((up1[0] ^ up2[0]) | (ip1[0] ^ ip2[0]));
#else
        const unsigned int *up1 = (const unsigned int *)p1;
        const unsigned int *up2 = (const unsigned int *)p2;
	return ((up1[0] ^ up2[0]) |
                (up1[1] ^ up2[1]) |
		(up1[2] ^ up2[2]));
#endif
}
#else
#include <arm_neon.h>

// FIXME, I still don't understand this magic, nor do
// I like the name. Isn't it just returning the max value?

inline static uint32_t is_not_zero(uint32x4_t v)
{
    uint32x2_t tmp = vorr_u32(vget_low_u32(v), vget_high_u32(v));
    return vget_lane_u32(vpmax_u32(tmp, tmp), 0);
}

static inline size_t v6_nequal (const unsigned char *p1,
				const unsigned char *p2) {
	uint32x4_t up1 = vld1q_u32((const unsigned int *) p1);
        uint32x4_t up2 = vld1q_u32((const unsigned int *) p2);
	return is_not_zero(veorq_u32(up1,up2));
}
/* All these casts make my eyes bleed

static inline size_t v6_nequal8 (const unsigned char *p1,
                                   const unsigned char *p2)
{
        const uint32x2_t *up1 = vld1_u32(const unsigned int *)p1;
        const uint32x2_t *up2 = vld1_u32(const unsigned int *)p2;
	uint32x2_t tmp = veor_u32(up1,up2);
        return vget_lane_u32(vmax_u32(tmp, tmp), 0);
}

static inline size_t isnot_v4(const unsigned char* p1,
const unsigned char plen) {
        const uint32x2_t up1 = vld1_u32(const unsigned int *)p1;
        ; load zeros somehow xor xor any register
        ; xor
        unsigned int ip1 = (const unsigned int) (p1[8]);
        if(ip1 == htobe32(0xffff)) {
	          then is_not_zero for the right type
	}
        return 1;
}

*/

#endif

static inline size_t v6_equal (const unsigned char *p1,
                                   const unsigned char *p2) {
	return !v6_nequal(p1,p2);
}



void timeval_add_msec(struct timeval *d,
                      const struct timeval *s, int msecs);
int timeval_compare(const struct timeval *s1, const struct timeval *s2)
    ATTRIBUTE ((pure));
void timeval_min(struct timeval *d, const struct timeval *s);
void timeval_min_sec(struct timeval *d, time_t secs);
int parse_nat(const char *string) ATTRIBUTE ((pure));
int parse_thousands(const char *string) ATTRIBUTE ((pure));
void do_debugf(int level, const char *format, ...)
    ATTRIBUTE ((format (printf, 2, 3))) COLD;
int in_prefix(const unsigned char *restrict address,
              const unsigned char *restrict prefix, unsigned char plen)
    ATTRIBUTE ((pure));
unsigned char *normalize_prefix(unsigned char *restrict ret,
                                const unsigned char *restrict prefix,
                                unsigned char plen);
const char *format_address(const unsigned char *address);
const char *format_prefix(const unsigned char *address, unsigned char prefix);
const char *format_eui64(const unsigned char *eui);
const char *format_thousands(unsigned int value);
int parse_address(const char *address, unsigned char *addr_r, int *af_r);
int parse_net(const char *net, unsigned char *prefix_r, unsigned char *plen_r,
              int *af_r);
int parse_eui64(const char *eui, unsigned char *eui_r);
int wait_for_fd(int direction, int fd, int msecs);
int martian_prefix(const unsigned char *prefix, int plen) ATTRIBUTE ((pure));
int daemonise(void);
int set_src_prefix(unsigned char *src_addr, unsigned char *src_plen);

enum prefix_status {
    PST_EQUALS = 0,
    PST_DISJOINT,
    PST_MORE_SPECIFIC,
    PST_LESS_SPECIFIC
};

// These make sense as inlines
// is_v4mapped could be less code
// v4 = plen >= 96 && v4mapped(prefix);
// What I kind of like about this check is that
// I end up getting the prefix into reg

extern const unsigned char v4prefix[16];
extern const unsigned char llprefix[16];

static inline int
linklocal(const unsigned char *address)
{
    const unsigned short *up1 = (const unsigned short *) address;
    return up1[0] == htobe16(0xfe80); 
}

static inline int
v4mapped2(const unsigned char *address)
{
    return memcmp(address, v4prefix, 12) == 0;
}

static inline size_t
v4mapped(const unsigned char *address)
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

static inline void
v4tov6(unsigned char *dst, const unsigned char *src)
{
    memcpy(dst, v4prefix, 12);
    memcpy(dst + 12, src, 4);
}

// This less so as an inline. I'm not really sure as to th
// purpose of all these compares.

static inline enum prefix_status
prefix_cmp(const unsigned char *p1, unsigned char plen1,
           const unsigned char *p2, unsigned char plen2)
{
    int plen = MIN(plen1, plen2);

    if(v4mapped(p1) != v4mapped(p2))
        return PST_DISJOINT;

    if(memcmp(p1, p2, plen / 8) != 0)
        return PST_DISJOINT;

    if(plen % 8 != 0) {
        int i = plen / 8 + 1;
	// FIXME - does the shift differ for endianness?
        unsigned char mask = (0xFF << (plen % 8)) & 0xFF;
        if((p1[i] & mask) != (p2[i] & mask))
            return PST_DISJOINT;
    }
    // FIXME: I don't see how we ever get here. Ah:
    // fd99::1:/60
    // fd99::1:/64

    if(plen1 < plen2)
        return PST_LESS_SPECIFIC;
    else if(plen1 > plen2)
        return PST_MORE_SPECIFIC;
    else
        return PST_EQUALS;
}

/* If debugging is disabled, we want to avoid calling format_address
   for every omitted debugging message.  So debug is a macro.  But
   vararg macros are not portable. */
#if defined NO_DEBUG

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#define debugf(...) do {} while(0)
#define kdebugf(...) do {} while(0)
#elif defined __GNUC__
#define debugf(_args...) do {} while(0)
#define kdebugf(_args...) do {} while(0)
#else
static inline void debugf(const char *format, ...) { return; }
static inline void kdebugf(const char *format, ...) { return; }
#endif

#else

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#define debugf(...) \
    do { \
        if(UNLIKELY(debug >= 2)) do_debugf(2, __VA_ARGS__);     \
    } while(0)
#define kdebugf(...) \
    do { \
        if(UNLIKELY(debug >= 3)) do_debugf(3, __VA_ARGS__);     \
    } while(0)
#elif defined __GNUC__
#define debugf(_args...) \
    do { \
        if(UNLIKELY(debug >= 2)) do_debugf(2, _args);   \
    } while(0)
#define kdebugf(_args...) \
    do { \
        if(UNLIKELY(debug >= 3)) do_debugf(3, _args);   \
    } while(0)
#else
static inline void debugf(const char *format, ...) { return; }
static inline void kdebugf(const char *format, ...) { return; }
#endif

#endif

#endif

