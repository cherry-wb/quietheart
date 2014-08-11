#!/usr/bin/python
import package.pkg1
import package.pkg2
def run():
    print __name__+":"+run.__name__
    package.pkg1.run()
    package.pkg2.run()

print __name__, " imported"#this print when import but only at the first time it imported.

if __name__=="__main__":
    print "This print when execute the module but not import.often put module test code here."
