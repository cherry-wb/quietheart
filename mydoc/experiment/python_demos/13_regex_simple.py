#!/usr/bin/python
#.*
#.*?
#\d
#\w
#.+
#\s
#\S
#()
#^
#$
import re
orig_string = 'This is a string with field (1)="f1" and (2)="f2" and (3)="f3" and boundary is "<>"'
regexp_greedy = r'^.*with field\s*\(\d+\)\s*=\s*"(?P<field1>\w+)".*\(\d+\)\s*=\s*"(?P<field2>\w+)".*is.*(?P<field3>"\S+").*$'
pattern = re.compile(regexp_greedy) #'.' is not '\n'
#pattern = re.compile(regexp_greedy,re.S) #this make '.' as any character.

###basic match
#match the whole string, then get specified substring.
match = pattern.match(orig_string)
if None == match:
    print "Not match."
    exit(1)

#the whole string is group 0
print "Whole string is:"
print match.group(0)

#refer group in "()" by group number:
print "group 1:"
print match.group(1)
#refer group by group name.
print "group field1:"
print match.group("field1")

print "group position:"
print "group 0 (whole string) start:",match.start(0) #first index of group0 in whole
print "group 1 start:",match.start(1) #first index of group1 in whole
print "group 1 end:",match.end(1) #end index of group1 in whole

###greedy and none greedy match.
# default greedy('.*' match as long as possible) so it is "f3" not "f2"
print "greedy group 2:"
print match.group(2)
#refer group by group name.
print "greedy group field2:"
print match.group("field2")

# nogreedy match('.*?' match not as long as possible) for "f2"
regexp_nogreedy = r'^.*with field\s*\(\d+\)\s*=\s*"(?P<field1>\w+)".*?\(\d+\)\s*=\s*"(?P<field2>\w+)".*is.*(?P<field3>"\S+").*$'
match = re.match(regexp_nogreedy,orig_string) #another way of match.
print "nogreedy group 2:"
print match.group(2)
#refer group by group name.
print "nogreedy group field2:"
print match.group("field2")

###search and other operations
#search a substring(pattern) and return the position.
wholeStr = "The content is: Hello pretty world! as whole string."
subStrPattern = re.compile(r"Hello.*world")
match = subStrPattern.search(wholeStr) #search the pattern in whole str
print "matched pattern is:",match.group() #gourp(0)
print "substr pattern start position in whole string:",match.start(0)

#split by regex
p = re.compile(r'\d+')
print p.split('one1two2three3four4')
