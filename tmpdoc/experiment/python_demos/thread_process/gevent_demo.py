#!/usr/bin/python
import random
import gevent
from gevent import Greenlet

def thrFunc(s):
    print "%s start.\n" %s
    gevent.sleep(2)
    print "%s end.\n" %s

gThr = Greenlet(thrFunc,"startjoin1")
gThr.start()
gThr.join()
gThr = Greenlet(thrFunc,"startjoin2")
gThr.start()
gThr.join()

print "+++++++++"
gThr = Greenlet(thrFunc,"start1")
gThr.start()
gThr = Greenlet(thrFunc,"start2")
gThr.start()
gThr = Greenlet(thrFunc,"start3")
gThr.start()
gThr = Greenlet(thrFunc,"start4")
gThr.start()

print "+++++++++"
gThr1 = Greenlet.spawn(thrFunc,"spawn1")
gThr2 = Greenlet.spawn(thrFunc,"spawn2")
gThr2.join()
