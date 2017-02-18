# Rabeld Goals

While the hope is most if not all of these features will make it back
into mainline babeld, having a safe play space was needed for what's
turned out to be a major hacking run.

In order to understand this code, I had to rewrite first.

## Features

- Better error handling
- higher cpu speed
- optimized qsort algorithm and/or better route lookups
- full support of 64 bit architectures
- Treat ipv6 as natural quantities
-- NEON support
-- SSE2 support
- Bugs quashed
- Better handling of cpu overload
- short RTT metrics
- working wifi channel detection
- kernel expires support
- "trust but verify" model
- interface globbing
- unicast route updates
- etags support and whole program compilation

40,000 routes or bust!

## Bugs quashed

- There is a persistent ongoing bug with losing connectivity
- On overload spread out route updates
- Improve rate limiter to account for actual behavior
- why do we get martian routes?

## Better Error handling

## 128 bit quantities

Handling ipv6 is just more "natural" if you can do it with 128 bits.

ARM32 in particular has a paucity of registers compared to mips.

Timekeeping is simpler with 128 bit quantities

get away from memory references for zeros and ones - zeros is xor 128
bits....

TODO figure out how to load a shift

## Todo items

Switch to a better netlink
- direct ubus/ulib support
- modernize code base

# Long term goals

## Multithreading

Originally I'd planned to write this from scratch as a librcu enabled
multithreaded daemon, as well as find ways to do crazy things like
offload BF to custom hardware.

## BPF based netlink filtering

## Crypto

I love the idea of offloading the crypto api into the kernel, actually.

## Unicast Hello

## Protocol enhancements

### IHU unicast

Protocol extension: Supply the number of routes I think I have from you

### Meshy tunneling in userspace

Build a network of networks over tunnels

### FQ and AQM support

### Better route compression

### Non-link-state-y monitoring daemon

### Incremental BF
