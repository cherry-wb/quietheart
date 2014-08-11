#!/usr/bin/python
myList = [('a',1,'a1'),('b',2,'b2'),('c',3,'c3')]
print "item1,item2,item3"
for item1,item2,item3 in myList:
    print "1:",item1,",2:",item2,",3:",item3

for item in myList:
    print item

#for item1,item2 in myList:#Error
#    print "1:",item1,",2:",item2
