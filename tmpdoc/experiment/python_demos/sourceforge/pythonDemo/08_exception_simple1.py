#!/usr/bin/python
'''Simple use of standard exception'''
try:
    a = 5
    b = 0
    c = a/b
except:
    print "==========="
    print "catch all kinds of error, better not use this way."
    print "==========="
finally:
    print "will excute no matter whether there's some error."

try:
    a = 5
    b = 0
    c = a/b
except Exception:
    print "==========="
    print "catch all kinds of error, better use this way."
    print "==========="

try:
    a = 5
    b = 0
    c = a/b
except IOError:
    print "==========="
    print "catch IOError."
    print "==========="
except Exception:
    print "==========="
    print "catch other error after IOError."
    print "==========="

try:
    a = 5
    b = 1
    c = a/b
except Exception:
    print "==========="
    print "catch all kinds of error, better use this way."
    print "==========="
else:
    print "Reach here if there's no exception."

try:
    a = 5
    b = 1
    c = a/b
except Exception:
    print "==========="
    print "catch all kinds of error, better use this way."
    print "==========="
else:
    print "Reach here if there's no exception."
finally:
    print "will excute no matter whether there's some error."

try:
    a = 5
    b = 0
    c = a/b
finally:
    print "_will excute no matter whether there's some error."
    print "and then give the exception to upper."



print "no try catch."
