#!/usr/bin/python
import sys
def run():
    print __name__+":"+run.__name__
    print "in pkg1, path is: ",sys.path

if __name__=="__main__":
    print "This print when execute the module but not import.often put module test code here."
