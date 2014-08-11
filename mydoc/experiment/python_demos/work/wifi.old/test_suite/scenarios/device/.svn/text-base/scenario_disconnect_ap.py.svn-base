#!/usr/bin/python

from scripts.factory import Factory

import scripts.lib.logtools as logtools

def run(scenario):
    moduleLog = logtools.logger
    dut = Factory().getObject(scenario)

    params = scenario.m_parameters
    moduleLog.info(params)

    dut.disconnectAp()

