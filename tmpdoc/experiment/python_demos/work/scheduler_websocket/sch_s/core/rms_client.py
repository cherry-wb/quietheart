# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

from core.message import Message
from core.queue import MyQueue
from gevent import monkey; monkey.patch_all()
from ws4py.client.threadedclient import WebSocketClient

class RmsWsClient(WebSocketClient):

    RMS_SERVER = "ws://localhost:7000/ws"


    def __init__(self, handler):
        WebSocketClient.__init__(self, self.RMS_SERVER)
        self.handler = handler
        self.queue = MyQueue()


    def opened(self):
        ""


    def received_message(self, json):
        rmsmsg = Message().restore(json)
        print "--------->Response from rms: %s" %rmsmsg.getRes()
        if rmsmsg.getStatus() == Message.STATUS_Y:
            self.handler.wsEngine.send('Y')
            message = self.queue.remove(rmsmsg.getId())
            self.handler.runningQueue.append(message)

        elif rmsmsg.getStatus() == Message.STATUS_N:
            self.handler.wsEngine.send('N')
            self.queue.remove(rmsmsg.getId())

        elif rmsmsg.getStatus() == Message.STATUS_BUSY:
            message = self.queue.remove(rmsmsg.getId())
            self.handler.waitingQueue.append(message)


    def closed(self, code, reason=None):
        ""


    def register(self, message):
        self.queue.append(message)
        print "-------->Send to rms: %s" %message.getRes()
        self.send(message.getRes())


    def release(self, message):
        self.send(message.getRes())

