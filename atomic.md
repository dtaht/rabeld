Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total
 time   seconds   seconds    calls  ms/call  ms/call  name
 39.53      3.72     3.72   152444     0.02     0.02  unsatisfied_request
 33.05      6.83     3.11   192175     0.02     0.02  satisfy_request
  9.56      7.73     0.90    51894     0.02     0.02  request_redundant
  8.82      8.56     0.83    21789     0.04     0.04  record_resend
  2.66      8.81     0.25  1469765     0.00     0.00  find_route_slot
  1.01      8.91     0.10 15118915     0.00     0.00  timeval_minus_msec
  0.74      8.98     0.07      585     0.12     3.28  update_neighbour_metric
  0.43      9.02     0.04  2165216     0.00     0.00  prefix_cmp
  0.32      9.05     0.03   228245     0.00     0.02  update_route
  0.32      9.08     0.03   185923     0.00     0.00  netlink_read.con

kernel_route(MODIFY metric): No such device
kernel_route(MODIFY metric): No such device
netlink_read: recvmsg(): No buffer space available
^Croot@dancer:~/git/rabeld#

kernel_route(MODIFY metric): No such device
kernel_route(MODIFY metric): No such device
kernel_route(MODIFY metric): Invalid argument

growing terror, that absolutely everything I depended on daily
didn't have robust error checking.

Odhcpd

Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink

Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink
Mon Feb 13 17:03:48 2017 daemon.debug odhcpd[13786]: Received 116 Bytes from kernel%netlink


d@dancer:~/git/rabeld$ cat babel2.log | sort | uniq -c
    365 kernel_route(ADD): File exists
   2121 kernel_route(FLUSH): No such process
 303320 kernel_route(MODIFY metric): Invalid argument
    329 kernel_route(MODIFY metric): No such device


v 3 nexthop 172.26.201.127
kernel_route(FLUSH): No such process
failed kernel_route: flush fd99::61/128 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::3aa2:8cff:fe5d:f9e5
kernel_route(FLUSH): No such process
send: Resource temporarily unavailable
send: Resource temporarily unavailable
send: Resource temporarily unavailable
send(unicast): Resource temporarily unavailable
failed kernel_route: add fd69:3860:b137::/48 from ::

failed kernel_route: flush fd44:0:0:d22::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d23::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d24::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d25::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d26::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d27::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d28::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d29::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d2a::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d2b::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d2c::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d2d::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d2e::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d2f::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d30::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d31::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d32::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d33::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d34::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d35::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d36::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d37::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d38::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d39::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d3a::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d3b::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d3c::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d3d::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d3e::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d3f::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d40::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d41::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d42::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d43::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d44::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d45::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d46::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d47::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d48::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d49::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d4a::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d4b::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d4c::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d4d::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d4e::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d4f::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d50::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d51::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d52::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d53::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d54::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d55::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d56::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d57::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d58::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d59::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d5a::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d5b::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:d5c::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fde8:9cb6:b42e::/60 from ::/0 table 254 metric 65535 dev 2 nexthop fe80::20d:b9ff:fe41:6c2d
kernel_route(FLUSH): No such process
send: Resource temporarily unavailable
send: Resource temporarily unavailable
send(unicast): Resource temporarily unavailable
send(unicast): Resource temporarily unavailable
send(unicast): Resource temporarily unavailable
send(unicast): Resource temporarily unavailable
failed kernel_route: flush 172.26.96.65/32 from ::/0 table 254 metric 65535 dev 3 nexthop 172.26.201.113
kernel_route(FLUSH): No such process
failed kernel_route: flush fd99::65/128 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::3aa2:8cff:fe5d:effb
kernel_route(FLUSH): No such process
failed kernel_route: flush 172.26.96.64/32 from ::/0 table 254 metric 65535 dev 3 nexthop 172.26.201.114
kernel_route(FLUSH): No such process
failed kernel_route: flush fd99::64/128 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::7ec7:9ff:fede:2bb5
kernel_route(FLUSH): No such process
failed kernel_route: flush 172.26.96.61/32 from ::/0 table 254 metric 65535 dev 3 nexthop 172.26.201.127
kernel_route(FLUSH): No such process
failed kernel_route: flush 172.26.201.127/32 from ::/0 table 254 metric 65535 dev 3 nexthop 172.26.201.127
kernel_route(FLUSH): No such process
failed kernel_route: flush fd99::61/128 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::3aa2:8cff:fe5d:f9e5
kernel_route(FLUSH): No such process
send: Resource temporarily unavailable

