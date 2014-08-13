from ws4py.client.threadedclient import WebSocketClient

class DummyClient(WebSocketClient):
    def opened(self):
        def data_provider():
            for i in range(1, 20):
                yield str(i) + ','

        #self.send(data_provider())

        for i in range(0, 200):
            print i
            self.send(str(i)+':')

    def closed(self, code, reason):
        print "Closed down", code, reason

    def received_message(self, m):
        print "=> %d %s" % (len(m), str(m))
        if len(str(m)) == 175:
            self.close(reason='Bye bye')

if __name__ == '__main__':
    try:
        ws = DummyClient('ws://localhost:9001/', protocols=['http-only', 'chat'])
        ws.connect()
    except KeyboardInterrupt:
        ws.close()
