#!/usr/bin/python
import sys
import os

def run(scenario):
    import parser.parser_api as parser_api
    from factory_class import FactoryScenario
    import lib.log_api as log_api

    moduleLog = log_api.initLogger("ApLogin")
    vendor = scenario.m_vendor
    params = scenario.m_parameters
    serial = scenario.m_serial
    ssidBroadcast = params['ssidBroadcast']
    factory = FactoryScenario()
    ap = factory.instance(scenario)
    moduleLog.debug(params)
    moduleLog.debug(ssidBroadcast)
    ap.test(params)
    ap.setSsidBroadcast(ssidBroadcast)

if "__main__" == __name__:
    pass
