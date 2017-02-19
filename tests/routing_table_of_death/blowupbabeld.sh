#!/bin/sh

END=10000
P=fd41:0:0:%x::/64
IFACE=eno1
CONF=routes.conf

add() {

for i in `seq 1 $END`
do
ip -6 route add `printf $P $i` dev $IFACE proto 43 expires 120
done

ip route save dev $IFACE proto 43 > $CONF

}

del() {

ip -6 route flush dev $IFACE proto 43

return

for i in `seq 1 $END`
do
ip -6 route del `printf $P $i` dev $IFACE proto 43
done
}

add
#sleep 120
#del

