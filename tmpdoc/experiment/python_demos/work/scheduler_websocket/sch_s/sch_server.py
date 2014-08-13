#!/usr/bin/python
import os
if __name__ == "__main__":
    startServer = 'python manage.py run_gunicorn -k "geventwebsocket.gunicorn.workers.GeventWebSocketWorker" -b 0.0.0.0:9000'
    os.system(startServer)
