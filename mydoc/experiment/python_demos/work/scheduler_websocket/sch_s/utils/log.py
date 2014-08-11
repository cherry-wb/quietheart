# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

import logging

import core.config as gconfig
from core.singleton import Singleton


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

            fName = gconfig.LOG_FILE
            fh = logging.FileHandler(fName)
            fh.setFormatter(formatter)
            self.logger.addHandler(fh)

        _mylog = self


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

    def info(self, msg, *args, **kwargs):
        self.logger.info(msg, *args, **kwargs)

    def warning(self, msg, *args, **kwargs):
        self.logger.warning(msg, *args, **kwargs)

    def error(self, msg, *args, **kwargs):
        self.logger.error(msg, *args, **kwargs)


    @staticmethod
    def getMyLog():
        global _mylog
        if _mylog is None:
            _mylog = MyLog()
        return _mylog


