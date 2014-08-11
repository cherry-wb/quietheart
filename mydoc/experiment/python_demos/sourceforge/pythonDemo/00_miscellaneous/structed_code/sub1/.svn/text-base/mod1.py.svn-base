#!/usr/bin/python
import sys
import package.pkg1
import package.pkg2
def run():
    print __name__+":"+run.__name__
    print "when run, path is:",sys.path[0]#this is the main path.
    package.pkg1.run()
    package.pkg2.run()

print __name__, " imported"#this print when import but only at the first time it imported.
print "path is:",sys.path[0]#this is the main path.

if __name__=="__main__":
    print "This print when execute the module but not import.often put module test code here."
