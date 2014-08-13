#!/usr/bin/python
import random
from random import Random
import time

class DateRandom(Random):
    '''Generate Random sequence by date.
       '''
    def __init__(self):
        Random.__init__(self)
        self.dateSeed = time.strftime("%Y%m%d",time.localtime())
        Random().seed(self.dateSeed)

    def seed(self,s=None):
        print "seed in me"
        if None != s:
            self.dateSeed = s
            Random().seed(s)
        else:
            self.dateSeed = time.strftime("%Y%m%d",time.localtime())
            Random().seed(self.dateSeed)

myrandom = DateRandom()
for i in range(1,10):
    print myrandom.randint(1,100)

print "with same seed again:"
myrandom.seed()
for i in range(1,10):
    print myrandom.randint(1,100) #not the same

#print "with state"
print "continue:"
state = myrandom.getstate()
for i in range(1,10):
    print myrandom.randint(1,100)

print "continue with same previous init state again:"
myrandom.setstate(state)
for i in range(1,10):
    print myrandom.randint(1,100)

print "with another seed:"
myrandom.seed(1000)
for i in range(1,10):
    print myrandom.randint(1,100)

print "with another same seed:"
myrandom.seed(1000)
for i in range(1,10):
    print myrandom.randint(1,100) #not the same
