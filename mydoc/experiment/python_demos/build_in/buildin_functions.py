#!/usr/bin/python

def add_one(integer):
    return integer+1

def f(i1,i2):
    return i1+i2

r1 = map(None,[1,2,3],[4,5,6],[7,8])
print r1 #[(1, 4, 7), (2, 5, 8), (3, 6, None)]

r1 = map(None,[1,2,3])
print r1 #[1,2,3]

r1 = map(add_one,[1,2,3])
print r1 #[2,3,4]

r1 = map(f,[1,2,3],[4,5,6])
print r1 #[5,7,9]
