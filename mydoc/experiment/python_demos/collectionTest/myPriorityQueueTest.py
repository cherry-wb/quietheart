#!/usr/bin/python
import itertools
import heapq
from Queue import Queue

class MyPriorityQueue(Queue):
    HIGH=3
    NORMAL=5
    LOW=7
    BLOCK=9
    def _init(self,maxsize):
        self.count = itertools.count()
        self.queue = []

    def _qsize(self,len=len):
        return len(self.queue)

    def peek(self):
        pass

    def put(self,item,priority=MyPriorityQueue.NORMAL):
        element = (priority,count.next(),item)
        heapq.heappush(self.queue,element)

    def get(self):
        priority,count,item = heapq.heappop()
        return item

    def block(self):
        pass
