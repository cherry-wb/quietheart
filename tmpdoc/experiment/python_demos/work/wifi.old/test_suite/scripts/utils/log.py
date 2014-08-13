# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

import logging

logger = None

# Init logger
__log_level = 'info'

def initLogger(level):
    global logger
    global __log_level
    __log_level = level
    logger = Logger('KATF')

def Logger(name, prefix = None):
    lg = logging.getLogger(name)
    console = logging.StreamHandler()
    if prefix is not None:
        formatter = logging.Formatter('%(name)-6s %(levelname)-8s:%s %(message)s', prefix)
    else:
        formatter = logging.Formatter('%(name)-6s %(levelname)-8s: %(message)s')
    #formatter = logging.Formatter('%(name)6s %(asctime)s %(levelname)-8s: %(message)s')
    console.setFormatter(formatter)
    lg.addHandler(console)
    if __log_level == 'warning':
        lg.setLevel(logging.WARNING)
    elif __log_level == 'debug':
        lg.setLevel(logging.DEBUG)
    else:
        lg.setLevel(logging.INFO)
    return lg

