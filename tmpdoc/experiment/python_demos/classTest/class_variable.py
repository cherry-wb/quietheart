#!/usr/bin/python

class MyClass:
    a = 1
    count = 0

    def __init__(self):
        print "__init__ count:",MyClass.count
        self.a = self.a+1
        self.test = MyClass.a
        MyClass.count += 1
        self.num = MyClass.count


class MyClass2:
    my = MyClass()
    print "Hello, declaration of MyClass2"

if __name__ == "__main__":
    my1 = MyClass()
    print my1.a #2
    print my1.test #1
    print my1.num #2

    my2 = MyClass()
    print my2.a #2
    print my2.test #1
    print my2.num #3

    my3 = MyClass()
    print my3.a #2
    print my3.test #1
    print my3.num #4

    myc = MyClass2()
    print myc.my.num #1
