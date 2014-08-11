#!/usr/bin/python
'''
An example of signal function.
call run function, if it not return at specified time, regard it as timeout and raise error.
Used function:
signal.alarm
signal.ALRM
os.kill
raise Exception
'''
import os
import time
import signal
class TimeOutControl:
    def __init__(self):
        self.newTimeout = 0
        self.oldTimeout = 0
        self.newHandler = None
        self.oldHandler = None

    def setupTimeout(self,timeout,handler):
        self.newTimeout = timeout
        oldHandler = signal.getsignal(signal.SIGALRM)
        print "old handler:",oldHandler
        signal.signal(signal.SIGALRM,timeoutHandler)
        self.oldTimeout = signal.alarm(self.newTimeout)
        print "previous timeout:",oldHandler

    def cleanupTimeout(self):
        leftTime = signal.alarm(0)
        elapseTime = self.newTimeout - leftTime
        print "left:",leftTime
        print "elapse:",elapseTime
        if self.oldTimeout > elapseTime:
            self.oldTimeout = self.oldTimeout-elapseTime
            signal.signal(signal.SIGALRM,self.oldHandler)
            signal.alarm(self.oldTimeout)
        elif self.oldTimeout > 0:
            signal.signal(signal.SIGALRM,self.oldHandler)
            os.kill(signal.SIGALRM)
        self.__init__()
        return leftTime

def timeoutHandler(signo,frame):
    print "timeout!"
    print "no:",signo
    print "arg:",frame
    raise Exception("Timeout")

def myfunc(sec):
    for i in range(sec):
        time.sleep(1)
        print i,"seconds elapse."

if "__main__" == __name__:
    print "start main."
    t = TimeOutControl() 
    t.setupTimeout(3,timeoutHandler)
    try:
        myfunc(6)
    except Exception,e:
        print "+++:",e
    t.cleanupTimeout()
    print "end main."
