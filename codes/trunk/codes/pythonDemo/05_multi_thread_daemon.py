#!/usr/bin/python
#if not have daemon subthread, main thread won't exit even if not join.
#if have daemon sub thread, main thread can exit without join and then daemon exit.
import threading
import time

class MyThread(threading.Thread):
    def __init__(self,name,param):
        threading.Thread.__init__(self)
        self.setName(name)
        self.thread_stop=False
        self.param = param

    def run(self):
        a = 1
        while True:
            time.sleep(1)
            print a
            a += 1

    def stop(self):
        self.thread_stop = True

if "__main__" == __name__:
    timeout = 5
    t1 = MyThread("thread1",5)

    t1.setDaemon(True)
    t1.start()

    t1.join(timeout)
    if t1.isAlive():
        print "thread1 timeout"
    else:
        print "thread ok!"

    for i in range(1,3):
        print "main thread end!"
        time.sleep(1)
