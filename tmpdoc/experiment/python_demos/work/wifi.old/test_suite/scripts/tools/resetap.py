#!/usr/bin/python
import sys
import os

s_fname = sys.path[0]
scripts_dir = s_fname
if scripts_dir.find("scripts") != -1:
    while os.path.basename(scripts_dir) != "scripts":
        scripts_dir = os.path.dirname(scripts_dir)
else:
    print "Path error, not in 'scripts'."
    exit(1)
main_dir = os.path.dirname(scripts_dir)
sys.path.insert(0,main_dir)
sys.path.insert(1,scripts_dir)

import scripts.parser.parser_api as parser_api
from scripts.factory_class import FactoryScenario
import scripts.lib.logtools as logtools

def run(vendor,mac):
    moduleLog.debug("Reset vendor:%s, mac:%s." %(vendor,mac))
    try:
        ap = FactoryScenario().create(vendor, mac)
        params = {"test":"test"}
        ret =ap.resetDefault()
        return ret
    except Exception,e:
        logger.error(repr(e))
        return 1

######
moduleLog = logtools.getLogger(__name__)
vendor = sys.argv[1]
mac = sys.argv[2]
sys.exit(run(vendor,mac))
