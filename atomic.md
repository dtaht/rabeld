I am still missing one edge case from this and I'm not sure
what it is.

d@dancer:~/git/rabeld$ ip route
default via 172.26.16.5 dev eno1 proto babel onlink 
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

