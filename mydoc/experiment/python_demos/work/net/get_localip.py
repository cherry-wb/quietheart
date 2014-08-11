#!/usr/bin/python
#The information of the current machine:
#$ifconfig
#eth0      Link encap:Ethernet  HWaddr 00:24:7e:03:62:14  
#          inet addr:192.168.1.139  Bcast:192.168.1.255  Mask:255.255.255.0
#          inet6 addr: fe80::224:7eff:fe03:6214/64 Scope:Link
#          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
#          RX packets:463737 errors:0 dropped:0 overruns:0 frame:0
#          TX packets:418383 errors:0 dropped:0 overruns:0 carrier:0
#          collisions:0 txqueuelen:1000 
#          RX bytes:264083575 (264.0 MB)  TX bytes:110666042 (110.6 MB)
#          Interrupt:16 Memory:fc500000-fc520000 
#
#lo        Link encap:Local Loopback  
#          inet addr:127.0.0.1  Mask:255.0.0.0
#          inet6 addr: ::1/128 Scope:Host
#          UP LOOPBACK RUNNING  MTU:16436  Metric:1
#          RX packets:10107 errors:0 dropped:0 overruns:0 frame:0
#          TX packets:10107 errors:0 dropped:0 overruns:0 carrier:0
#          collisions:0 txqueuelen:0 
#          RX bytes:788561 (788.5 KB)  TX bytes:788561 (788.5 KB)
#
#$./get_localip.py
#host name: quietheart
#local name: quietheart
#local addr: 127.0.1.1
#ipList: ('quietheart', [], ['127.0.1.1'])


import socket
host_name = socket.gethostname()
local_name = socket.getfqdn(socket.gethostname())
local_addr = socket.gethostbyname(local_name)
ip_list = socket.gethostbyname_ex(socket.gethostname())
print "host name:", host_name
print "local name:",local_name
print "local addr:",local_addr
print "ipList:",ip_list
