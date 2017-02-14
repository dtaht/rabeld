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
#ifndef _BABEL_RESEND
#define _BABEL_RESEND
#define REQUEST_TIMEOUT 65000
#define RESEND_MAX 3

#define RESEND_REQUEST 1
#define RESEND_UPDATE 2

struct resend {
    unsigned char kind;
    unsigned char max;
    unsigned short delay;
    struct timeval time;
    unsigned char prefix[16];
    unsigned char plen;
    unsigned char src_prefix[16];
    unsigned char src_plen;
    unsigned short seqno;
    unsigned char id[8];
    struct interface *ifp;
    struct resend *next;
};

extern struct timeval resend_time;
extern struct resend *to_resend;

void
recompute_resend_time();

static inline int
resend_match(struct resend *resend,
             int kind, const unsigned char *prefix, unsigned char plen,
             const unsigned char *src_prefix, unsigned char src_plen)
{
    return (resend->kind == kind &&
            resend->plen == plen && memcmp(resend->prefix, prefix, 16) == 0 &&
            resend->src_plen == src_plen &&
            memcmp(resend->src_prefix, src_prefix, 16) == 0);
}


void flush_resends(struct neighbour *neigh);


static inline struct resend *
find_resend(int kind, const unsigned char *prefix, unsigned char plen,
            const unsigned char *src_prefix, unsigned char src_plen,
            struct resend **previous_return)
{
    struct resend *current, *previous;

    previous = NULL;
    current = to_resend;
    while(current) {
        if(resend_match(current, kind, prefix, plen, src_prefix, src_plen)) {
            if(previous_return)
                *previous_return = previous;
            return current;
        }
        previous = current;
        current = current->next;
    }

    return NULL;
}

static inline struct resend *
find_request(const unsigned char *prefix, unsigned char plen,
             const unsigned char *src_prefix, unsigned char src_plen,
             struct resend **previous_return)
{
    return find_resend(RESEND_REQUEST, prefix, plen, src_prefix, src_plen,
                       previous_return);
}



int record_resend(int kind, const unsigned char *prefix, unsigned char plen,
                  const unsigned char *src_prefix, unsigned char src_plen,
                  unsigned short seqno, const unsigned char *id,
                  struct interface *ifp, int delay);
static inline int
resend_expired(struct resend *resend)
{
    switch(resend->kind) {
    case RESEND_REQUEST:
        return timeval_minus_msec(&now, &resend->time) >= REQUEST_TIMEOUT;
    default:
        return resend->max <= 0;
    }
}


static inline int
unsatisfied_request(const unsigned char *prefix, unsigned char plen,
                    const unsigned char *src_prefix, unsigned char src_plen,
                    unsigned short seqno, const unsigned char *id)
{
    struct resend *request;

    request = find_request(prefix, plen, src_prefix, src_plen, NULL);
    if(request == NULL || resend_expired(request))
        return 0;

    if(memcmp(request->id, id, 8) != 0 ||
       seqno_compare(request->seqno, seqno) <= 0)
        return 1;

    return 0;
}

static inline int
satisfy_request(const unsigned char *prefix, unsigned char plen,
                const unsigned char *src_prefix, unsigned char src_plen,
                unsigned short seqno, const unsigned char *id,
                struct interface *ifp)
{
    struct resend *request, *previous;

    request = find_request(prefix, plen, src_prefix, src_plen, &previous);
    if(request == NULL)
        return 0;

    if(ifp != NULL && request->ifp != ifp)
        return 0;

    if(memcmp(request->id, id, 8) != 0 ||
       seqno_compare(request->seqno, seqno) <= 0) {
        /* We cannot remove the request, as we may be walking the list right
           now.  Mark it as expired, so that expire_resend will remove it. */
        request->max = 0;
        request->time.tv_sec = 0;
        recompute_resend_time();
        return 1;
    }

    return 0;
}


int request_redundant(struct interface *ifp,
                      const unsigned char *prefix, unsigned char plen,
                      const unsigned char *src_prefix, unsigned char src_plen,
                      unsigned short seqno, const unsigned char *id);

void expire_resend(void);
void recompute_resend_time(void);
void do_resend(void);
#endif
