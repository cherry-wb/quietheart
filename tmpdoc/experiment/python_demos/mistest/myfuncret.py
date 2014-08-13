#!/usr/bin/python

def func1():
    mylist = [1,2,3]
    return tuple(mylist)

def func2():
    mylist = [1]
    return tuple(mylist)

a = func1()
print a
#print a+1 #error

a = func2()
print a
#print a+1 #error
