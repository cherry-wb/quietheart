#!/usr/bin/python

#@deco2
#@deco1
#def func(arg1, arg2, ...): pass
#This equals to :
#def func(arg1, arg2, ...): pass
#func = deco2(deco1(func))

###Simple
def decor1(func):
    def wrapperFunc():
        print "wrapper1's code before %s" %func.__name__
        func()
        print "wrapper1's code after %s" %func.__name__
    return wrapperFunc

@decor1
def myFunc1():
    print "myFunc1's code"

myFunc1()


###Decorated function with arguments.
def decor2(func):
    def wrapperFunc(a,b):
        print "before call %s" %func.__name__
        func(a,b)
        print "after call %s" %func.__name__
    return wrapperFunc

@decor2
def myFunc2(a,b):
    print "myFunc2's code, argument:%d %d" %(a,b)

myFunc2(1,2)



###Decorated function have variable arguments.
def decor3(func):
    def wrapperFunc(*args,**kargs):
        print "before call %s" %func.__name__
        func(*args,**kargs)
        print "after call %s" %func.__name__
    return wrapperFunc

@decor3
def myFunc3(a,b):
    print "myFunc3's code, argument:%d %d" %(a,b)

@decor3
def myFunc4(a,b,c):
    print "myFunc4's code, argument:%d %d %d" %(a,b,c)

myFunc3(1,2)
myFunc4(3,4,5)


###Decorating function have arguments.
def decor4(arg):
    def _decor4(func):
        def __decor4():
            print "wrapper1's code before %s, with arg:%s" %(func.__name__,arg)
            func()
            print "wrapper1's code after %s, with arg:%s" %(func.__name__,arg)
        return __decor4
    return _decor4

@decor4("test")
def myFunc5():
    print "myFunc5's code"

myFunc5()

class MyClass():
    def __init__(self):
        pass

    @decor3
    def myfunc(self):
        print "in myfunc of class"

    @decor3
    def myfunc2(self,a):
        print "in myfunc2 of class"

MyClass().myfunc()
MyClass().myfunc2(1)
