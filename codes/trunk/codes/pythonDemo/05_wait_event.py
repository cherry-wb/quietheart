#!/usr/bin/python
import time
import threading
from threading import Event

runEvent=Event()
class MyThread(threading.Thread):
    def __init__(self,param):
        threading.Thread.__init__(self)
        self.param = param

    def run(self):
        print "Sub thread."
        time.sleep(self.param)
        runEvent.set()

t1 = MyThread(5)
t1.start()
print "Begin to wait."
while not runEvent.wait(1):
    print "waiting..."

print "wait over."
