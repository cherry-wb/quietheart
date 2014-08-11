#!/usr/bin/python
import time
import sys
def run(procName,num):
    for i in range(0,num):
        print procName+":",
        print i+1
        time.sleep(1)

if "__main__" == __name__:
    run(sys.argv[1],5)
