#!/usr/bin/python
import time
import threading

class MyThread(threading.Thread):
    #def __init__(self):
    #    threading.Thread.__init__(self)

    def _get_my_tid(self):
        """determines this (self's) thread id"""
        if not self.isAlive():
            raise threading.ThreadError("the thread is not active")
 
        # do we have it cached?
        if hasattr(self, "_thread_id"):
            return self._thread_id
 
        thread_id = threading.current_thread().ident
        if None != thread_id:
            return thread_id
        else:
            raise AssertionError("could not determine the thread's id")

    def run(self):
        try:
            while True:
                print 'test thread %s run.' %threading.current_thread()
                time.sleep(1)
        except Exception,e:
            print "thread:%s Error." %threading.current_thread()
            print e


if __name__ == '__main__':
    print "main thread start."
    print "sub thread start."
    t = MyThread()
    t.start()
    print "begin to stop sub thread after 5 seconds."
    #time.sleep(5)
    #t.exit()
    #while True:
    #    time.sleep(1)
    import sys
    sys.exit()
    print "exit main"
