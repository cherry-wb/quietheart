#!/usr/bin/python
import traceback
'''Simple use of custom exception'''
class MyException1(Exception):
    def __init__(self,msg="MyException1 occured!"):
        self.msg = msg

    def __str__(self):
        return repr(self.msg)

class MyException2(Exception):
    def __init__(self,msg="MyException2 occured!"):
        self.msg = msg

    def __str__(self):
        return repr(self.msg)

def myfunc1(p1,p2):
    '''exception(MyException1) if p1 / p2 < 0.
       '''
    c = p1 / p2
    if c < 0:
        raise MyException1("occured exception1 in myfunc1!")

def myfunc2():
    '''exception(MyException2) forever.
       '''
    try:
        c = 5 / 0 
    except Exception,e:
        print repr(e)
        raise MyException2("occured exception2 in myfunc2!")

if "__main__" == __name__:
    try:
#We can comment the other two to see special exception.
        myfunc1(1,-2) #exception 1
        myfunc2() #exception 2
        myfunc2(1,2) #other exception parameter error.
    except (MyException1,MyException2),e:
        traceback.print_exc() #print trace back
        print e
    except Exception,e:
        print "other exception:", e
