#!/usr/bin/python
import os
class Mem(object):
    Attri="aaa"

class A(object):
    def __init__(self):
        self.aaa = "BBB"

print Mem.Attri
a = A()
print a.aaa

print eval("a."+Mem.Attri)


os.close(os.open("testaaa",'w'))
