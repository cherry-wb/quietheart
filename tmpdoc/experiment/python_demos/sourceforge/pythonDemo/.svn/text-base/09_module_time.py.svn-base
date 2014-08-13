#!/usr/bin/python
import time

gmtime = time.gmtime() #8 hours early than localtime
print "gmtime:"
print gmtime
print

localtime=time.localtime()
print "localtime:"
print localtime
print

asctime = time.asctime()
print "asctime:"
print asctime
print

thetime = time.time()
print "time:"
print thetime
print

print localtime.tm_year
print localtime.tm_mon
print localtime.tm_mday
print localtime.tm_hour
print localtime.tm_min
print localtime.tm_sec
print

formatstr = "%Y-%m-%d---%H:%M:%S"
timestr = time.strftime(formatstr,localtime) #also can be gmtime
print timestr
print

customTime=time.strptime("18:18:18", "%H:%M:%S")
print "customTtime:"
print customTime
print

#for compute
utcRawTime = time.time()
print "utc raw time:",utcRawTime
cLocalTime = time.localtime(utcRawTime)
print "convert from raw time:",cLocalTime
cLocalTime = time.localtime(utcRawTime-303)
print "convert from raw time minus 303 seconds:",cLocalTime

inputTime =time.strptime("18:18:18", "%H:%M:%S")
print "input time:",time.strftime("%H:%M:%S",inputTime)
rawTime = time.mktime(inputTime)
print "conver input to raw:",rawTime
rawTime = rawTime - 305
print "minus raw by 305 seconds:",rawTime
changedTime = time.strftime("%H:%M:%S",time.localtime(rawTime))
print "after changed input time:",changedTime
