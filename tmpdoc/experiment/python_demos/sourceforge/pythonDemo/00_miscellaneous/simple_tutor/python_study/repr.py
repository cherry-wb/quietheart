#!/usr/bin/python
# Filename:repr.py

i = ['item']
#i.append('item')
print 'declare is:i = [\'item\']'
print '---result of print \'`i`\'------:'
print `i`
print '---result of print \'repr(i)\'------:'
print repr(i)
print '---result of print \'eval(repr(i))\'------:'
print eval(repr(i))
print '---result of print \'i\'------:'
print i
print '---end------'
