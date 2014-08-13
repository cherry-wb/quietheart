#!/usr/bin/python
'''
directory:
./mod.py
./sub1/mod1.py
./sub2/mod2.py
./package/__init__.py
./package/pkg1.py
./package/pkg2.py
./package/subpkg/__init__.py
./package/subpkg/subpkg1.py
./package/subpkg/subpkg2.py

'''
import sys
import os

print __name__
sys.path.append(sys.path[0]+os.sep+"sub1")
sys.path.append(sys.path[0]+os.sep+"sub2")

#import package name
import package
package.subpkg1() #use this because subpkg1 was imported by package/__init__.py

import mod2
package.pkg1.run() #can use this because mod2 do 'import package.pkg1'
