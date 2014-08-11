#!/usr/bin/python
import threading
numLock = threading.Lock()
g_num = 0
class MyThread(threading.Thread):
    def __init__(self,name,param):
        threading.Thread.__init__(self)
        self.setName(name)
        self.thread_stop=False
        self.param = param

    def run(self):
        global g_num
        for i in range(0,self.param):
            if not self.thread_stop:
                numLock.acquire()
                print self.getName(),
                print "g_num:",g_num
                g_num += 1
                numLock.release()

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
