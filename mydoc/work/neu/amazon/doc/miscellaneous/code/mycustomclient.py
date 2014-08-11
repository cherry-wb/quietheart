# -*- coding: utf-8 -*-
from gevent import monkey; monkey.patch_all()
#from ws4py.client.threadedclient import WebSocketClient
from ws4py.client.geventclient import WebSocketClient
from ws4py.messaging import TextMessage

class Lab126Client(WebSocketClient):
#    def opened(self):
#        msg = TextMessage("Message from client.")
#        self.send(msg.data,msg.is_binary)

    def received_message(self, m):
        print "=> In Client, received message is: %s" % str(m)
        self.close(reason='Bye bye')

if __name__ == '__main__':
    try:
        ws = Lab126Client('http://127.0.0.1:8000/ws', protocols=['http-only', 'chat'])
        ws.daemon = False
        ws.connect()
        msg = TextMessage("Message from client.")
        ws.send(msg.data,msg.is_binary)
    except KeyboardInterrupt:
        ws.close()
