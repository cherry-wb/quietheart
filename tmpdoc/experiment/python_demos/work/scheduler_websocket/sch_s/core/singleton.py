# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

class Singleton(object):
    _state = {}

    def __new__(cls, *arg, **kw):
        if not cls._state.has_key(cls):
            cls._state[cls] = super(Singleton, cls).__new__(cls, *arg, **kw)
        return cls._state[cls]

