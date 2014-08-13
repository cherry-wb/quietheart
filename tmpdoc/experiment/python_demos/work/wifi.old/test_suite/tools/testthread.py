#!/usr/bin/python
import sys
import os
import threading
factoryLock = threading.Lock()

if "__main__" == __name__:
    s_fname = sys.path[0]
    main_dir = s_fname
    if main_dir.find("test_suite") != -1:
        while os.path.basename(main_dir) != "test_suite":
            main_dir = os.path.dirname(main_dir)
    else:
        print "Path error, not in 'scripts'."
        exit(1)
    sys.path.insert(0,main_dir)
    scripts_dir = main_dir + os.sep + "scripts"
    sys.path.insert(1,scripts_dir)

import scripts.parser.parser_api as parser_api
from scripts.factory_class import FactoryScenario
import scripts.lib.logtools as logtools

class ResetThread(threading.Thread):
    def __init__(self,vendor,mac):
        threading.Thread.__init__(self)
        self.m_vendor = vendor
        self.m_mac = mac

    def run(self):
        moduleLog = logtools.getLogger(__name__)
        moduleLog.info("Reset vendor:%s, mac:%s." %(self.m_vendor,self.m_mac))
        factoryLock.acquire()
        ap = FactoryScenario().create(self.m_vendor, self.m_mac)
        factoryLock.release()
        params = {"test":"test"}
        ap.test(params)

    def stop(self):
        self.thread_stop = True

if "__main__" == __name__:
    t1 = ResetThread("ap:cisco:e3000","68:7F:74:C5:CA:82")
    t2 = ResetThread("ap:cisco:wrt54gl","58:6D:8F:CA:AE:37")

    t1.start()
    t2.start()

    t1.join() #wait t1 end.
    t2.join() #wait t2 end.

    print "main thread end!"
