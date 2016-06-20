# Rapid Babel (RABEL) - Babel Protocol Network Extensions for Rapid Convergence

This document describes some potential optimizations for the the babel
protocol specification and implementation, with pointers to real world
problems. While it first deals with multicast/unicast issues, it later goes
into other problems induced by wireless transports, and is by no means
definitive.

The overall intent of this document is to improve babel to work faster
and integrate better over more layer 2 transports (802.11a[c,x,d],
802.11n fiber, ethernet, usbnet, tunnels, powerline), and scale
to larger numbers of interoperable nodes and networks.

## The case for minimizing multicast

The use of multicast packets for measuring packet loss as a metric is of
minimal usefulness, and will become less so if/when multicast-spoofing
techniques become more common in the wild.

In wifi, unicast paths run at much higher rates than multicast ones - in
the case of 802.11ac, as much as 1000 times higher. Wifi networks are
also frequently bridged to wired networks, with an even worse
performance disparity between unicast and multicast.

Calculated one way (as a fraction of the total bandwidth available), as
a 300Mbit capable link with a 6mbit multicast rate, it would be faster
to send unicast to 50 stations than it would be to use multicast.

The wifi world, however, has variable rates and fixed length minimum
txops and a RABEL daemon MAY chose to change to revert to multicast
announcements and transfers when sufficient listeners on a link exist.
The suggested number for wireless-g is 4, wireless-n is 12. Most links
are considerably "sparser" than that.

On active wifi links, the added cost of carrying routing traffic via unicast
is nearly "free".

Multicast hello and a unicast IHU does have the advantage of testing
both kinds of path simultaneously.

Aside from hellos and some acknowledgements, it is possible for a babel
compliant daemon to use unicast almost entirely, at a substantial
improvement in route propagation and reliability, for less cost

(the range of possibilities for a unicast hello extension is covered in
a different document)

Receiving unicast on inactive links this causes battery life and costs a TXOP.
However, sleepy nodes SHOULD send their hellos and IHUs with a longer
request for wakeups in the first place.

## Unicast IHU

Is already added in this repo and works transparently with the default babel daemons.

## Unicast routing table updates

Universal (instead of triggered) unicast routing table updates would be
*much faster* and more reliable if sent more exclusively over unicast,
subject to the total number of stations paying attention.

This is already supported in principle by the existing codebase.

## Applying unicast for routing table updates

Propagating the routes over a less lossy link leads to stable routes
being available to all routers, making a route switch in the case of
failure faster and simpler.

We have been observing a bad behavior with multicast routing table
update in the first place, being lost to many devices, which in the end
triggers a unicast route exchange, anyway.

## Advantages to more unicast

Actual unicast traffic keeps updating the wifi rate control statistics,
multicast bypasses that, and leads to invalid rate statistics when the
link actually is used.

Additional advantages include

* Improve the reliable transfer of routing information
* Decrease the amount of multicast traversing switches with sparse babel speakers
* Improve the performance on wireless p2p links

## Disadvantages to more unicast

* More CPU and bandwidth overhead from the sending station
* Additional code complexity
* head of line blocking for routing updates that previously were
  received and processed in parallel.

# Other new features for more rapid, reliable routing

Everything described thus far can be implemented. Addition of the
Unicast Hello option is not required for much of the potential benefit.

If I had any one goal here it would be to reduce the time to detect a
failed link to below a typical TCP RTO (250-1sec). Being down for longer than
that causes more traffic. Other goals (not necessarily with babel), would
be to have an IGP with enough of the same characteristics of BGP to
scale to city-wide networks.

# Accellerated link recovery and monitoring

Certain kinds of links tend to flap once and resume in a matter of
milliseconds (ethernet, usbnet). Wifi tends to go down for 10s or 100s
of milliseconds. Less conservative approaches to thinking a link stable
or unstable might be good, especially when there was a total loss of
connectivity being recovered from in the first place.

## Soft accellerated loss detection optimization

If a IHU packet is not received within the designated interval, the
next and 2 remaining hello packets are sent out at 1/4th, 1/8th and
1/16 the default interval with a maximum delay of 250ms, after which
point the link should be decided as down.

At the default hello interval of 4 seconds, this would be 1,1.5,and 1.75
seconds, resulting in a link down notification in 8 seconds rather than
16.

Alternatively the IHU delay minimum could be calculated as the weighted
average of recent RTTS * 4, and fall back to that - one loss, 3 ever
more rapid probes. This would treat "failure to respond rapidly enough"
essentially the same as loss, and be more sensitive to channel scans and
interference, and congestion.

As a reasonable tradeoff between compute and traffic, the default
minimum possible update rate can be as low as 10ms.

After link recovery hello/IHU intervals should start short and rapidly
scale up in the inverse of the above.

## Decrease the default hello interval for wired and wifi links.

Other DV protocols (e.g. bmx6) are using a hello interval of 500ms. See
above for how to reduce typical failover to under 1sec.

