#!/usr/bin/python

import time
import random

import gevent
from gevent import Greenlet
from gevent.pool import Pool


def thrFunc(n):
    print "sleep %d seconds start.\n" %n
    gevent.sleep(n)
    print "sleep %d seconds end.\n" %n

threadPool = Pool(size=3)
while True:
    sec = random.randint(3,6)
    #gThr = Greenlet(thrFunc,sec)
    #gThr.start()
    #gThr.join()
    print "+++free:",threadPool.free_count()
    threadPool.spawn(thrFunc,sec)
    #threadPool.apply_async(thrFunc,sec)
