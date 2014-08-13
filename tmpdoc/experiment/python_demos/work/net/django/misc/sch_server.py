from gevent import monkey; monkey.patch_all()
from django.core.management import setup_environ
from django.core.handlers.wsgi import WSGIHandler as DjangoWSGIApp

from sch_s import settings
from ws.urls import ws_connector


"""
python manage.py run_gunicorn  -k "geventwebsocket.gunicorn.workers.GeventWebSocketWorker"
gunicorn -b 0.0.0.0:7000 -k "geventwebsocket.gunicorn.workers.GeventWebSocketWorker" sch_server:runserver
"""
def runserver(environ, start_response):
    if ws_connector(environ) != True:
        # If environment is not WebSocket, then call django server
        setup_environ(settings)
        application = DjangoWSGIApp()
        return application.__call__(environ, start_response)
