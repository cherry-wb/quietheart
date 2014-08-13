#!/usr/bin/python
import threading
import time

class MyThread(threading.Thread):
    def __init__(self,name,param):
        threading.Thread.__init__(self)
        self.setName(name)
        self.thread_stop=False
        self.param = param

    def run(self):
        for i in range(0,self.param):
            if not self.thread_stop:
                print self.getName(),
                print ":",i
                time.sleep(1)

    def stop(self):
        self.thread_stop = True

if "__main__" == __name__:
    t1 = MyThread("thread1",5)
    t2 = MyThread("thread2",5)

    t1.start()
    t2.start()

    t1.join() #wait t1 end.
    t2.join() #wait t2 end.

    print "main thread end!"
