#!/usr/bin/python
import itertools
mylist = [1,2,3,4,5,4,3,2,1,]

for i in mylist:
    if i > 2:
        mylist.remove(i)
        print "remove:",i

print mylist

mylist = ["hello", "world!"]
s1,s2 = mylist
print s1 #hello
print s2 #world!

list2 = []
list2.extend(["content:%s" %content] for content in mylist)
print "list2:",list2
flat = list(itertools.chain(*list2))#flat each sub list 
print "flat:",flat

list2.extend("content:%s" %content for content in mylist)
print "list2:",list2
flat = list(itertools.chain(*list2))
print "flat:",flat

flat.extend(["aha"])
print "flat:",flat
