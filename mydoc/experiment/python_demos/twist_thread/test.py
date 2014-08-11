#!/usr/bin/python
import time
from twisted.internet import reactor,defer
#run be called 5 times and then use mycallback chain , which the last return as next arg.
c = 0
d = defer.Deferred()
r = 0
def mycallback(arg):
    print mycallback.__name__,"'s arg is:",arg
    global r
    r = r+1
    return r

def run():
    global c
    c=c+1
    print "test c:",c
    time.sleep(1)
    d.addCallback(mycallback)
    if 5 == c:
        d.callback("start")
        reactor.stop()
    return d

reactor.suggestThreadPoolSize(5)
for i in range(0,5):
    reactor.callWhenRunning(run)
    print "add ok",i
reactor.run()
print "finish!"
