#!/usr/bin/python
# Filename: func_local.py
def func(x):
	print 'local x is:', x
	x = 2;
	print 'changed local x to:', x#the comma of the print must need

x = 50
func(x)
print 'global x is still:', x
