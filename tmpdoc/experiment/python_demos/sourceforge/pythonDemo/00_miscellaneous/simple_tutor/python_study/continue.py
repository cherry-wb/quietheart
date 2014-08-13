#!/usr/bin/python
# Filename: continue.py

while True:
	s = raw_input('Enter something: ')
	if s == 'quit':
		break
	if len(s) < 3:
		print 'not enough length\n'
		continue
	print 'Input is of sufficient length'
print 'done\n'
