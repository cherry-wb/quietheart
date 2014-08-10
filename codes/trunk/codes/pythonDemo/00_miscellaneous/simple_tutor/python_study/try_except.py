#!/usr/bin/python
# Filename: try_except.py

import sys

try:
	s = raw_input('Enter something -->')
except EOFError:
	print '\n Why did you do an EOF on me?'
	sys.exit()#exit the program
except:
	print '\nSome error/exception occurred.'#if you press <C-c>this is print
#here, we are not exiting the program

print 'Done'#if you print <C-c>this is also print but if you press <C-d>at first this will not print
