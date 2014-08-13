#!/usr/bin/python
class MyBase(object):
    def __init__(self):
        pass

    def __myfunc(self):
        print "in MyBase __myfunc"

    def _myfunc(self):
        print "in MyBase _myfunc"

    def myfunc(self):
        print "in MyBase myfunc"
        self.__myfunc()
        self._myfunc()

class MySub1(MyBase):
    def __myfunc(self):
        print "in MySub1 __myfunc"
        super(MySub1,self).__myfunc()

    def myfunc(self):
        print "in MySub1 myfunc"
        self.__myfunc() #wrong

class MySub2(MyBase):
    def __myfunc(self):
        print "in MySub2 __myfunc"

    def _myfunc(self):
        print "in MySub2 _myfunc"

class MySub3(MyBase):
    def __myfunc(self):
        print "in MySub3"

    def _myfunc(self):
        print "in MySub3 _myfunc"

    def myfunc(self):
        print "in MySub3 myfunc"
        MyBase.myfunc(self)

base = MyBase()
base.myfunc() #in MyBase, MyBase2

#sub1 = MySub1()
#sub1.myfunc() #wrong

sub2 = MySub2()
sub2.myfunc() #MyBase::myfunc,MyBase::__myfunc,MySub2::_myfunc

sub3 = MySub3()
sub3.myfunc() #in MySub3::myfunc,MyBase::myfunc,MyBase::__myfunc,MySub3::_myfunc
