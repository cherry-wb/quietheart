#!/usr/bin/python
class Singleton(object):
    _state = {}
    def __new__(cls, *arg, **kw):
        #print cls.__class__ #type
        if not cls._state.has_key(cls):
            cls._state[cls] = super(Singleton, cls).__new__(cls, *arg, **kw)
            #print "+++",cls._state[cls].__class__ #Singleton
        return cls._state[cls]


class Factory(Singleton):
    __instance = None
    def __init__(self):
        if not hasattr(self,'count'):
            self.count = 0
        Factory.__instance = self #still the same object.

    def refCount(self):
        self.count += 1
        print "self.count:%s" %self.count

    @staticmethod
    def getInstance():
        return Factory.__instance

if "__main__" == __name__:
    print "obj = Factory();obj.refCount() two times."
    f = Factory()
    f.refCount() #1

    g = Factory()
    g.refCount() #2

    print "Factory().refCount() two times."
    Factory().getInstance().refCount() #3
    Factory().getInstance().refCount() #4

    print "Factory.getInstance().refCount() two times."
    Factory.getInstance().refCount() #5
    Factory.getInstance().refCount() #6
