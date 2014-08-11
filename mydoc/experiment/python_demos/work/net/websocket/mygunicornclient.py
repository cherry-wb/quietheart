#!/usr/bin/env python
from gevent import monkey; monkey.patch_all()
from ws4py.client.geventclient import WebSocketClient
from ws4py.messaging import TextMessage

class Lab126Client(WebSocketClient):
    def received_message(self, m):
        self.handle_message(m)
        self.close(reason='Bye bye')

    def handle_message(self, m):
        print "===> In Client, received message from server is: %s" % str(m)

try:
    webSocketUrl = 'http://localhost:7000/ws'
    ws = Lab126Client(webSocketUrl)
    ws.daemon = False
    ws.connect()
    msg = TextMessage("Message from client.")
    ws.send(msg)
    ws.receive()
except KeyboardInterrupt:
    ws.close()
