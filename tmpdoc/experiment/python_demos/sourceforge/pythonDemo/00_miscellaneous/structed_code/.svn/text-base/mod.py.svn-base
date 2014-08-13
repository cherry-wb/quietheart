#!/usr/bin/python
'''
directory:
./mod.py
./sub1/mod1.py
./sub2/mod2.py
./package/__init__.py
./package/pkg1.py
./package/pkg2.py

1,for mod:
mod add the "sub1", "sub2" directory to path,
mod can import the sub1/mod1,
mod can import the sub2/mod2
mod call mod2.run()

2,then:
2.1,for mod2:
mod2 can import mod1 directly.
then mod2.run() can call mod1.run()

2.2,for mod1:
mod1 can import package.pkg1 directly.
mod1 can import package.pkg2 directly.
mod1.run() can call package.pkg1.run() and package.pkg2.run()

3,but:
for mod1 and mod2:
they cann't import each other, and package.* when directly run them.

i.e. 
If a module is imported, it can use the same path as its main module's.
If a module is executed by itself, it's another main module and use its own path.
'''
import sys
import os

print __name__
sys.path.append(sys.path[0]+os.sep+"sub1")
sys.path.append(sys.path[0]+os.sep+"sub2")
import mod1
import mod2
print "in main, path is: ",sys.path
mod2.run()
