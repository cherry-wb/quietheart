# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.


from core.message import Message
from core.queue import MyQueue 
from core.rms_client import RmsWsClient
from core.scheduler import Scheduler


class Handler(object):

    def __init__(self, request):
        self.request = request
        self.wsEngine = request.META.get('wsgi.websocket', None)
        self.wsRms = RmsWsClient(self)

        self.stop = False
        self.waitingQueue = MyQueue()
        self.runningQueue = MyQueue()


    def process(self):
        """
        TODO, Handle request 
        1] open to RMS websocket
        2] New waitingQueue and runningQueue and defines maximum size
        3] Launch comsumer thread, then monitor runningQueue
        4] Two thread do their work
            How to use Queue?
            MainThread
            1] new a waitingQueue, like a proceduer, everytime, main thread receives client request, then put it into waitintQueue
            2] Everytime, main thread receives client release, call RMS release resources, then remove resource from runningQueue,
                How to remove resources from runningQueue, need to talk with RMSs
    
            CosumerThread
            2] new a runningQuueu, like a consumer, its has maximum size, 
                when runningQueue reaches its maximun size, consumer thread sleep 1 second, then poll again
                when runningQueue resources -1, consumer thread get a new resource from waiting queue,
                    if this unit is BUSY by RMS, put it to the end of the waiting queue, then loop get next
                    if this unit is Y/N by RMS, put it to the runningQueue + 1, then return it to client
                    Need to talk RMS
        """

        self.wsRms.connect()

        self.scheduler = Scheduler(self)
        self.scheduler.setDaemon(True)
        self.scheduler.start()

        while not self.stop:
            json = self.wsEngine.receive()
            if json == None:
                time.sleep(1)
                continue
            print "------->Receive from lib: %s" %json
            message = Message().restore(json)

            if message.getCmd() == Message.CMD_REGISTER:
                self.waitingQueue.append(message)

            elif message.getCmd() == Message.CMD_RELEASE:
                self.wsRms.release(message.getRes())
                self.runningQueue.remove(message)

        self.scheduler.stop()

    def stop(self):
        self.stop = True
