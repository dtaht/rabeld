# Babel Protocol Unicast Extension

A (mostly) backward compatible extension of the babel protocol and
daemon. This paper describes several possibilities for for extensions to
the existing babel protocol that allows for co-operating daemons to
transparently migrate to a nearly-entirely unicast-only mode, using
multicast for initial mutual discovery, only.

These techniques could be extended further to manage p2p tunneled routes
transparently.

## (My possibly brain damaged) Unicast-capable TLV hello proposal

The absence of slow, unreliable, multicast traffic on a link capable of
carrying unicast at higher rates would lead to a generally better link.

Switching to a system where the multicast hello also has a flag
indicating willingness to use unicast hellos would reduce babel's use of
multicast to initial neighbor discovery, only, and speed up discovery
and fallback.

Unicast hellos do not need to carry the "I am unicast" capable flag,
in fact they could take on another format entirely.

## Alternative Approaches that are a PITA

* Explicit extension of the main tlvs

Adding a new TLV that explicitly announces this capability to the hello
packet would be silently ignored by older implementations, and cost 4
bytes in the hello message.

* Add a byte to the hello tlv

Violates the rfc (must be ignored), costs a byte only

* Automatically Sense unicast hello capability

Rather than make any changes to the protocol, RABEL daemons can
supply one or several unicast hello packets to new router_id multicast hellos,
and see if they get a response. If they get a response then they can
silenty upgrade to unicast hellos. This may, in fact, be the best
way to approach the above methods.

### Flag day options

* Switch to a different protocol

UDP_LITE is commonly available and nearly underused.

* Bump babel version

Still need to indicate willingness to unicast.

* Encode unicast-hello-willingness into an route update instead

There is a pre-existing "flags" field that is part of the update tlv,
with 6 bits unused. Semantically, adding 2-3 bits in this field to
indicate unicast-hello-willingness does not make sense, however
the bits ARE unused, and would also rapidly result in propagating
unicast hello capability to the network, and leave the hello short.

* Use a dedicated TLV not part of the hello packet.
* Use a different port
* Use a different multicast address

## Piggyback packets

- this is essentially what a device in powersave mode already does to
  multicast. All packets are buffered until the next beacon interval.

Having a generic socket type of "piggyback" might help on systems with
delayed broadcasts "Please send this packet in the next 4 seconds", and
could perhaps leverage the 6tich APIS.

Passive IHU - leveraging layer 2 statistics?

## Codebase overhead

the seqno/hello tuple would need to become a neighbor/seqno/hello tuple.

## The case for minimizing multicast

The use of multicast packets for measuring packet loss is of minimal
usefulness, and will become less so if/when multicast-spoofing
techniques become more common in the wild.

In wifi, unicast paths run at much higher rates than multicast ones, in
the case of 802.11ac, as much as 1000 times higher.

Calculated one way (as a fraction of the total bandwidth available),
a 300Mbit capable link with a 6mbit multicast rate, it would be faster
to send unicast to 50 stations than it would be to use multicast.

The real world, however, has variable rates and a fixed minimum length
TXOP, and a RABEL client MAY chose to change to multicast hello when
sufficient listeners on a link exist. The suggested number is 15. Most
links are considerably "sparser" than that.

On active links, the added cost of carrying routing traffic via unicast
nearly "free".

Multicast hello and a unicast IHU does have the advantage of testing
both kinds of path simultaneously.

Receiving unicast on inactive links this causes battery life and costs a TXOP.
However, sleepy nodes SHOULD send their hellos and IHUs with a longer
request for wakeups in the first place.

## upgrading to unicast hello (method 2)

Unicast hello is flagged by advertising the capability in the
new flags tlv in the multicast hello packet.

0: Prefer multicast hello
1: Prefer unicast hello
2-7: undefined

RABEL listeners seeing hello packets containing no flags field MUST use
multicast for their hello exchange on that interface.

RABEL listeners that hear no multicast hellos on a given interface for 1
minute can upgrade to a unicast hello.

RABEL listeners that see a multicast hello preference must fall back to
multicast hello.

RABEL listeners that hear more than X (15?) stations on a given link or
(ratio of multicast rate vs unicast rates) SHOULD elect to use multicast.

## Upgrading to a unicast hello (method #1)

Periodically send a unicast hello to a multicast broadcaster and see
if you get a an IHU. After sufficient IHUs are heard, switch to
unicast hello.

## Unicast IHU

Is already added and works transparently with the default babel daemons.
This might solve an on-going problem with things like AP isolation mode,
where a multicast transmission is often "heard", but a unicast one is not.

## Unicast routing table updates

Universal (instead of triggered) unicast routing table updates would be
*much faster* and more reliable if sent more exclusively over unicast,
subject to the total number of stations paying attention.

This is already supported in principle by the existing codebase.

# issues

## Advantages to more unicast

Actual unicast traffic keeps updating the wifi rate control statistics,
multicast bypasses that, and leads to invalid rate statistics when the
link actually is used.

* Decrease the amount of multicast traversing switches with sparse babel speakers
* Improve the performance on wireless p2p links



...

# Tubel - Tunneling babel

## Tunnel TLV

One interesting use case for babel has becom e creating arbitrary
tunnels for it, and the resulting architecture has been messy and
difficult. (but people do it anyway)

Having a unicast rendezvous and transfer mechanism that could work over udp
with real ipv6 addresses for tunnel management would be nice.

For inspiration, see:

https://tools.ietf.org/html/draft-ietf-idr-tunnel-encaps-02

## Piggyback packets

- this is essentially what a device in powersave mode already does to
  multicast. All packets are buffered until the next beacon interval.

Having a generic socket type of "piggyback" might help on systems with
delayed broadcasts "Please send this packet in the next 4 seconds", and
could perhaps leverage the 6tich APIS.

Passive IHU - leveraging layer 2 statistics?
