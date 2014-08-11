#!/usr/bin/python
import os
if __name__ == "__main__":
    startServer = './manage.py run_gunicorn \
    -k "geventwebsocket.gunicorn.workers.GeventWebSocketWorker"'
    os.system(startServer)

