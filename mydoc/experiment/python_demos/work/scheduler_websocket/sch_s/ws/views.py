# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

from gevent import monkey; monkey.patch_all()
from django.http import HttpResponse
from ws.handler import Handler

def ws_connector(request):
    ws = request.META.get('wsgi.websocket', None)
    if ws is None:
        return HttpResponse("SCH/S Websocket Error")
    handler = Handler(request)
    handler.process()