d@dancer:~/git/rabeld$ cat *.log  | sort | uniq -c
   2127 kernel_route(ADD): File exists
   5447 kernel_route(FLUSH): No such process
 624589 kernel_route(MODIFY metric): Invalid argument
    570 kernel_route(MODIFY metric): No such device
    123 send: Resource temporarily unavailable
     16 send(unicast): Resource temporarily unavailable

NO SUCH PROCESS??? is ESRCH?
ENODEV no such device
ENOENT no such


https://github.com/openvswitch/ovs/blob/master/lib/netlink-socket.c

KErnel bu error code as bytes read???

        error = (retval < 0 ? errno
                 : retval == 0 ? ECONNRESET /* not possible? */
                 : nlmsghdr->nlmsg_len != UINT32_MAX ? 0
                 : retval);

ENOBUFS - we've lost state

v 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:f21::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:f22::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:f24::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:f27::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process

failed kernel_route: flush 2406:da00:ff00::/48 from 2600:3c01:e001:9300::/56 table 254 metric 0 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(FLUSH): No such process
failed kernel_route: add 2406:da00:ff00::/48 from 2600:3c01:e001:9300::/56 table 254 metric 0 dev 3 nexthop fe80::16cc:20ff:fee5:64c1
kernel_route(ADD): File exists
send: Resource temporarily unavailable




So I got stuck in this state:

kernel_route(FLUSH): No such process
failed kernel_route: flush fd44:0:0:ac7::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::7ec7:9ff:fede:2bb5
kernel_route(FLUSH): No such process

d@dancer:~/git/babeld$ ip -6 route  | grep fd44:0:0:ac7::
fd44:0:0:ac7::/64 via fe80::7ec7:9ff:fede:2bb5 dev wlp2s0 proto babel metric 1024  pref medium
d@dancer:~/git/babeld$ sudo ip -6 route flush fd44:0:0:ac7::/64
[sudo] password for d:
d@dancer:~/git/babeld$ ip -6 route  | grep fd44:0:0:ac7::
gone

254 metric 65535 dev 3 nexthop fe80::7ec7:9ff:fede:2bb5
Error: inet prefix is expected rather than "metric".
d@dancer:~/git/babeld$ sudo ip -6 route flush fd44:0:0:ac6::/64 from ::/0 table 254 metric 65535 dev 3 nexthop fe80::7ec7:9ff:fede:2bb5

??? Is next hop the same as via?

If I flush something do I specify the metric??ip -

d@dancer:~/git/babeld$ sudo ip -6 route flush fd44:0:0:ac6::/64 from ::/0 table 254 dev wlp2s0 nexthop fe80::7ec7:9ff:fede:2bb5
Error: inet prefix is expected rather than "nexthop".
d@dancer:~/git/babeld$ sudo ip -6 route flush fd44:0:0:ac6::/64 from ::/0 table 254 dev wlp2s0 via  fe80::7ec7:9ff:fede:2bb5
d@dancer:~/git/babeld$ ip -6 route show | grep fd44:0:0:ac6
d@dancer:~/git/babeld$

A cool thing is I'm now in a state where all my known good routes are
toast

d@dancer:~/git/babeld$ ip -6 route | grep fd99::61
fd99::61 via fe80::3aa2:8cff:fe5d:f9e5 dev wlp2s0 proto babel metric 1024  pref medium
unreachable fd99::61 dev lo proto babel metric 4294967295  error -113 pref medium



unreachable 2406:da00:ff00::/48 from 2600:3c01:e001:9300::/56 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable 2601:646:4101:2de0::/60 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable 2601:646:4101:a740::/60 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fd32:7d58:8d63::/48 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fd55::/64 dev lo proto 44 metric 1024  error -101 pref medium
unreachable fd69:3860:b137::/48 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fd99::13 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fd99::61 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fd99::64 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fd99::65 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fd99::66 dev lo proto babel metric 4294967295  error -113 pref medium
unreachable fde8:9cb6:b42e::/60 dev lo proto babel metric 4294967295  error -113 pref medium




up vote
2
down vote
I wonder if you are running on a 64bits machine. If it is the case, I
suspect that the use of an int as the type of payload can be the root of
some issues as genlmsg_new() expects a size_t which is 64bits on x86_64.

FILE exists

EINVAL - invalid argument

(setsockopt(fd, SOL_SOCKET, SO_RCVBUF, ...) , or
nl_socket_set_buffer_size() if y

https://github.com/golang/go/issues/5932

./babel -t 253

table 253 proto static???

                if (setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER,
                                &bpf_prog, sizeof(bpf_prog))) {
                        syslog(LOG_ERR, "Failed to set BPF: %s", strerror(errno));
                        ret = -1;
                        goto out;
                }

I am still missing one edge case from this and I'm not sure
what it is.

