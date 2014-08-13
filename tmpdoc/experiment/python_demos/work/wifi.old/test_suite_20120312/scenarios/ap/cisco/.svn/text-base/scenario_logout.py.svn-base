#!/usr/bin/python
import sys
import os

import parser.parser_api as parser_api
from factory_class import FactoryScenario
import lib.log_api as log_api

def run(scenario):
    moduleLog = log_api.initLogger(scenario.m_name)
    ap = FactoryScenario().instance(scenario)

    params = scenario.m_parameters
    moduleLog.info(params)

    ap.closeWebDriver()

if "__main__" == __name__:
    print "nothing to test!"
