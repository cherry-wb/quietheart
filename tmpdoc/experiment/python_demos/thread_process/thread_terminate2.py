#!/usr/bin/python
import time
import threading
import inspect
import ctypes

def _async_raise(tid, exctype):
    """raises the exception, performs cleanup if needed"""
    if not inspect.isclass(exctype):
        raise TypeError("Only types can be raised (not instances)")
    res = ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, ctypes.py_object(exctype))
    if res == 0:
        raise ValueError("invalid thread id")
    elif res != 1:
        ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, 0)
        raise SystemError("PyThreadState_SetAsyncExc failed")


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

    def raise_exc(self, exctype):
        """raises the given exception type in the context of this thread"""
        _async_raise(self._get_my_tid(), exctype)

    def terminate(self):
        """raises SystemExit in the context of the given thread, which should 
        cause the thread to exit silently (unless caught)"""
        self.raise_exc(SystemExit)

    def run(self):
        while True:
            print 'test thread %s run.' %threading.current_thread().__dict__
            time.sleep(1)


if __name__ == '__main__':
    print "main thread start."
    print "sub thread start."
    t = MyThread()
    t.start()
    time.sleep(5)
    print "begin to stop sub thread after 5 seconds."
    t.terminate()
    while True:
        time.sleep(1)
