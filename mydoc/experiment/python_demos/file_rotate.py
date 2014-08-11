#!/usr/bin/python
import os
import logging

num = 5
fName = "mylog"
for i in range(0,num):
    n = num - i
    if os.path.exists(fName+"."+str(n)):
        if n < num:
            os.rename(fName+"."+str(n),fName+"."+str(n+1))

if os.path.exists(fName):
    os.rename(fName,fName+"."+str(1))

logger = logging.getLogger('mytest')
fh = logging.FileHandler(fName)
logger.addHandler(fh)

formatter = logging.Formatter('%(name)-6s %(astime)-8s: %(message)s')
fh.setFormatter(formatter)

logger.info("hello")
