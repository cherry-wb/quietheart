#!/usr/bin/python
#Two method for generate a list whose item is all possible permutation and combination come from every item of many list.

A = ['1', '2']
B = ['a', 'b', 'c']
C = ['A', 'B', 'C', 'D']

retList = []
for a in A:
    for b in B:
        for c in C:
            retList.append((a,b,c))
print retList
    
print '*' * 40

def myfunc(*lists):
    #list all possible composition from many list, each item is a tuple.
    #Here lists is [list1, list2, list3], return a list of [(item1,item2,item3),...]

    #len of result list and result list.
    total = reduce(lambda x, y: x * y, map(len, lists))
    retList = []

    #every item of result list.
    for i in range(0, total):
        step = total
        tempItem = []
        for l in lists:
            step /= len(l)
            tempItem.append(l[i/step % len(l)])
        retList.append(tuple(tempItem))

    return retList

print myfunc(A,B,C)
