#!/usr/bin/python
import sys
import os

import parser.parser_api as parser_api
from factory_class import FactoryScenario
import lib.log_api as log_api

def run(scenario):

    moduleLog = log_api.initLogger("ApSetSecurityMode")
    factory = FactoryScenario()
    ap = factory.instance(scenario)

    params = scenario.m_parameters
    moduleLog.debug(params)

    s_mode= params["s_mode"]
    ap.setSecurityMode(s_mode)

if "__main__" == __name__:
    pass
