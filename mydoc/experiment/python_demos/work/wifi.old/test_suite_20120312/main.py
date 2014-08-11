#!/usr/bin/python

#####General setting.######
import os
import sys
import getopt

main_dir = sys.path[0]
scripts_dir = main_dir+os.sep+"scripts"
sys.path.insert(1,scripts_dir)
import parser.parser as parser
import lib.log_api as log_api

scripts_parser = scripts_dir+os.sep+"parser"


def show_help():
    print "NAME"
    print "    %s - Run the test case." % sys.argv[0]
    print
    print "SYNOPSIS"
    print "    %s [ [-h] | [-t <path>] [-l <level>] ]" % sys.argv[0]
    print
    print '''DESCRIPTION
    Options:
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
    print "    $%s -t ./cases -l debug" % sys.argv[0]
    sys.exit(1)

######Main function.######
if __name__ == "__main__":
    case_dir = "cases"
    loglevel = "info"
    mainLog = log_api.initLogger("mainLog")
    #if 1 == len(sys.argv):
    #    show_help()

    try:
        opts, args = getopt.getopt(sys.argv[1:], 'ht:l:', ['help','target=','loglevel='])
    except getopt.GetoptError:
        show_help()

    for o,v in opts:
        if o in ('-h', '--help'):
            show_help()
        elif o in ('-t', '--target'):
            case_dir = v
        elif o in ('-l', '--loglevel'):
            loglevel = v
            log_api.setLevel(loglevel)
    log_api.setLogLevel(mainLog,loglevel)
    mainLog.info("Begin to run.")
    parser.run(case_dir)
