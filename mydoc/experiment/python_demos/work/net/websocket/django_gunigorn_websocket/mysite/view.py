from gevent import monkey; monkey.patch_all()
from django.http import HttpResponse

def ws_handler(request,arg=None):
    ws = request.META.get('wsgi.websocket', None)
    print ws
    if ws != None:
        print '-------ws_connector--------'
        message = ws.receive()
        handle_message(request, message)
        ws.close()
    else:
        print '-------no_ws_connector--------'
        html = "<html><body>Not websocket</body></html>"
        return HttpResponse(html)

def handle_message(request, msg):
    print "===> In server, data received from client is:",msg
    ws = request.META.get('wsgi.websocket', None)
    ws.send("Message from server")
