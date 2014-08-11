#!/usr/bin/python

# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

from scripts.utils import log
from scripts.factory import factory as factory

def run(scenario):

    logger = log.Logger("scenario_set_wireless_keyRenewal")

    params = scenario.m_parameters
    logger.info(params)

    ap = factory.getObject(scenario)
    ap.setKeyRenewal(params)
