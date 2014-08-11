#!/usr/bin/python

import gevent

def win():
    gevent.sleep(3)
    print "win out!"
    return 'You win!'

def fail():
    raise Exception('You fail at failing.')

winner = gevent.spawn(win)
loser = gevent.spawn(fail)

print "started:"
print(winner.started) # True
print(loser.started)  # True

print "value:"
print(winner.value) # 'You win!'
print(loser.value)  # None

print "ready:"
print(winner.ready()) # True
print(loser.ready())  # True

print "successful:"
print(winner.successful()) # True
print(loser.successful())  # False

while not winner.ready():
    print "not ready"
    gevent.sleep(1)
print (winner.value)

# Exceptions raised in the Greenlet, stay inside the Greenlet.
try:
    gevent.joinall([winner, loser])
except Exception as e:
    print('This will never be reached')

print "value:"
print(winner.value) # 'You win!'
print(loser.value)  # None

print "ready:"
print(winner.ready()) # True
print(loser.ready())  # True

print "successful:"
print(winner.successful()) # True
print(loser.successful())  # False

# The exception raised in fail, will not propogate outside the
# greenlet. A stack trace will be printed to stdout but it
# will not unwind the stack of the parent.

print(loser.exception)

# It is possible though to raise the exception again outside
# raise loser.exception
# or with
# loser.get()

