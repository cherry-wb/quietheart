#!/usr/bin/python
import logging

logger = None
__log_level = 'info'
def initLogger(name, prefix = None):
	lg = logging.getLogger(name)
	console = logging.StreamHandler()
	if prefix is not None:
		formatter = logging.Formatter('%(name)-6s %(levelname)-8s:%s %(message)s', prefix)
	else:
		formatter = logging.Formatter('%(name)-6s %(levelname)-8s: %(message)s')
	console.setFormatter(formatter)
	lg.addHandler(console)
	if __log_level == 'warning':
		lg.setLevel(logging.WARNING)
	elif __log_level == 'debug':
		lg.setLevel(logging.DEBUG)
	else:
		lg.setLevel(logging.INFO)
	return lg

def setLevel(level):
	global __log_level
	__log_level = level

def setLogLevel(lg,level):
	if level == 'warning':
		lg.setLevel(logging.WARNING)
	elif level == 'debug':
		lg.setLevel(logging.DEBUG)
	else:
		lg.setLevel(logging.INFO)

def getLogLevel():
    return __log_level


if "__main__" == __name__:
	initLogger('debug')
	mylog = Logger("LogName")
	mylog.debug("test log debug")
	mylog.info("test log info")
