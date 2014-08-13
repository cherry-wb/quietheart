#!/usr/bin/python
import os
import sys
import getopt

def show_help():
	print "NAME"
	print "    %s - Run the test case." % sys.argv[0]
	print
	print "SYNOPSIS"
	print "    %s [ [-h] | [-d <path>] [-l <level>] ]" % sys.argv[0]
	print
	print '''DESCRIPTION
    Options:
    -d PATH,--directory=PATH
          Specify directory.

    -l LEVEL,--level=LEVEL
          Log level. Available levels as below:
          - warning
          - info (default)
          - debug

    -h,--help
          Print this help.
	'''
	print
	print "EXAMPLE"
	print "    $%s -d ./directory -l debug" % sys.argv[0]
	sys.exit(1)

######Main function.######
''' show usage of getopt function for command line arguments.
	'''
if __name__ == "__main__":
	case_dir = "cases"
	try:
		opts, args = getopt.getopt(sys.argv[1:], 'hd:l:', ['help','directory=','level='])
		print "input options: ", opts
		print "input arguments: ", args
	except getopt.GetoptError:
		show_help()

	for o,v in opts:
		print "option:",o
		print "argument:",v
		if o in ('-h', '--help'):
			show_help()
		elif o in ('-d', '--directory'):
			case_dir = v
			print case_dir
		elif o in ('-l', '--level'):
			level = v
			print level
