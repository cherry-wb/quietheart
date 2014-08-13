#!/usr/bin/python
'''Many small tips.
'''
import sys
import time
import random

###output redirect
print >>sys.stderr, "test error put"
print >>sys.stdout, "test output"

###init many variable, at one time
(a,b,c)=("init","variable","by tuple")
print a
print b
print c

a,b=3,2
print a
print b

a,b = b,a
print a
print b

###flush
#for i in range(0,2):
#    print i+1,
#    sys.stdout.flush() #flush explicitly
#    time.sleep(1)
#print #flush when meet the end of line.

###random
num = random.choice([1,2,3,4,5])
print num

num = random.randint(0,3) #[0,3]
print num

###defination after run or before run. defination after definataion.
def func1():
    print func1.__name__
    func2()

#func1() #run error

###function tips
def func2():
    print func2.__name__

def funcx(a,b,c=1,d=2):
    print a
    print b
    print c
    print d

func1() #good
funcx(1,2,d=3) #1213

### short condition in one sentence
itemId = "true" if 0 else 'false'

dic = {"key1":1,"key2":2}
a = dic["key1"] if dic.has_key("key1") else 0
print a #1
a = dic["key3"] if dic.has_key("key3") else 0
print a #0

print "call func1:"
func1() if 1 else ""

print "not call func1:"
func1() if 0 else ""

print "not print" if 0 else None
print "print" if 1 else None

print "helloworle!!!!" if 1>2 else "hehehe"

###assert
print "assert 2>1"
assert 2 > 1 #ok
print "assert 'str1' == 'str2'"
assert 'str1' == 'str1' #ok

str1 = "hello"
assert "hello" == str1

#print "assert 1>3"
#assert 1 > 3
print itemId

###merge dict
dict1={1:"1"}
dict2={2:"2"}

dict12=dict(dict1,**dict2)

dict122=dict1.copy()
dict122.update(dict2)

dict123=dict(dict1.items()+dict2.items())

###characters
#number
for i in range(48,58):
    print chr(i)

#upper
for i in range(65,91):
    print chr(i)

#lower
for i in range(97,123):
    print chr(i)


mystr = ("" or 1)
print mystr #1
