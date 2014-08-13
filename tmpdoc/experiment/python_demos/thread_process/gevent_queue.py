#!/usr/bin/python
import random
import gevent
from gevent import Greenlet
from gevent.queue import Queue, Empty

q = Queue(maxsize=5)
def productMsg():
    while True:
        num = random.randint(3,6)
        print "put:",num,num+3
        q.put((num,num+3))
        gevent.sleep(1)

gThr = Greenlet(productMsg)
gThr.start()
while True:
    a,e = q.get()
    print "get:",a,e

