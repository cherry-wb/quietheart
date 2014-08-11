#!/usr/bin/python
mystr="hello,world!"

#find substring or return -1
print mystr.find("world") #6
print mystr.find("worldd") #-1

#split
print mystr[:2] #he
print mystr[2:] #llo,world!
print mystr[:-2] #hello,worl

#split to list
myip="192.168.0.1"
print myip.split('.') #['192', '168', '0', '1']
print myip.split('.',2) #['192', '168', '0.1']
print myip.split('.')[0] #192
print myip.split('.')[1] #168
print myip.split('.')[2] #0
print myip.split('.')[3] #1

print myip.strip("12") #92.168.0.  (remove chars in params from head and trail)

print myip.replace(".",":") #192:168:0:1

if "hello,world!" == mystr:
    print "equal!"

