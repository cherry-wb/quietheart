#!/usr/bin/python
import random
import threading
import gevent
from gevent import Greenlet

class MyThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        print "======="

def subFunc():
    print "%s start.\n" %"subfunc"
    gevent.sleep(2)
    MyThread().start()
    print "%s end.\n" %"subfunc"

def thrFunc(s):
    print "%s start.\n" %s
    gevent.sleep(2)
    gThr = Greenlet(subFunc)
    gThr.start()
    gThr.join()
    print "%s end.\n" %s

print "+++++++++"
gThr = Greenlet(thrFunc,"start1")
gThr.start()

print "+++++++++"
gThr1 = Greenlet.spawn(thrFunc,"spawn1")
gThr1.join()

