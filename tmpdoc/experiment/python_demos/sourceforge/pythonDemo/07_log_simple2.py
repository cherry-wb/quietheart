#!/usr/bin/python
import logging
import logging.config
if "__main__" == __name__:
######Simple Use
    logging.basicConfig(format='%(name)s:%(asctime)s--%(filename)s:%(funcName)s:%(lineno)d:%(levelname)s>>>:%(message)s', level=logging.DEBUG)
    logging.debug("error level.")
    logging.info("error level.")
    logging.error("error level.")
    logging.log(logging.ERROR,"error by log.")
    
######Use1,config by code
# create logger
    myLogger = logging.getLogger('MyLog1')
    myLogger.setLevel(logging.DEBUG) #set level pass to handler

# create console handler and set level to debug
    consoleHandler = logging.StreamHandler()
    consoleHandler.setLevel(logging.DEBUG) #set level handler send.

# create formatter
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

# add formatter to consoleHandler
    consoleHandler.setFormatter(formatter)

# add consoleHandler to MyLogger
    myLogger.addHandler(consoleHandler)

    myLogger.debug('debug message')
    myLogger.info('info message')
    myLogger.warn('warn message')
    myLogger.error('error message')
    myLogger.critical('critical message')

######Use2,config by file
    r'''
    ./logging.conf
[loggers]
keys=root,MyLog2

[handlers]
keys=consoleHandler

[formatters]
keys=simpleFormatter

[logger_root]
level=DEBUG
handlers=consoleHandler

[logger_MyLog2]
level=DEBUG
handlers=consoleHandler
qualname=MyLog2
propagate=0

[handler_consoleHandler]
class=StreamHandler
level=DEBUG
formatter=simpleFormatter
args=(sys.stdout,)

[formatter_simpleFormatter]
format=%(name)s:%(asctime)s--%(filename)s:%(funcName)s:%(lineno)d:%(levelname)s--->>:%(message)s
datefmt=
'''
    logging.config.fileConfig('./logging.conf')
    # create logger
    myLogger = logging.getLogger('MyLog2')
    
    myLogger.debug('debug message')
    myLogger.info('info message')
    myLogger.warn('warn message')
    myLogger.error('error message')
    myLogger.critical('critical message')

######Use3,config by dict file
#should refer to http://docs.python.org/library/logging.config.html#logging-config-api
    #logging.config.dictConfig('./dictfile.conf')
    #myLogger = logging.getLogger('MyLog3')
    
    #myLogger.debug('debug message')
    #myLogger.info('info message')
    #myLogger.warn('warn message')
    #myLogger.error('error message')
    #myLogger.critical('critical message')
