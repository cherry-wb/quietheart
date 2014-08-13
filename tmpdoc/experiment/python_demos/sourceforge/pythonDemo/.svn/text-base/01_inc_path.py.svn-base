#!/usr/bin/python
import sys
import os

#current path of this module.
print sys.path[0]

#add current path to system path
sys.path.append(sys.path[0])

#mod.py content is:
#!/usr/bin/python
#import sys
#print sys.path
#print 'hello!'

#import module and then the module can contain the current added before.
#despite import 3 times but only load("exec") one time.
import mod
import mod
import mod

#system the module but the path add before cann't see in module.
os.system("./mod.py")
