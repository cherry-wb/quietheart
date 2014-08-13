#!/usr/bin/python

import sys
import os
import ConfigParser
import MySQLdb

"""
DBManager class encapsulates database common operation
"""

class DBTables (object):
    APTABLE = "apTable"
    APINFO = "apInfo"
    CASELOGTABLE = "caseLogTable"

class DBApTableColumns (object):
    Vendor = "vendor"
    Model = "model"
    Mac = "mac"

class DBApInfoColumns (object):
    ApId = "ap_id"
    ConfigName = "config_name"
    ConfigValue = "config_value"

class DBApConfigName (object):
    VENDOR = "vendor"
    SERIAL = "serial"
    MAC = "mac"
    IP = "ip"
    MANAGEIP = "manageIp"
    SUBMASK = "submask"
    DHCP = "dhcp"
    DNS = "dns"
    STARTIP = "startIp"
    MAXUSER = "maxUser"
    ADMIN = "admin"
    PASSWORD = "password"
    NETMODE5G = "netMode5g"
    NETMODE2G = "netMode2g"
    PASSPHRASE5G = "passphrase5g"
    PASSPHRASE2G = "passphrase2g"
    SSID5G = "ssid5g"
    SSID2G = "ssid2g"
    CHANNELWIDTH5G = "channelWidth5g"
    CHANNELWIDTH2G = "channelWidth2g"
    CHANNEL5G = "channel5g"
    CHANNEL2G = "channel2g"
    SSIDBROADCAST5G = "ssidBroadcast5g"
    SSIDBROADCAST2G = "ssidBroadcast2g"
    SECURITYMODE5G = "securityMode5g"
    SECURITYMODE2G = "securityMode2g"
    KEYRENEWAL5G = "keyRenewal5g"
    KEYRENEWAL2G = "keyRenewal2g"
    ALGORITHMS5G = "algorithms5g"
    ALGORITHMS2G = "algorithms2g"
    TRANSMISSIONRATE = "transmissonRate"
    TRANSMISSIONRATEB = "transmissonRateB"
    TRANSMISSIONRATEG = "transmissonRateG"
    TRANSMISSIONRATEN = "transmissonRateN"
    TRANSMISSIONRATEBG = "transmissonRateBG"
    TRANSMISSIONRATEGN = "transmissonRateGN"
    TRANSMISSIONRATEBGN = "transmissonRateBGN"
    CHANNELSCAN5G = "channelScan5g"
    CHANNELSCAN2G = "channelScan2g"

class DBCaseTableColumns (object):
    Name = "name"
    Time = "time"
    Module = "module"
    ApModel = "apModel"
    ApMac = "apMac"
    DutModel = "dutModel"
    DutMac = "dutMac"
    Status = "status"
    Message = "message"

class DataBase:
    def __init__(self):
        defProfile = sys.path[0] + os.sep + "profiles" + os.sep + "general.conf"
        defConfig = ConfigParser.SafeConfigParser(allow_no_value = True)
        defConfig.read(defProfile)
        sectionName = 'MySQLStorage'
        self.myHost = defConfig.get(sectionName, 'Host')
        self.myUser = defConfig.get(sectionName, 'User')
        self.myPasswd = defConfig.get(sectionName, 'Password')
        self.myDb = defConfig.get(sectionName, 'Database')

    def connect(self):
        self.conn = MySQLdb.connect(host = self.myHost, user = self.myUser, passwd = self.myPasswd)
        self.conn.select_db(self.myDb)

    def disconnect(self):
        self.conn.close()

    def getDefaults(self, apObj):

        ap_table = DBTables.APTABLE
        ap_info = DBTables.APINFO
        cursor = self.conn.cursor(cursorclass = MySQLdb.cursors.DictCursor)
        command = "select "+DBApInfoColumns.ConfigName+","+DBApInfoColumns.ConfigValue+" from %s,%s " % (ap_table, ap_info)
        command += "where "
        command += "%s.mac='%s' " % (ap_table, apObj.mac)
        command += "and %s.%s=%s.id " % (ap_info,DBApInfoColumns.ApId,ap_table)
        cursor.execute(command)
        params = cursor.fetchall()
        cursor.close()

        return params

    def getApVendorMacs(self):
        ap_table = DBTables.APTABLE
        cursor = self.conn.cursor(cursorclass = MySQLdb.cursors.DictCursor)
        command = "select "+DBApTableColumns.Vendor+","+DBApTableColumns.Model+","+DBApTableColumns.Mac+" from %s " % (ap_table)
        cursor.execute(command)
        result = cursor.fetchall()
        result = [ ["ap:" + i[DBApTableColumns.Vendor] + ":" + i[DBApTableColumns.Model], i[DBApTableColumns.Mac]] for i in result]
        #result = [["ap:cisco:e3000","68:7F:74:C5:CA:82"]]
        #result = [["ap:cisco:wrt160n","68:7F:74:19:DF:E7"]]
        return result

    def logCase(self, log):
        caseLogTable = DBTables.CASELOGTABLE
        caseLogKeys = [
        DBCaseTableColumns.Name, DBCaseTableColumns.Time, DBCaseTableColumns.Module,
        DBCaseTableColumns.ApModel, DBCaseTableColumns.ApMac, DBCaseTableColumns.DutModel,
        DBCaseTableColumns.DutMac, DBCaseTableColumns.Status, DBCaseTableColumns.Message]
        caseLogData = {DBCaseTableColumns.Name:log.name, DBCaseTableColumns.Time:log.time, DBCaseTableColumns.Module:log.module,
            DBCaseTableColumns.ApModel:log.apModel, DBCaseTableColumns.ApMac:log.apMac, DBCaseTableColumns.DutModel:log.dutModel,
            DBCaseTableColumns.DutMac:log.dutMac, DBCaseTableColumns.Status:log.status, DBCaseTableColumns.Message:log.message }

        cursor = self.conn.cursor(cursorclass = MySQLdb.cursors.DictCursor)
        command = 'insert into ' + caseLogTable + ' values(id'
        for key in caseLogKeys:
            command += ',%(' + key + ')s'
        command += ');'
        cursor.execute(command, caseLogData)


database = DataBase()
