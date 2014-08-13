#!/usr/bin/env python
import gevent
from gevent import monkey; monkey.patch_all()
from ws4py.client.geventclient import WebSocketClient
from ws4py.messaging import TextMessage

class Lab126Client(WebSocketClient):
    def received_message(self, m):
        self.handle_message(m)
        #self.close(reason='Bye bye')

    def handle_message(self, m):
        print "===> In Client, received message from server is: %s" % str(m)
        #gevent.sleep(2)
        #self.send("Continue.")

try:
    webSocketUrl = 'http://localhost:9000/ws'
    ws = Lab126Client(webSocketUrl)
    #ws.daemon = False
    ws.connect()
    msg = TextMessage("Message from lib client.")
    ws.send(msg)
    while True:
        message = ws.receive()
        print "+++receive response from server:%s" %message
        gevent.sleep(1)
        ws.send("Continue.")
    gevent.joinall([ws.run()])
except KeyboardInterrupt:
    ws.close()
