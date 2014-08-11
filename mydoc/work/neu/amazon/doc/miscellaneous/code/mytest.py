from ws4py.client.threadedclient import WebSocketClient
class EchoClient(WebSocketClient):
    def opened(self):
     print "Connection opened..."
    def closed(self, code, reason=None):
        print code, reason
    def received_message(self, m):
        self.send(m)
try:
    ws = EchoClient('http://localhost:9000/ws')
    ws.connect()
except KeyboardInterrupt:
    ws.close()
print "test"
