#!/usr/bin/python
# Filename: break.py

while True:
	s = raw_input('Enter something:')
	if s == 'quit':
		break
	print 'Length of the string is', len(s), '\n'
else:
	print "won't run here when break!\n"
print 'Done'