Exceptionally slow (e.g. 2.4ghz wifi)links should retain the default 4 second
interval.

## ND triggering

It is envisioned that RA/ND, now a problem in wifi, will be optimized out
of upcoming wifi layers. At the same time ND provides an ongoing useful
test of the multicast capability of the link independent of babel, so
that basic connectivity is managed that way. Babel's current
use of multicast is redundant where ND can take over.

## ICMP host unreachable

Use of unicast may result in icmp host unreachable long before babel's
normal loss detection methods can kick in. Rabel should respond and act
appropriately on icmp host unreachable.

## BFD

Modern wired networks have
[Bidirectional Forward Detection](https://en.wikipedia.org/wiki/Bidirectional_Forwarding_Detection)
. Alerting Rabel to to these, where exposed by the switching
infrastructure, would be a goodness.

There are also other means of detecting a link down or up (in wifi AP/STA mode,
disassociation, a variety of means in tunnels and ethernet) that are faster than
babel's usual basic metrics.

## Atomic updates

The present delete/add system for updating routes causes packet loss and
icmp unreachable messages. Better kernel support for updating routes
appears to be needed.

## Gentle Route switching

The native optimization properties of the default algorithm mean that
"optimal" routes are gradually switched to, over the period of minutes.

Continuing to maintain more casual routing arrangements for two or more
routes of roughly equal cost, and observing the effect of a route change
over time, rather than selecting the single best one,
might result in better routing.

## Casual multipath and NECMP (nearly equal cost multipath)

When two routes of "equal" goodness arise, babel currently choses the most
stable of the two routes to hold onto, rather than selecting two or more.

Selecting different routes for paths that might have otherwise converged
to one route might lead to a significant performance enhancement.

Other costs (such as diversity routing) may mean that two paths may never
become equal.

# PIM

Oh, god. Why does this still matter to anyone?

## TCP-friendly Rate Sensitive Route Flooding

The existing fixed rate limiter was originally designed for slow route
propagation over very slow network. It was put in place to handle
accidentally dumping an entire bgp route table into the previously
unlimited system.

The default rate is eons too slow for a 1 or 10Gbit network, and arguably too
slow for most purposes. It also essentially does "pacing" where the
right thing for wifi is more of a burst of packets that will fit into a txop.

Choosing a rate more suited and dynamically adapting to the available
network capacity would be good.

## Reducing the self induced jitter and delay

The current behavior of babel is based on the analysis of RIP back in
1993, where it was proven (on the networks of the day) that ultimately
a network would self-synchronize. ( http://ee.lbl.gov/papers/sync_94.pdf )

However, this assertion as unproven on modern networks. Repeating the
simulation studies done in that paper adding back in the native layer 2
behaviors of current networks would be a goodness.

Also multiple alternatives to inducing enough jitter exist. One example
from that paper:

"A second method for avoiding synchronization is to implement a routing
timer that is indepen- dent of external events (as mentioned in the
specifications for RIP) [ He88 , p.23]. If each router resets its timer
immediately after the timer expires (regardless of its activities when
the timer expires) and if routers don’ t reset their timers after
triggered updates, then the process of timer synchronization described
in this paper might be avoided. There are, however , drawbacks to this
approach: if routers are initially synchronized (either by chance, or
because they were restarted at the same time) then they will remain
synchronized since there is no mechanism to break up synchronization if
it does occur". .

The native characteristics of most busy networks today can induce (almost?)
sufficient delay and jitter to compensate. And: On idle networks self sync
does not matter as much, and can be periodically broken up when noticed.

Wifi is subject to native jitter and delay measured in the 100s of
microseconds, and multicast traffic in particular can be delayed by the
access point by 250ms or more.

Thus, the self induced jitter in babel can be reduced, especially in the case
of wifi, in favor of leveraging natural effects.

The second desirable behavior of the self induced jitter allows for more
route infomation to be accumulated into a single packet.

Rather than randomly inducing a fixed peak amount of jitter, a jitter
interval based on the RTT timestamps of received packets could be
calculated to optimize for reception and packing.

## Scheduled downtime notifications and fast switchback

A given link (in wifi) might take a "time out" to do a channel scan. It
may only be briefly down, and a protocol could notify others that it was
going down very temporarily and (if possible) and re-route, otherwise
hold.

As opposed to a classic route retraction, this would be a "route hold" message
where again, packets could be buffered briefly until the device is back
again.

The pluggable packet scheduler availabe in linux might be something that
could be leveraged.

The need for layer 2 to temporarily buffer (channel scan) or delay
packets (powersave) is now baked into multiple IEEE standards, but not
propigated to layer 3 in any way that is currently useful, enhancements
to APIs and sensing such events is presently out of scope for this
document (but see 6tich)

## Fast channel switch

Layer 2 wireless technologies and sensing are capable of switching
channels in under 20ms.

In particular, modern wifi implementations with DFS are *required* to do
a fast channel switch.

The impact of channel switching like this needs to be polled for, and
managed for a routing protocol at layer 3.

As a channel switch presumably uses some better metric for quality than
a layer 3 protocol can achieve, noting a channel switch and more rapidly
adopting a good metric might be useful.

## ECN support

Particularly with more unicast over wifi, packet loss becomes a very
poor metric of link quality - either you get the packet, with potentially
tons of delay, or you don't.

It seemed extremely unlikely, except on extremely overburdened networks,
that ect(3) will be asserted. However in an age where packet loss is
increasingly rare, one test showed 30% of ECN marked babel packets being
ECT(3) marked by a fq_codel based congestion controller.

Upon reception of an ect(3) marked packet, a babel instance MUST

* Increase the rxcost
* send a IHU (or other acknowledgement?) marked with ect(3), with an
  increased hello interval (if present interval is below the default)
* reduce it's sending rate by half (if performing a routing table update)

Receipt of ECT(3) markings MUST NOT be treated the same as packet loss
as for the total viability of a given route.

## using delay as an overall base metric, not just for tunnels

is seemingly a very promising option in a fq_codeled world

## deprecate CS6 unicast

Regrettably CS6 is mistreated by many unicast wifi stacks, putting it
into the 802.11n Voice queue, which costs an entire txop and can only
handle a single packet for each TXOP.

CS6 can be used for multicast, but best effort should be used for most
(all) babel traffic on bridged wifi/ethernet, pure wifi or adhoc
networks.

Not using special markings for babel traffic allows for in-band dynamic
measurement of existing congestion and delay, and saves on TXOPs on busier
networks.

If used, CS6 should be used for it's actual original purpose,
and *sparingly*, as "a network alert" - perhaps only on a route retraction,
with careful attention to what effect delivering that notice has
on re-ordering in front of other backlogged routing traffic.

As some networks might mis-treat CS6 marked traffic in other ways,
on-going testing of whether or not it can be used at all can be
leveraged by periodically marking hello and IHU traffic with CS6,
and observing the results.

## Decreasing the fixed diameter estimate

The default "hold time" for route retractions and blackholing is
currently set to the largest possible fixed diameter of the network,
with fuzzy factors for the update interval factored in for the
anticipated time for a route change to propagate, ending up with a
default blackhole time of 2 minutes for certain kinds of updates.

Having a better estimate for the diameter (somehow) - would reduce the
hold time by a lot.

A distance-vector protocol might benefit from propagating the actual
distance (as measured in time), rather than or in addition to a derived
metric, in general.

## Rotating route announcement start points

Babel protocol messages are isotonic within a packet, and packets can be
delivered in any order. Larger updates can suffer from "tail loss", and
the starting point for a routing update could rotate to ensure more
route changes are propagated at different times in the stream.

This would also inject a degree of randomness into route changes.

## Route coalescing within babel routing messages

Particularly on gateway nodes, exporting more than a few covering routes
is undesirable.

Add guidance for administrators: wherever possible, p2p routes should fit
into an covering route for the entire domain and not be arbitrarily
assigned from a separate pool.

A AE type notice of various "filtered and coalesed" might help narrow
down the problems when a covering route is a generated entity between
two DV nodes.

## Reducing the kernel RIB size especially for p2p routes.

While individual babel instances can be configured to not export
all their local addresses "redistribute local deny", and only export
exceptions to the list...

Example:

The following 9 p2p and /64 routes could be reduced by the babel daemon
and handled in the kernel RIB table with just the single covering /48
route, reducing memory requirements and lookup times.

fde8:9cb6:b42e::1 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::20d:b9ff:fe41:6c2d via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::518:a4d9:af9:71ab via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::21b1:559d:16c9:3924 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::3952:75ff:d576:e671 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::8dc8:50bd:2f0b:7367 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::c5ff:3639:eaa2:171f via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::dc94:c26a:e93e:5610 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::f95d:e1c3:61f2:2538 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::/64 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium
fde8:9cb6:b42e::/48 via fe80::20d:b9ff:fe41:6c2e dev br-lan  proto babel  metric 1024  pref medium

## Authentication

Authentication, at least, should be treated as a first class citizen in
a modern routing protocol. BMX7 shows one path forward.

## Authentication relies on a sequence number and timestamp anyway

With more adoption of unicast we could move to calculating link metrics
based on all packets transmitted, not just hellos and IHUs, also using
gaps in sequence numbers (CTR) as indications of issues.

## Selective blackholing

Perhaps on some link types or on certain kinds of interconnects (vpns?)
the blackhole could be removed.

# Summary

The massive sea-change of the proposed changes here convert babel from
a multicast-mostly routing protocol to a unicast-mostly routing protocol,
with nearly no underlying changes to the RFCs, and, for that matter,
the codebase.

Entirely removing multicast from the protocol seems possible with
an alternate means of connection establishment.
