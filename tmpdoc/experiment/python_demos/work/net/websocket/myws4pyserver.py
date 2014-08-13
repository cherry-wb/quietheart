# -*- coding: utf-8 -*-
from gevent import monkey; monkey.patch_all()

import gevent
import argparse
import gevent.pywsgi

from ws4py.websocket import WebSocket
from ws4py.server.geventserver import UpgradableWSGIHandler
from ws4py.server.wsgi.middleware import WebSocketUpgradeMiddleware

from ws4py.server.geventserver import WebSocketServer
from ws4py.messaging import TextMessage

class Lab126WebSocket(WebSocket):
    def received_message(self, m):
        if not hasattr(self,'msgNum'):
            self.msgNum=0
        self.recvMsg = str(m)
        print "=> In Server, received message is: %s" % self.recvMsg

        #self.send(m.data, m.is_binary)
        msg = TextMessage("Ok! Response from server number:%d." %self.msgNum)
        self.send(msg)
        self.msgNum += 1


class Lab126WebSocketServer(WebSocketServer):
    
    def __init__(self, host, port):
        WebSocketServer.__init__(self, (host, port))
        self.application = self
        self.ws = WebSocketUpgradeMiddleware(app=self.wsHandler,websocket_class=Lab126WebSocket)

    def __call__(self, environ, start_response):
        if environ['PATH_INFO'] == '/ws':
            return self.ws(environ, start_response)
        return self.webApp(environ, start_response)

    def wsHandler(self, websocket):
        g = gevent.spawn(websocket.run)
        g.join()
        #self.recvMsg = websocket.recvMsg

    def webApp(self, environ, start_response):
        """
        Our main webapp that'll display the chat form
        """
        status = '200 OK'
        headers = [('Content-type', 'text/html')]

        start_response(status, headers)

        #return "Hello world! %s" %self.recvMsg
        return "Hello world! "

if __name__ == '__main__':
    #parser = argparse.ArgumentParser(description='Echo gevent Server')
    #parser.add_argument('--host', default='127.0.0.1')
    #parser.add_argument('-p', '--port', default=9000, type=int)
    #args = parser.parse_args()

    #server = Lab126WebSocketServer(args.host, args.port)
    server = Lab126WebSocketServer('127.0.0.1', 9000)
    server.serve_forever()
