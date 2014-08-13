#!/usr/bin/python
import ConfigParser
import MySQLdb
from ap.cisco_e3000 import *

class Table:
    pass

class DataBase:
    def __init__(self):
        pass

    def getDefaults(self,obj,vendor):
#path of profiles
        defProfile = sys.path[0] + os.sep + "profiles" + os.sep + "general.conf"
        defConfig = ConfigParser.SafeConfigParser(allow_no_value=True)
        defConfig.read(defProfile)
        sectionName='MySQLStorage'
        myHost=defConfig.get(sectionName,'Host')
        myUser=defConfig.get(sectionName,'User')
        myPasswd=defConfig.get(sectionName,'Password')
        myDb=defConfig.get(sectionName,'Database')

#map the vendor to table name
        table_maps = {
            "ap:cisco:e3000":"ap_cisco_e3000"
        }
#map the table column to class member.
        member_maps ={
            "serial":"serial",
            "mac":"mac",
            "ip":"rawIp",
            "manageip":"ip",
            "submask":"submask", 
            "dhcp":"dhcp",
            "dns":"dns",
            "admin":"admin",
            "password":"password",
            "netMode5g":"netMode5g",
            "netMode2g":"netMode2g",
            "passphrase5g":"passphrase5g",
            "passphrase2g":"passphrase2g",
            "ssid5g":"ssid5g",
            "ssid2g":"ssid2g",
            "channelWidth5g":"channelWidth5g",
            "channelWidth2g":"channelWidth2g",
            "channel5g":"channel5g",
            "channel2g":"channel2g",
            "ssidBroadcast5g":"ssidBroadcast5g",
            "ssidBroadcast2g":"ssidBroadcast2g"
        }
        self.conn = MySQLdb.connect(host=myHost, user=myUser, passwd=myPasswd)
        self.conn.select_db(myDb)
            
        table=table_maps[vendor]
        cursor = self.conn.cursor(cursorclass=MySQLdb.cursors.DictCursor)
        command = "select * from %s where mac= '%s';" %(table,obj.mac)
        cursor.execute(command)

        info = cursor.fetchone()
        if info != None:
            for column in info.keys():
                member = member_maps[column]
                exec 'obj.' + member + ' = info["' + column + '"]'
        cursor.close()

database = DataBase()
