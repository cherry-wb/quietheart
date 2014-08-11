#!/usr/bin/python
mylist = [1,2,3,4,5,4,3,2,1,]

for i in mylist:
    if i > 2:
        mylist.remove(i)
        print "remove:",i

print mylist
