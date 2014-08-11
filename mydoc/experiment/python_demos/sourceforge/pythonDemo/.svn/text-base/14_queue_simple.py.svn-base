#!/usr/bin/python
from Queue import Queue
from Queue import PriorityQueue
a1='a1'
a2='a2'
a3='a3'
a4='a4'
a5='a5'

b1='b1'
b2='b2'
b3='b3'
b4='b4'
b5='b5'

q = Queue()
pq = PriorityQueue()
for i in xrange(5):
    p = 5 - i
    q.put("a"+str(p))
    q.put("b"+str(p))

    pq.put((p,"a"+str(p)))
    pq.put((p,"b"+str(p)))

for i in xrange(5):
    p = 5 - i
    q.put("a"+str(p)+str(i+5))
    q.put("b"+str(p)+str(i+5))

    pq.put((p,"a"+str(p)+str(i+5)))
    pq.put((p,"b"+str(p)+str(i+5)))

size = q.qsize()
print "queue item size:%s" %size
print "queue items:"
for i in xrange(size):
    print q.get()

size = pq.qsize()
print "priority queue item size:%s" %size
print "priority queue items:"
for i in xrange(size):
    print pq.get()

#"but priority queue with same priority is not queue, if we want so, do the following:"
import itertools
count = itertools.count()
poq = PriorityQueue()
for i in xrange(5):
    p = 5 - i
    poq.put((p,count.next(),"a"+str(p)))
    poq.put((p,count.next(),"b"+str(p)))

for i in xrange(5):
    p = 5 - i
    poq.put((p,count.next(),"a"+str(p)+str(i+5)))
    poq.put((p,count.next(),"b"+str(p)+str(i+5)))


size = poq.qsize()
print "priority ordered queue item size:%s" %size
print "priority ordered queue items:"
for i in xrange(size):
    print poq.get()
