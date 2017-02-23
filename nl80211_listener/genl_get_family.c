
/*
 * The olsr.org Optimized Link-State Routing daemon version 2 (olsrd2)
 * Copyright (c) 2004-2015, the olsr.org team - see HISTORY file
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of olsr.org, olsrd nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Visit http://www.olsr.org for more information.
 *
 * If you find this software useful feel free to make a donation
 * to the project. For more information see the website or contact
 * the copyright holders.
 *
 */

/**
 * @file
 */

/*
 * Much of the code of this file originally came from the iw userspace
 * command source code and was adapted for OLSRv2.
 *
 * Copyright (c) 2007, 2008 Johannes Berg
 * Copyright (c) 2007    Andy Lutomirski
 * Copyright (c) 2007    Mike Kershaw
 * Copyright (c) 2008-2009   Luis R. Rodriguez
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define _GNU_SOURCE

/* must be first because of a problem with linux/netlink.h */
#include <sys/socket.h>

/* and now the rest of the includes */
#include <linux/types.h>
#include <linux/netlink.h>
#include <linux/genetlink.h>
#include "nl80211.h"
#include <netlink/attr.h>
#include <netlink/msg.h>
#include <netlink/genl/genl.h>

#include "common/common_types.h"
#include "subsystems/os_system.h"

#include "nl80211_listener/nl80211_internal.h"
#include "nl80211_listener/nl80211_listener.h"
#include "nl80211_listener/genl_get_family.h"

/**
 * Send a netlink message to get the nl80211 id and multicast group
 * @param nl_msg netlink message
 * @param hdr generic netlink message header
 */
void
genl_send_get_family(struct nlmsghdr *nl_msg, struct genlmsghdr *hdr) {
  hdr->cmd = CTRL_CMD_GETFAMILY;
  hdr->version = 1;

  nl_msg->nlmsg_flags |= NLM_F_DUMP;
}

/**
 * Process CTRL_CMD_NEWFAMILY message
 * @param hdr pointer to netlink message header
 * @param nl80211_id pointer to nl80211 id, will be overwritten by function
 * @param nl80211_mc pointer to nl80211 multicast group, will be overwritten by function
 */
void
genl_process_get_family_result(struct nlmsghdr *hdr, uint32_t *nl80211_id, uint32_t *nl80211_mc) {
  static struct nla_policy ctrl_policy[CTRL_ATTR_MAX+1] = {
    [CTRL_ATTR_FAMILY_ID]    = { .type = NLA_U16 },
    [CTRL_ATTR_FAMILY_NAME]  = { .type = NLA_STRING, .maxlen = GENL_NAMSIZ },
    [CTRL_ATTR_VERSION]      = { .type = NLA_U32 },
    [CTRL_ATTR_HDRSIZE]      = { .type = NLA_U32 },
    [CTRL_ATTR_MAXATTR]      = { .type = NLA_U32 },
    [CTRL_ATTR_OPS]          = { .type = NLA_NESTED },
    [CTRL_ATTR_MCAST_GROUPS] = { .type = NLA_NESTED },
  };
  struct nlattr *attrs[CTRL_ATTR_MAX+1];
  struct nlattr *mcgrp;
  int iterator;

  if (nlmsg_parse(hdr, sizeof(struct genlmsghdr),
      attrs, CTRL_ATTR_MAX, ctrl_policy) < 0) {
    OONF_WARN(LOG_NL80211, "Cannot parse netlink CTRL_CMD_NEWFAMILY message");
    return;
  }

  if (attrs[CTRL_ATTR_FAMILY_ID] == NULL) {
    OONF_WARN(LOG_NL80211, "Missing Family ID in CTRL_CMD_NEWFAMILY");
    return;
  }
  if (attrs[CTRL_ATTR_FAMILY_NAME] == NULL) {
    OONF_WARN(LOG_NL80211, "Missing Family Name in CTRL_CMD_NEWFAMILY");
    return;
  }

  OONF_DEBUG(LOG_NL80211, "Found Netlink family '%s'\n",
      nla_get_string(attrs[CTRL_ATTR_FAMILY_NAME]));

  if (strcmp(nla_get_string(attrs[CTRL_ATTR_FAMILY_NAME]), "nl80211") != 0) {
    /* not interested in this one */
    return;
  }

  *nl80211_id = nla_get_u16(attrs[CTRL_ATTR_FAMILY_ID]);
  OONF_DEBUG(LOG_NL80211, "Received nl80211 family id: %d\n", *nl80211_id);

  if (*nl80211_mc || !attrs[CTRL_ATTR_MCAST_GROUPS]) {
    /* no multicast groups */
    return;
  }

  nla_for_each_nested(mcgrp, attrs[CTRL_ATTR_MCAST_GROUPS], iterator) {
    struct nlattr *tb_mcgrp[CTRL_ATTR_MCAST_GRP_MAX + 1];
    uint32_t group;

    nla_parse(tb_mcgrp, CTRL_ATTR_MCAST_GRP_MAX,
        nla_data(mcgrp), nla_len(mcgrp), NULL);

    if (!tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME] ||
        !tb_mcgrp[CTRL_ATTR_MCAST_GRP_ID])
      continue;

    group = nla_get_u32(tb_mcgrp[CTRL_ATTR_MCAST_GRP_ID]);
    OONF_DEBUG(LOG_NL80211, "Found multicast group %s: %d",
        (char *)nla_data(tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME]),
        group);

    if (strcmp(nla_data(tb_mcgrp[CTRL_ATTR_MCAST_GRP_NAME]), "mlme"))
      continue;

    *nl80211_mc = group;
  }
}

#if 0
    if (os_system_netlink_add_mc(&netlink_handler, &group, 1)) {
      OONF_WARN(LOG_NL80211,
          "Could not activate multicast group %d for nl80211", group);
    }
    else {
    }
    break;
  }
}

#endif
