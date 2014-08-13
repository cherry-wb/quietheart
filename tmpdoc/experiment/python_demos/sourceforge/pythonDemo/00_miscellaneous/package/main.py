#!/usr/bin/python
#every package dir must have "__init__.py"
#if use '*' for import, we should edit __init__.py and add module to __all__.
#I found that we can add package name to __all__.
from sub1.sub11 import *
cls1.cls11()

import sub1.sub12.cls2
sub1.sub12.cls2.cls12()
