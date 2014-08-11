#!/usr/bin/python
import random

char_list=[]
#number
for i in range(48,58):
    char_list.append(chr(i))

#upper
for i in range(65,91):
    char_list.append(chr(i))

#lower
for i in range(97,123):
    char_list.append(chr(i))

print char_list

random_list = random.sample(char_list,6)
random_str = "".join(random_list)

print random_str

print ''.join(random.sample([chr(i) for i in range(48, 123)], 8))
