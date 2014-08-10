#!/usr/bin/python
# Filename: func_default.py

def say(message, times = 1):
	#times = 3#we can change the default times here
	#print 'hi,' * 3#output: hi,hi,hi
	#print 3*3#output: 9
	print message * times

say('Hello')
say('World', 5)
