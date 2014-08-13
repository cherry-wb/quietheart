#!/usr/bin/python
''' custom format log.
'''
import logging
import logging.config

class CustomMessage():
    def __init__(self,f1="",f2=""):
        self.field1 = f1
        self.field2 = f2

    def __str__(self):
        ret = ""
        ret += "field1:" + self.field1 + "."
        ret += "field2:" + self.field2 + "."
        return ret

    def setF1(self,f):
        self.field1 = f

    def setF2(self,f):
        self.field2 = f

class MyHandler(logging.Handler):
    def __init__(self,level=0):
        logging.Handler.__init__(self,level)

    def emit(self,record):
        #print record
        print "--------"
#for study
        print "set print in format:"
        print "args:",record.args,
        print "asctime:",record.asctime,
        print "name:",record.name,
        print "levelname:",record.levelname,
        print "lineno:",record.lineno,
        print "message:",record.message
        print "not set print in format:"
        print "pathname:",record.pathname,
        print "process:",record.process,
        print "processName:",record.processName
        print "custom attribute:"
        if hasattr(record,"custom1"):
            print "custom1:%s." %record.custom1,
        if hasattr(record,"custom2"):
            print "custom2:%s." %record.custom2,
        if hasattr(record,"custom3"):
            custom_obj = record.custom3
            print custom_obj.field1 + ":" + custom_obj.field2 + "."
#common things starts here
        print "use format:"
        msg = self.format(record)
        print msg
        print "--------"

    def format(self,record):
        if self.formatter:
            fmt = self.formatter
        else:
            return "No formmatter"
        ret_str = fmt.format(record)

        ret_str = "processed formated result in custom Handler:" + ret_str
        return ret_str

if "__main__" == __name__:
# create logger
    myLogger = logging.getLogger('MyLog1')
    myLogger.setLevel(logging.DEBUG) #set level pass to handler

# create console handler and set level to debug
    consoleHandler = logging.StreamHandler()
    consoleHandler.setLevel(logging.DEBUG) #set level handler send.

    customHandler = MyHandler()
    customHandler.setLevel(logging.DEBUG)


# create formatter
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    formatter2 = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(lineno)d - %(message)s')

# add formatter to consoleHandler
    consoleHandler.setFormatter(formatter)
    customHandler.setFormatter(formatter2)

# add consoleHandler to MyLogger
    myLogger.addHandler(consoleHandler)
    myLogger.addHandler(customHandler)

# normal use
    myLogger.debug('debug message')
    myLogger.info('info message')
    myLogger.warn('warn message')
    myLogger.error('error message')
    myLogger.critical('critical message')

# custom message
    msg = CustomMessage("msgvalue1","msgvalue2")
    myAttribute = {"custom1":"value1","custom2":"value2","custom3":msg}
    myLogger.info(msg,extra=myAttribute) #add custom attribute for handler by dictionary.
