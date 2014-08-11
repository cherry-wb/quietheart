# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

import time
import threading
from gevent import monkey; monkey.patch_all()


MAX_RUNNING = 30

class Scheduler(threading.Thread):
    def __init__(self, handler):
        threading.Thread.__init__(self)
        self.handler = handler
        self.stop = False

    def run(self):
        """
        TODO, access waitingQueue and runningQueue,
        and wsRMS websocket request resources
        
        Question, How to use queue, wsRMS variables, wsClient and so on
        """
        
        while not self.stop:
            if self.handler.waitingQueue.isEmpty():
                print "Waiting queue empty."
                time.sleep(1)
                continue

            if self.handler.runningQueue.size() + self.handler.wsRms.queue.size() >= MAX_RUNNING:
                print "Running queue overload."
                time.sleep(1)
                continue

            message = self.handler.waitingQueue.get()
            print "Get one from wait queue: %s" %message.getRes()
            self.handler.wsRms.register(message)


    def stop(self):
        self.stop = True

