# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

import logging
import os
import time
import core.config as gconfig
from core.singleton import Singleton
from core.thread_local import ThreadLocal


_mylog = None

class MyLog(Singleton):

    def __init__(self):
        global _mylog

        if _mylog is None:
            self.logger = logging.getLogger('ACS')
            self.logger.setLevel(logging.DEBUG)

            console = logging.StreamHandler()
            formatter = logging.Formatter('%(name)-4s %(asctime)s %(levelname)-6s: %(message)s')
            console.setFormatter(formatter)
            self.logger.addHandler(console)

            fName = self.getLogFolder()
            fh = logging.FileHandler(fName)
            fh.setFormatter(formatter)
            self.logger.addHandler(fh)

            self.tlogger = ThreadLog.getInstance()

        _mylog = self


    def getLogFolder(self):
        logFolder = gconfig.LOG_PATH
        parentFolder = os.path.split(logFolder)[0]
        if not os.path.exists(parentFolder):
            os.mkdir(parentFolder)
        if not os.path.exists(logFolder):
            os.mkdir(logFolder)
        timeStamp = time.strftime('%Y%m%d%H%M',time.localtime(time.time()))
        logPath = logFolder + os.sep + "log_" + timeStamp
        return logPath


    def setLevel(self, level):
        self.level = level

        if level == 'debug':
            self.logger.setLevel(logging.DEBUG)
        elif level == 'info':
            self.logger.setLevel(logging.INFO)
        elif level == 'warning':
            self.logger.setLevel(logging.WARNING)
        elif level == 'error':
            self.logger.setLevel(logging.ERROR)
        else:
            self.logger.setLevel(logging.INFO)


    def debug(self, msg, *args, **kwargs):
        self.logger.debug(msg, *args, **kwargs)
        self.tlogger.debug(msg, *args, **kwargs)

    def info(self, msg, *args, **kwargs):
        self.logger.info(msg, *args, **kwargs)
        self.tlogger.info(msg, *args, **kwargs)

    def warning(self, msg, *args, **kwargs):
        self.logger.warning(msg, *args, **kwargs)
        self.tlogger.warning(msg, *args, **kwargs)

    def error(self, msg, *args, **kwargs):
        self.logger.error(msg, *args, **kwargs)
        self.tlogger.error(msg, *args, **kwargs)

    def dump(self):
        return self.tlogger.dump()


    @staticmethod
    def getMyLog():
        global _mylog
        if _mylog is None:
            _mylog = MyLog()
        return _mylog



"""
Collect log for every ACS request
"""
_threadlog = None

class ThreadLog():

    LOG_KEY = 'LOG'

    def __init__(self):
        """
        """

    def append(self, msg):
        tlocal = ThreadLocal.getInstance()

        tobj = tlocal.get()
        if not tobj.has_key(self.LOG_KEY):
            tobj[self.LOG_KEY] = []

        tlog = tobj[self.LOG_KEY]
        tlog.append(msg)

    def debug(self, msg, *args, **kwargs):
        self.append(msg)

    def info(self, msg, *args, **kwargs):
        self.append(msg)

    def warning(self, msg, *args, **kwargs):
        self.append(msg)

    def error(self, msg, *args, **kwargs):
        self.append(msg)

    def dump(self):
        tlocal = ThreadLocal.getInstance()
        tobj = tlocal.remove()
        logs = tobj.get(self.LOG_KEY, ['No server log'])
        return "\n".join(logs)


    @staticmethod
    def getInstance():
        global _threadlog
        if _threadlog is None:
            _threadlog = ThreadLog()
        return _threadlog

