#!/usr/bin/python

import socket
import struct
import fcntl

def getip(ethname):
	''' get the ipaddress of ethname.

	'''
    s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(s.fileno(), 0X8915, struct.pack('256s', ethname[:15]))[20:24])

if __name__=='__main__':
    print getip('eth0')
