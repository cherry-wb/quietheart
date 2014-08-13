#!/usr/bin/python
#from scripts.factory_class import FactoryScenario

import os
import sys
import getopt
import subprocess

main_dir = sys.path[0]
scripts_dir = main_dir + os.sep + "scripts"


import scripts.parser.parser as parser
import scripts.db.dbmanager as dbtools
import scripts.lib.logtools as logtools
mainLog = logtools.logger

MaxProcessNum = 5

def usage():
    print "NAME"
    print "    %s - Run the test case." % sys.argv[0]
    print
    print "SYNOPSIS"
    print "    %s [ [-h] | [-r] [-t <path>] [-l <level>] ]" % sys.argv[0]
    print
    print '''DESCRIPTION
    Options:
    -r,--reset
          Reset all ap to default configuration before test.
          
    -t PATH,--target=PATH
          Specify the case directory instead of default.
          Case directory specified the which directory's cases to be run.
          Default case directory is:
          ./cases
          Which means execute all the cases.We can also specify a single case file by this option.
          If we want to specify multi file, we'd better put them in a 'temp' directory specified.

    -l LEVEL,--loglevel=LEVEL
          Log level. Available levels as below:
          - warning
          - info (default)
          - debug

    -h,--help
          Print this help.
    '''
    print
    print "EXAMPLE"
    print "    $%s -r -t ./cases -l debug" % sys.argv[0]
    sys.exit(1)

def _update_process_queue(que, logInfo):
    check = True
    while check:
        for p in que:
            ret = p.poll()
            if None != ret:
                if ret < 0:
                    mainLog.warning(logInfo[p.pid] + "Termined by signal.")
                    logInfo[p.pid] += ":Reset interrupted by signal."
                if ret > 0:
                    mainLog.warning(logInfo[p.pid] + "Terminated due to some wrong.")
                    logInfo[p.pid] += ":Reset terminated due to wrong."
                else:
                    mainLog.debug(logInfo[p.pid] + "Reset ok.")
                    logInfo[p.pid] += "------>Reset ok."
                que.remove(p)
                check = False

def _wait_process_queue(que, logInfo):
    while len(que) > 0:
        _update_process_queue(que, logInfo)

def reset_all(procNum = MaxProcessNum):
    mainLog.debug("Begin reset.")
    procLog = {}
    procQueue = []
    dbtools.database.connect()
    aps = dbtools.database.getApVendorMacs()
    dbtools.database.disconnect()
    for model, mac in aps:
        cmd = []
        cmd.append(scripts_dir + os.sep + "tools" + os.sep + "resetap.py")
        cmd.append(model)
        cmd.append(mac)
        if len(procQueue) >= procNum:
            _update_process_queue(procQueue, procLog)
        p = subprocess.Popen(cmd)
        procQueue.append(p)
        procLog[p.pid] = "model:" + model + ",mac:" + mac

    _wait_process_queue(procQueue, procLog)

    mainLog.debug("Reset done, reset result is:")

    for k in procLog.keys():
        mainLog.info(procLog[k])

if __name__ == "__main__":
    case_dir = "cases"
    loglevel = "info"
    reset = False

    if 1 == len(sys.argv):
        usage()

    try:
        opts, args = getopt.getopt(sys.argv[1:], 'hrt:l:', ['help', 'reset=', 'target=', 'loglevel='])
    except getopt.GetoptError:
        usage()

    for o, v in opts:
        if o in ('-h', '--help'):
            usage()
        elif o in ('-l', '--loglevel'):
            loglevel = v
        elif o in ('-r', '--reset'):
            reset = True
        elif o in ('-t', '--target'):
            case_dir = v
    logtools.setLevel(loglevel)
    mainLog.debug("Begin to run.")
    if reset:
        reset_all()
    parser.run(case_dir)