d@dancer:~/git/rabeld$ ip route
default via 172.26.16.5 dev eno1 proto babel online
default via 172.26.201.1 dev wlp2s0 proto static metric 600
172.26.16.0/24 dev eno1 proto kernel scope link src 172.26.16.3
172.26.20.0/22 via 172.26.16.1 dev eno1 proto babel onlink
172.26.64.0/24 via 172.26.16.5 dev eno1 proto babel onlink
172.26.96.61 via 172.26.201.127 dev wlp2s0 proto babel onlink
172.26.96.64 via 172.26.201.114 dev wlp2s0 proto babel onlink
172.26.96.65 via 172.26.201.113 dev wlp2s0 proto babel onlink
172.26.96.66 via 172.26.201.190 dev wlp2s0 proto babel onlink
172.26.96.100 via 172.26.16.1 dev eno1 proto babel onlink
172.26.130.0/23 via 172.26.16.5 dev eno1 proto babel onlink
172.26.200.0/22 via 172.26.16.5 dev eno1 proto babel onlink
172.26.201.0/24 dev wlp2s0 proto kernel scope link src 172.26.201.244 metric 600
172.26.201.127 via 172.26.201.127 dev wlp2s0 proto babel onlink
198.27.232.0/22 via 172.26.16.5 dev eno1 proto babel onlink

024  pref medium
fd44:0:0:a01::/64 via fe80::3aa2:8cff:fe5d:effb dev wlp2s0 proto static metric 1024  pref medium
fd44:0:0:a02::/64 via fe80::3aa2:8cff:fe5d:effb dev wlp2s0 proto static metric 1024  pref medium
fd44:0:0:a03::/64 via fe80::3aa2:8cff:fe5d:effb dev wlp2s0 proto static metric 1024  pref medium
unreachable fd55::/64

d@dancer:~/git/rabeld$ ip -6 route
default from 2600:3c01:e001:9300::/56 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
default from 2601:646:4101:2de0::/60 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
default from 2601:646:4101:a740::/60 via fe80::32b5:c2ff:fe75:7faa dev eno1 proto babel metric 1024  pref medium
2406:da00:ff00::/48 from 2600:3c01:e001:9300::/56 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
2600:3c01:e001:9310::/64 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
2600:3c01:e001:9300::/56 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
2601:646:4101:2de0::/64 dev wlp2s0 proto ra metric 600  pref medium
2601:646:4101:2de0::/60 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
2601:646:4101:a740::/64 dev eno1 proto kernel metric 256  expires 291141sec pref medium
2601:646:4101:a740::/60 via fe80::32b5:c2ff:fe75:7faa dev eno1 proto babel metric 1024  pref medium
2602:24c:61bf:9828::/64 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
2620:0:ef0::/48 from 2600:3c01:e001:9300::/56 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
fd32:7d58:8d63::199 dev wlp2s0 proto kernel metric 256  pref medium
fd32:7d58:8d63::/64 dev wlp2s0 proto ra metric 600  pref medium
fd32:7d58:8d63::/48 via fe80::16cc:20ff:fee5:64c1 dev wlp2s0 proto babel metric 1024  pref medium
fd69:3860:b137::/48 via fe80::32b5:c2ff:fe75:7faa dev eno1 proto babel metric 1024  pref medium
fd99::4 via fe80::32b5:c2ff:fe75:7faa dev eno1 proto babel metric 1024  pref medium
fd99::10 via fe80::ba27:ebff:fec9:3c08 dev eno1 proto babel metric 1024  pref medium
fd99::13 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
fd99::61 via fe80::3aa2:8cff:fe5d:f9e5 dev wlp2s0 proto babel metric 1024  pref medium
fd99::64 via fe80::7ec7:9ff:fede:2bb5 dev wlp2s0 proto babel metric 1024  pref medium
fd99::65 via fe80::3aa2:8cff:fe5d:effb dev wlp2s0 proto babel metric 1024  pref medium
fd99::66 via fe80::3aa2:8cff:fe5d:d369 dev wlp2s0 proto babel metric 1024  pref medium
fdaf:dc63:6de9:8::/64 dev eno1 proto kernel metric 256  pref medium
fde8:9cb6:b42e::/60 via fe80::20d:b9ff:fe41:6c2d dev eno1 proto babel metric 1024  pref medium
fe80::/64 dev wlp2s0 proto kernel metric 256  pref medium
fe80::/64 dev eno1 proto kernel metric 256  pref medium
default via fe80::16cc:20ff:fee5:64c1 dev wlp2s0 proto static metric 600  pref medium
default via fe80::32b5:c2ff:fe75:7faa dev eno1 proto ra metric 1024  expires 65305sec hoplimit 64 pref high
