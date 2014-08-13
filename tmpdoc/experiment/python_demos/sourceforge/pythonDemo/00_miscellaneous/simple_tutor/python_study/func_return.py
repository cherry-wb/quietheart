#!/usr/bin/python
# Filename: func_return.py

def maximum(x,y):
	if x > y:
		print 'x is more than y'
		return x
	elif x < y:
		print 'y is more than x'
		return y
	else:
		print 'x is equal to y'
		return None

def nothing():
	pass
print maximum(2,2)
print maximum(2,3)
print nothing()#output None
#print nothing #this output the address of the function none
#print good#error! can't print string so,or it will be an undefined var
#print None#the None can print like this!
