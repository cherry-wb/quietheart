#!/usr/bin/python
import threading
import time

def func1(num):
    for i in range(0,num): #[0,num)
        print func1.__name__,
        print "thread id:",threading.currentThread().ident
        print ":",i
        time.sleep(1)

def func2(num):
    for i in range(0,num): #[0,num)
        print func2.__name__,
        print ":",i
        time.sleep(1)

if "__main__" == __name__:
#func1(5)
#func2(5)
    t1 = threading.Thread(target=func1,args=(5,))
    t2 = threading.Thread(target=func2,args=(5,))

    print "main thread get sub thread1 start before id:", t1.ident #None

    t1.start()
    t2.start()

    print "main thread get sub thread1 started id:", t1.ident
    t1.join() #wait t1 end.
    t2.join() #wait t2 end.

    print "main thread end!"
