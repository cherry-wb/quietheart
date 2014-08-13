#!/usr/bin/python
import sys
def print_arg():
	'''Print the arguments of command.

	if runs alone, print arguments of command;
	if imported as a module don't print command arguments.'''
	for arg in sys.argv:
		print arg

if __name__ == "__main__":
	argc=len(sys.argv)
	print "the argument count is:%d" %(argc-1)
	if argc < 2:
		print print_arg.__doc__
		print "At least one argument needed."
		exit(1)
	else:
		print_arg()
