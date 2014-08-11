#!/usr/bin/python

def fun(arg1, arg2=None):
    print arg1
    print arg2

def mydebug(*args, **kargs):
    print "-"*10
    fun(args[0],kargs.get("arg2",None))
    print "-"*10
    fun(args[0],**kargs)
    print "-"*10
    fun(*args,**kargs)
    print "-"*10

mydebug("arg1","arg2")
mydebug("arg1",arg2 = "arg2")

