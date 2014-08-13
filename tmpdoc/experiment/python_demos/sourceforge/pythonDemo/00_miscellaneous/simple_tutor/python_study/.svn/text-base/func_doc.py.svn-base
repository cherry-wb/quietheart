#!/usr/bin/python
# Filename: func_doc.py

def printMax(x,y):
	'''prints the maximum of two numbers.

	The two values must be integers.'''#this is a standard doc
	x = int(x)# convert to integers, if possible
	y = int(y)
	if x > y:
		print x, 'is maximum'
	else:
		print y, 'is maximum'
def testDoc1():
	'''this is a test1 to see if this doc is right'''#this is right
	pass
def testDoc2():
	'this is a test2 to see if this doc is right'#this is right
	return#equal to the return None
def testDoc3():
	print 'test'
	'this is a test3 to see if this doc is right'#no error,but not right
def testDoc4():
	'this is a test2 to see if this doc is right'#this is right
	'second line to see if it is right'#no error,but not doc here
	return#equal to the return None

print printMax(3,5)
print printMax.__doc__#this is a standard doc
print testDoc1.__doc__#this is right
print testDoc2.__doc__#this is right
print testDoc3.__doc__#the output is None
print testDoc4.__doc__#out put is the same as testDoc2
help(printMax)#this call the help function press 'q' to quit.
