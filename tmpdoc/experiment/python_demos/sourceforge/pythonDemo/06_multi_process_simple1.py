#!/usr/bin/python
r'''
The child process's source code is:
==========
#!/usr/bin/python
import time
import sys
def run(procName,num):
    for i in range(0,num):
        print procName+":",
        print i+1
        time.sleep(1)

if "__main__" == __name__:
    run(sys.argv[1],5)
==========
'''
import subprocess
import sys

def run():
    print "main process."
    processes = []

#run childprocess
    for i in range(0,5):
        cmd = "./process1.py"
        arg1 = "name" + str(i)
        cmdList = ["./process1.py", arg1]
        p = subprocess.Popen(cmdList,stdout=sys.stdout)
        processes.append(p)

#check child status.
    for p in processes:
       ret_code = p.poll() #None:not complete, negative:terminal by signal, positive:return value.
       print p.pid,"return code:",ret_code

#wait process and get the status
    processes[0].wait() #if wait, we cann't get the status by poll() again.
    print "main process end." #Child process may still run.

if "__main__" == __name__:
    run()
