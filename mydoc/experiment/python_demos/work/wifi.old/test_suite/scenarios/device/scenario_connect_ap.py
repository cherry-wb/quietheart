#!/usr/bin/python

from scripts.factory import Factory

import scripts.parser.parser_api as parser_api
import scripts.lib.logtools as logtools

def run(scenario):
    moduleLog = logtools.logger
    dut = Factory().getObject(scenario)

    params = scenario.m_parameters
    moduleLog.info(params)

    ap = parser_api.g_context.get_ap_obj()
    dut.connectAp(ap)

