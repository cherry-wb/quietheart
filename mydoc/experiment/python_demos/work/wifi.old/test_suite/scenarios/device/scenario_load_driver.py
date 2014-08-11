#!/usr/bin/python

import scripts.lib.logtools as logtools

from scripts.factory import Factory

def run(scenario):
    moduleLog = logtools.logger
    dut = Factory().getObject(scenario)

    params = scenario.m_parameters
    moduleLog.info(params)

    dut.loadDriver()

