#!/usr/bin/python
#we cann't derive prive function which prefix with "__"
class MyBase:
    def __init__(self):
        pass
    
    def __my(self):
        print "base"

    def my(self):
        self.__my()


class MySub(MyBase):
    def __init__(self):
        pass
    
    def __my(self):
        print "sub"

myobj = MySub()
#myobj.__my() #run error
myobj.my() #print "base"
