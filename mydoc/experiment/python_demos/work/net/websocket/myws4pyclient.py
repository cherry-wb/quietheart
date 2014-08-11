# -*- coding: utf-8 -*-
from ws4py.client.threadedclient import WebSocketClient
from ws4py.messaging import TextMessage

class Lab126Client(WebSocketClient):
    def received_message(self, m):
        if not hasattr(self,'msgNum'):
            self.msgNum=0
        print "=> In Client, received message is: %s" % str(m)
        if self.msgNum >= 5:
            self.close(reason='Bye bye')
        else:
            msg = TextMessage("Message again from client, number: %d." %self.msgNum)
            self.send(msg)
            self.msgNum+=1

if __name__ == '__main__':
    try:
        ws = Lab126Client('http://localhost:9000/ws', protocols=['http-only', 'chat'])
        ws.daemon = False
        ws.connect()
        msg = TextMessage("Message from client.")
        ws.send(msg)
    except KeyboardInterrupt:
        ws.close()
