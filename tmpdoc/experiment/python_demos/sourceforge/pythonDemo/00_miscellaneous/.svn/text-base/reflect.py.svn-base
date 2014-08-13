#!/usr/bin/python
import os
#a file contains python code, exec the code here:
file_path="./myfile.py"
if os.path.exists(file_path):
    exec open(file_path, 'r').read() #execute the python file 'myfile.py''s code.

class MyClass(object):
    def __init__(self):
        print "haha"

#translate a string to a class
class_name = "MyClass"
objclass = eval(class_name)
objclass() #print haha
