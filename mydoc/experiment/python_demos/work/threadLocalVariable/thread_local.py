# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

import threading

from core.singleton import Singleton

_instance = None

class ThreadLocal(Singleton):
    def __init__(self):
        global _instance
        if _instance is None:
            self.values = {}
        _instance = self

    def get(self):
        thread = threading.currentThread()
        ident = thread.ident
        if self.values.has_key(ident):
            value = self.values[ident]
        else:
            value = self.initValue()
            self.values[ident] = value
        return value


    def set(self, value):
        thread = threading.currentThread()
        ident = thread.ident
        self.values[ident] = value


    def remove(self):
        thread = threading.currentThread()
        ident = thread.ident
        if self.values.has_key(ident):
            return self.values.pop(ident)
        else:
            return {}


    def initValue(self):
        return {}


    @staticmethod
    def getInstance():
        global _instance
        if _instance is None:
            _instance = ThreadLocal()
        return _instance

