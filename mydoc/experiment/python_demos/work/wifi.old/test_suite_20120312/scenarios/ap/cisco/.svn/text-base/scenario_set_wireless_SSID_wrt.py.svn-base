#!/usr/bin/python
import sys
import os

s_fname = sys.path[0]
scripts_dir = s_fname + os.sep + "scripts"
if scripts_dir.find("scripts") != -1:
    while os.path.basename(scripts_dir) != "scripts":
        scripts_dir = os.path.dirname(scripts_dir)
else:
    print "Path error, not in 'scripts'."
    exit(1)

import parser.parser_api as parser_api
from factory_class import FactoryScenario
import lib.log_api as log_api
moduleLog = log_api.initLogger("ApSetWireLessSSID")

def run(vendor, params):
    factory = FactoryScenario()
    ap = factory.instance(vendor)
    params_dict = params
    ssid = params["ssid"]
    moduleLog.debug(params_dict)
    moduleLog.debug(ssid)
    ap.setParameters(params_dict)
    ap.setSSID(ssid)
