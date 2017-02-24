# Kernel Hacks

## Passive Routing Loop Detection

We've got conntrack. We've got hashes from fq_codel. We can clearly
identify when a packet is looping in one interface from another.

We can get hopcount
and see if we're losing somehow. Toss samples into a bloom filter and
see what pops out.

Nobody measures routing loops actively, in the sense that the routing 
protocol tends to exist separate from  the traffic. Having a passive
loop routing detector could trigger other actions from userspace

"Loop detected from A to B. - Well, try A to C. C is looping? Well,

A) clamp the hopcount rapidly to at least minimize the damage in the loop?
B) Keep tryng alternate routes. Measure the hop count after each change.
It may not be the shortest number of hops but seeing any form of inflation
larger that X or smaller than Y is a "good sign" you are permuting the
problem downstream. 

C) More aggressively drop packets identified as looping

## Passive RTT measurement

TSDE is doing this presently in userspace.

## Routing counters

just like with iptables, we could be keeping track of packets going
through each route. I think this is an openflow feature. 

## Rotating mac hash

Hash the multicast packets primarily on their mac addresses. Or leverage
the ip layer when avaiable and treat arp specially. FQ - on a per packet
basis, not DRR - into a fixed length head drop queue. In this case you
do want to rotate the hash regularly and there is no need for conventional
convention control.

## Rate limit the multicast queue

Limit multicast traffic to injecting bursts of no more than X ms and
yet service the queue rationally - if there's no other traffic multicast
is fine...

## Hardware assist for routing aggregation and prefix lookup

Finding minimal prefixes to sort against is computationally intensive.
However it can be offloaded to a co-processor (the one I'm
fiddling with is a parallela, and there is a GPU on most of 
the hackerboards). I wonder to what extent those FPUS can do
shifts ands and xors?

There's a lot of attempts:

http://research.ijcaonline.org/volume110/number13/pxc3901027.pdf

Babel is NOT quite bellman ford and would be useful to try  co-operation
with a kernel feature to manage some of it - and produce a real implementation
with real source code.

- decryption
- authentication

In this case dropping packets as soon as possible that are not authenticated
is desirable - e.g. - in the kernel. 

sch_fq's basic red/black tree could be useful here with shared co
processor memory - 

I'm also finding the prosecpect of userspace RCU as interesting.

## The Cambridge NETFPGA project has some interesting stuff going on,.

## So does mellonix

I am under the impression mellonix runs linux onchip.

LTE modems run linux on chip.
