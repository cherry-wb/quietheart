#!/usr/bin/python

from scripts.factory_class import FactoryScenario
#from scripts.tools.reset import ResetThread

import os
import sys
import getopt
import subprocess

main_dir = sys.path[0]
scripts_dir = main_dir + os.sep + "scripts"
#sys.path.insert(1, scripts_dir)
import scripts.parser.parser as parser
import scripts.lib.dbtools as dbtools
import scripts.lib.logtools as logtools

mainLog = logtools.getLogger(__name__)
mainLog.info("testtest")
MaxProcessNum = 5
