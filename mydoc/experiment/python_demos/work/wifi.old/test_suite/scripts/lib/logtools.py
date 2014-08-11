#!/usr/bin/python
from logging import Logger
from scripts.lib.pyh import *
import logging
import os
import time

import scripts.db.dbmanager as dbtools

logger = None
__log_level = 'info'

class CaseDBLog(object):
    def __init__(self):
        self.time = ""
        self.module = ""
        self.message = ""

        self.name = ""
        self.apModel = ""
        self.apMac = ""
        self.dutModel = ""
        self.dutMac = ""
        self.status = ""

class DBLogHandler(logging.Handler):
    def __init__(self,dbName,level=0):
        logging.Handler.__init__(self,level)
        self.db = dbName

    def emit(self,record):
        dbLog = self.format(record)
        if dbLog.has_key("caseLog"):
            caseDbLog = dbLog["caseLog"]
            dbtools.database.connect()
            dbtools.database.logCase(caseDbLog)
            dbtools.database.disconnect()

    def format(self,record):
        dbLog = {}
        if hasattr(record,"caseLog"):
            caseDbLog = record.caseLog
            caseDbLog.time = record.asctime
            caseDbLog.module = record.module
            caseDbLog.funcName = record.funcName
            caseDbLog.message = record.message
            dbLog["caseLog"]=caseDbLog
        return dbLog

class CaseHtmlLog(object):
    def __init__(self):
        self.time = ""
        self.module = ""
        self.message = ""

        self.name = ""
        self.apModel = ""
        self.apMac = ""
        self.dutModel = ""
        self.dutMac = ""
        self.status = ""

class HtmlLogHandler(logging.Handler):
    def __init__(self,htmlName,level=0):
        logging.Handler.__init__(self,level)
        time_prefix=time.strftime("%Y_%m_%d_%H_%M_%S_",time.localtime())
        tempDir = "report"+os.sep+"temp"
        if not os.path.exists(tempDir):
            os.mkdir(tempDir)

        self.html = tempDir+os.sep+time_prefix+htmlName+".html"
        self.page = PyH("CasePage")
        self.page <<h1('CaseLogTable',align='center')
        self.caseTable = self.page << table(border='1',id='caseTable')
        tableHead = [
        dbtools.DBCaseTableColumns.Name, dbtools.DBCaseTableColumns.Time, dbtools.DBCaseTableColumns.Module,
        dbtools.DBCaseTableColumns.ApModel, dbtools.DBCaseTableColumns.ApMac, dbtools.DBCaseTableColumns.DutModel,
        dbtools.DBCaseTableColumns.DutMac, dbtools.DBCaseTableColumns.Status, dbtools.DBCaseTableColumns.Message]
        caseHeadLine = self.caseTable << tr(id='headline')
        for column in tableHead:
            caseHeadLine << td(column)

    def emit(self,record):
        htmlLog = self.format(record)
        if htmlLog.has_key("caseLog"):
            caseHtmlLog = htmlLog["caseLog"]
            tableColumn = [
            caseHtmlLog.name,caseHtmlLog.time,caseHtmlLog.module,
            caseHtmlLog.apModel,caseHtmlLog.apMac,caseHtmlLog.dutModel,
    caseHtmlLog.dutMac,caseHtmlLog.status,caseHtmlLog.message]
            line  = self.caseTable << tr()
            for column in tableColumn:
                line << td(column)
            self.page.printOut(self.html)

    def format(self,record):
        htmlLog = {}
        if hasattr(record,"caseLog"):
            caseHtmlLog = record.caseLog
            caseHtmlLog.time = record.asctime
            caseHtmlLog.module = record.module
            caseHtmlLog.funcName = record.funcName
            caseHtmlLog.message = record.message
            htmlLog["caseLog"]=caseHtmlLog
        return htmlLog
    def __del__(self):
        pass

def _initLogger(name, prefix = None):
    global logger
    logger = logging.getLogger(name)
    console = logging.StreamHandler()
    dbHandler = DBLogHandler(dbtools.database.myDb)
    htmlHandler = HtmlLogHandler("logfile")
    if prefix is not None:
        formatter = logging.Formatter('%(name)-6s %(asctime)s %(levelname)-8s %(module)s %(funcName)s %(lineno)d:%s %(message)s', prefix)
    else:
        formatter = logging.Formatter('%(name)-6s %(asctime)s %(levelname)-8s %(module)s %(funcName)s %(lineno)d: %(message)s')
    console.setFormatter(formatter)
    logger.addHandler(console)

    dbHandler.setFormatter(formatter)
    logger.addHandler(dbHandler)

    htmlHandler.setFormatter(formatter)
    logger.addHandler(htmlHandler)
    if __log_level == 'warning':
        logger.setLevel(logging.WARNING)
    elif __log_level == 'debug':
        logger.setLevel(logging.DEBUG)
    else:
        logger.setLevel(logging.INFO)
    return logger

def getLogger(name = None,prefix = None):
    global logger
    if None == logger:
        logger = _initLogger(name,prefix)
    return logger

def setLevel(level):
    global __log_level
    if level == 'warning':
        logger.setLevel(logging.WARNING)
    elif level == 'debug':
        logger.setLevel(logging.DEBUG)
    else:
        logger.setLevel(logging.INFO)
    __log_level = level

def getLevel():
    return __log_level


logger = getLogger("WirelessTest")

if "__main__" == __name__:
    mylog = getLogger(__name__)
    mylog.info("test log info")
    mylog.info("test log info2")

    mylog = getLogger()
    mylog.info("test log info3")

    mylog = getLogger()
    mylog.info("test log info4")

    mylog = getLogger()
    mylog.info("test log info5")
