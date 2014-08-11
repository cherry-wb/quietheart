# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.
import threading

class MyQueue(object):
    def __init__(self):
        self.queue = []
        self.lock = threading.Lock()


    def append(self, message):
        self.lock.acquire()
        self.queue.append(message)
        self.lock.release()

    def remove(self, messageId):
        self.lock.acquire()
        message = None
        for item in self.queue:
            if item.getId() == messageId:
                message = item
                break
        if None != message:
            self.queue.remove(message)
        self.lock.release()
        return message

    def get(self):
        self.lock.acquire()
        msg = self.queue.pop(0)
        self.lock.release()
        return msg

    def isEmpty(self):
        self.lock.release()
        empty = len(self.queue) == 0
        self.lock.release()
        return empty
    
    def size(self):
        self.lock.release()
        length = len(self.queue)        
        self.lock.release()
        return length
