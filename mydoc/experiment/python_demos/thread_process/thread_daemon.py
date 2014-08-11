#!/usr/bin/python
#setDaemon: if not True(default), the main thread will wait sub thread return before exit even if not join.
#else main will exit and daemon thread exit also.
import threading
import time

class MyThread(threading.Thread):
    def __init__(self,name,param):
        threading.Thread.__init__(self)

    def run(self):
        while True:
            time.sleep(1)
            print "sub"

if "__main__" == __name__:
    t1 = MyThread("thread1",5)
    t1.setDaemon(True)

    t1.start()

    time.sleep(5)

