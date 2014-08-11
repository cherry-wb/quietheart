#!/usr/bin/python
import logging
import logging.config

logger = None

# Init logger
__log_level = 'info'

def initLogger(level):
    ''' initialize the level.
        level value maybe "warning", "debug", or else "info".
        '''
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
    logging.config.dictConfig('./dictfile.conf')
#    myLogger = logging.getLogger('MyLog3')
#    
#    myLogger.debug('debug message')
#    myLogger.info('info message')
#    myLogger.warn('warn message')
#    myLogger.error('error message')
#    myLogger.critical('critical message')

######custom
    #formatter = logging.Formatter('%(asctime)s--%(filename)s:%(funcName)s:%(lineno)d:%(levelname)s>>>:%(message)s', 'the prefix:')
    #formatter = logging.Formatter('%(asctime)s--%(filename)s:%(funcName)s:%(lineno)d:%(levelname)s>>>:%(message)s')
    #console = logging.StreamHandler()
    #console.setFormatter(formatter)
    #mylogger = logging.getLogger("MyLog")
    #mylogger.addHandler(console)
    #mylogger.error("myinfo.")

    #numeric_level = getattr(logging, loglevel.upper(), None)
    #initLogger(1)
    #mylog = Logger("testlog")
    #mylog.info("my message info")
    #mylog.error("my message error")

#    myformat = '%(name)-6s %(levelname)-8s:%s %(message)s'#%(filename)s %(funcName)s %(lineno)d %(leveno)s %(module)s %(pathname)s'
#    mylog = logging.getLogger("test2")
#    logging.basicConfig(format=myformat)
#    #mylog.setLevel(DEBUG)
#    mylog.error("myinformation:%s")
