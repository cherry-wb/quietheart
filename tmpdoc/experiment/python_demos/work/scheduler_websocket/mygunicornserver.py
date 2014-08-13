import time
from gevent import monkey; monkey.patch_all()


"""
gunicorn -b 0.0.0.0:7000 -k "geventwebsocket.gunicorn.workers.GeventWebSocketWorker" mygunicornserver:runserver
"""
def ws_connector(environ):
    if environ["PATH_INFO"] == '/ws':
        print '-------ws_connector--------'
        ws = environ["wsgi.websocket"]
        while True:
            message = ws.receive()
            if message != None:
                print "===> In server, data received from client is:",message
                ws.send("Response message from rms server.")
            else:
                print "None message!"
                time.sleep(1)
    else:
        print '-------no_ws_connector--------'
        return False

def runserver(environ, start_response):
    if ws_connector(environ) != True:
        # If environment is not WebSocket, then call django server
        response_body = "Hello world!"
        status = '200 OK'
        response_headers = [('Content-Type', 'text/html'),
    ('Content-Length', str(len(response_body)))]
        start_response(status, response_headers)
        return [response_body]

