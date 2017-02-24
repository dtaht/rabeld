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
#ifndef _BABEL_CONFIGURATION
#define _BABEL_CONFIGURATION
/* Values returned by parse_config_from_string. */

#define CONFIG_ACTION_DONE 0
#define CONFIG_ACTION_QUIT 1
#define CONFIG_ACTION_DUMP 2
#define CONFIG_ACTION_MONITOR 3
#define CONFIG_ACTION_UNMONITOR 4
#define CONFIG_ACTION_NO 5
#define CONFIG_ACTION_DUMP_NEIGHBOURS 6
#define CONFIG_ACTION_DUMP_ROUTES 7
#define CONFIG_ACTION_DUMP_INTERFACES 8
#define CONFIG_ACTION_DUMP_ME 9

struct filter_result {
    unsigned char *src_prefix;
    unsigned int add_metric; /* allow = 0, deny = INF, metric = <0..INF> */
    unsigned int table;
    unsigned char src_plen;
    unsigned char pad[3];
};

struct filter {
    char *ifname;
    int af;
    unsigned int ifindex;
    unsigned char *id;
    unsigned char *prefix;
    unsigned char *src_prefix;
    unsigned char plen;
    unsigned char plen_ge, plen_le;
    unsigned char src_plen;
    unsigned char src_plen_ge, src_plen_le;
    /* two byte hole */
    int proto;                  /* May be negative */
    unsigned char *neigh;
    struct filter *next;
    struct filter_result action;
} CACHEALIGN;

extern struct interface_conf *default_interface_conf;

void flush_ifconf(struct interface_conf *if_conf);

int parse_config_from_file(const char *filename, int *line_return);
int parse_config_from_string(char *string, int n, const char **message_return);
void renumber_filters(void);

int input_filter(const unsigned char *id,
                 const unsigned char *prefix, unsigned short plen,
                 const unsigned char *src_prefix, unsigned short src_plen,
                 const unsigned char *neigh, unsigned int ifindex);
int output_filter(const unsigned char *id,
                  const unsigned char *prefix, unsigned short plen,
                  const unsigned char *src_prefix, unsigned short src_plen,
                  unsigned int ifindex);
int redistribute_filter(const unsigned char *prefix, unsigned short plen,
                    const unsigned char *src_prefix, unsigned short src_plen,
                    unsigned int ifindex, int proto,
                    struct filter_result *result);
int install_filter(const unsigned char *prefix, unsigned short plen,
                   const unsigned char *src_prefix, unsigned short src_plen,
                   struct filter_result *result);
int finalise_config(void);
#endif
