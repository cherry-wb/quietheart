#!/usr/bin/python
import random
import time

#random item from list:
#random.choice(list)
mydict = {"1":"one","2":"two","3":"three","4":"four"}
num = len(mydict.keys())
print "dict key is:",num

mydict["random"] = mydict[random.choice(mydict.keys())]
print mydict

#random num from int range[1,5]:
print random.randint(1,5)

#random number in [0,1)
print random.random()


#print "with seed:"
date = int(time.strftime("%Y%m%d",time.localtime()))#20120427
print date

random.seed(date) #seed canbe string, not only int
for i in range(1,10):
    print random.randint(1,100)
print "with same seed again:"
random.seed(date)
for i in range(1,10):
    print random.randint(1,100)

#print "with state"
print "continue:"
state = random.getstate()
for i in range(1,10):
    print random.randint(1,100)

print "continue with same previous init state again:"
random.setstate(state)
for i in range(1,10):
    print random.randint(1,100)
