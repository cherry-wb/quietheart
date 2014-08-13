#!/usr/bin/python
import os
import sys 

support_type=['.py','.sh']
main_dir = sys.path[0]
scripts_dir = main_dir+os.sep+"scripts"

#print scripts_dir
#file_list = [scripts_dir + os.sep + i for i in os.listdir(scripts_dir)]
#print file_list
#file_list=os.listdir(main_dir)
#file_list.sort()
script_list = []

#walk the file with specified file extension.
def filter_type(support_type,dirname,fname):
    for i in fname:
        if os.path.isfile(dirname+os.sep+i) and (os.path.splitext(dirname+os.sep+i)[1] 
                in support_type):
            script_list.append(dirname+os.sep+i)
os.path.walk(scripts_dir+os.sep+"parser",filter_type,support_type)

script_list.sort()

for script in script_list:
    os.system(script)

