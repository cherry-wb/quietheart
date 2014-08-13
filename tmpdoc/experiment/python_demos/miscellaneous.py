#!/usr/bin/python
import os
import sys

support_type=['.py','.sh']
main_dir = sys.path[0]
scripts_dir = main_dir+os.sep+"scripts"+os.sep+"parser"

print scripts_dir
file_list = [scripts_dir + os.sep + i for i in os.listdir(scripts_dir)]
print file_list
#file_list=os.listdir(main_dir)
file_list.sort()
script_list = []
for i in file_list:
	if os.path.isfile(i) and (os.path.splitext(i)[1] in support_type):
		print os.path.splitext(i)[1]
		script_list.append(i)
print "after filter: ", script_list


def filter_type(arg,dirname,fname):
