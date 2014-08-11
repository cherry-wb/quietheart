#!/usr/bin/python
'''Here make a tool write default configure for every ap to mysql, for reading.'''
import MySQLdb
import sys
import getopt

userName = "root"
password = "12345678"
dbName = "wirelessdb"

caseLogTable = "caseLogTable"
caseLogKeys = [
    'name','time','module',
    'apModel','apMac','dutModel',
    'dutMac','status','message']

apTable = "apTable"
tableKeys = ['vendor','model','mac']
tableData =[
{ "vendor":"cisco", "model":"e3000", "mac":"68:7F:74:C5:CA:82" },
{ "vendor":"cisco", "model":"wrt54gl", "mac":"58:6D:8F:CA:AE:37" },
{ "vendor":"cisco", "model":"e3200", "mac":"58:6D:8F:5A:6F:F8" },
{ "vendor":"dlink", "model":"dir655", "mac":"84:c9:b2:4c:3b:88" },
{ "vendor":"cisco", "model":"wrt160n", "mac":"68:7F:74:19:DF:E7" },
{ "vendor":"netgear", "model":"wndr3700v3", "mac":"74:44:01:51:E7:C7" }
    ]

apInfo = "apInfo"
infoKeys = ['ap_id','config_name','config_value']
infoData = [
#cisco_e3000
{ "ap_id":1, "config_name":"vendor", "config_value":"ap:cisco"},
{ "ap_id":1, "config_name":"serial", "config_value":"CVQ01k634585"}, 
{ "ap_id":1, "config_name":"mac", "config_value":"68:7F:74:C5:CA:82"}, 
{ "ap_id":1, "config_name":"ip", "config_value":"192.168.1.1"}, 
{ "ap_id":1, "config_name":"manageIp", "config_value":"10.1.10.32:8080"}, #to modify
{ "ap_id":1, "config_name":"submask", "config_value":"255.255.255.0"}, 
{ "ap_id":1, "config_name":"dhcp", "config_value":"Enabled"}, 
{ "ap_id":1, "config_name":"startIp", "config_value":"192.168.1.100"}, 
{ "ap_id":1, "config_name":"maxUser", "config_value":"50"}, 
{ "ap_id":1, "config_name":"dns", "config_value":"10.1.10.254"}, #to modify
{ "ap_id":1, "config_name":"admin", "config_value":"admin"},
{ "ap_id":1, "config_name":"password", "config_value":"myadmin"},  #to modify
{ "ap_id":1, "config_name":"netMode5g", "config_value":"Mixed"}, 
{ "ap_id":1, "config_name":"netMode2g", "config_value":"Mixed"}, 
{ "ap_id":1, "config_name":"passphrase5g", "config_value":"password"}, 
{ "ap_id":1, "config_name":"passphrase2g", "config_value":"password"}, 
{ "ap_id":1, "config_name":"ssid5g", "config_value":"Cisco34585"}, 
{ "ap_id":1, "config_name":"ssid2g", "config_value":"Cisco34585"}, 
{ "ap_id":1, "config_name":"channelWidth5g", "config_value":"Auto(20MHz or 40MHz)"}, 
{ "ap_id":1, "config_name":"channelWidth2g", "config_value":"20MHz only"}, 
{ "ap_id":1, "config_name":"channel5g", "config_value":"Auto (DFS)"}, 
{ "ap_id":1, "config_name":"channel2g", "config_value":"Auto"}, 
{ "ap_id":1, "config_name":"ssidBroadcast5g", "config_value":"Enabled"}, 
{ "ap_id":1, "config_name":"ssidBroadcast2g", "config_value":"Enabled"}, 
{ "ap_id":1, "config_name":"securityMode5g", "config_value":"WPA2/WPA mixed Mode"}, 
{ "ap_id":1, "config_name":"securityMode2g", "config_value":"WPA2/WPA mixed Mode"},

#cisco_wrt54gl
{ "ap_id":2, "config_name":"vendor", "config_value":"ap:cisco"},
{ "ap_id":2, "config_name":"serial", "config_value":"CL7C1LB12625"}, 
{ "ap_id":2, "config_name":"mac", "config_value":"58:6D:8F:CA:AE:37"}, 
{ "ap_id":2, "config_name":"ip", "config_value":"192.168.1.1"}, 
{ "ap_id":2, "config_name":"manageIp", "config_value":"10.1.10.92:8080"}, #to modify
{ "ap_id":2, "config_name":"submask", "config_value":"255.255.255.0"}, 
{ "ap_id":2, "config_name":"dhcp", "config_value":"Enabled"}, 
{ "ap_id":2, "config_name":"startIp", "config_value":"192.168.1.100"}, 
{ "ap_id":2, "config_name":"maxUser", "config_value":"50"}, 
{ "ap_id":2, "config_name":"dns", "config_value":"10.1.10.254"}, #to modify
{ "ap_id":2, "config_name":"admin", "config_value":"admin"},
{ "ap_id":2, "config_name":"password", "config_value":"myadmin"},  #to modify
{ "ap_id":2, "config_name":"netMode2g", "config_value":" Mixed"},  #carefull about the first blank space in " Mixed"
{ "ap_id":2, "config_name":"passphrase2g", "config_value":"12345678"},
{ "ap_id":2, "config_name":"ssid2g", "config_value":"linksys"}, 
{ "ap_id":2, "config_name":"channel2g", "config_value":" 6 - 2.437GHZ"}, #carefull about the first blank space in " 6 - 2.437GHZ"
{ "ap_id":2, "config_name":"ssidBroadcast2g", "config_value":"Enabled"}, 
{ "ap_id":2, "config_name":"securityMode2g", "config_value":"disabled"},
{ "ap_id":2, "config_name":"algorithms2g", "config_value":"TKIP"},
{ "ap_id":2, "config_name":"keyRenewal2g", "config_value":"3600"},

#cisco e3200
{ "ap_id":3, "config_name":"vendor",         "config_value":"ap:cisco"},
{ "ap_id":3, "config_name":"serial",         "config_value":"10B10C18104218"}, 
{ "ap_id":3, "config_name":"mac",            "config_value":"58:6D:8F:5A:6F:F8"}, 
{ "ap_id":3, "config_name":"ip",             "config_value":"192.168.1.1"}, 
{ "ap_id":3, "config_name":"manageIp",       "config_value":"10.1.10.24:8080"}, #to modify
{ "ap_id":3, "config_name":"submask",        "config_value":"255.255.255.0"}, 
{ "ap_id":3, "config_name":"dhcp",           "config_value":"Enabled"}, 
{ "ap_id":3, "config_name":"startIp",        "config_value":"192.168.1.100"}, 
{ "ap_id":3, "config_name":"maxUser",        "config_value":"50"}, 
{ "ap_id":3, "config_name":"dns",            "config_value":"10.1.10.254"}, #to modify
{ "ap_id":3, "config_name":"admin",          "config_value":"admin"},
{ "ap_id":3, "config_name":"password",       "config_value":"myadmin"},  #to modify
{ "ap_id":3, "config_name":"netMode5g",      "config_value":"Mixed"}, 
{ "ap_id":3, "config_name":"netMode2g",      "config_value":"Mixed"}, 
{ "ap_id":3, "config_name":"passphrase5g",   "config_value":""}, 
{ "ap_id":3, "config_name":"passphrase2g",   "config_value":""}, 
{ "ap_id":3, "config_name":"ssid5g",         "config_value":"Cisco04218"}, 
{ "ap_id":3, "config_name":"ssid2g",         "config_value":"Cisco04218"}, 
{ "ap_id":3, "config_name":"channelWidth5g", "config_value":"Auto (20 MHz or 40 MHz)"}, 
{ "ap_id":3, "config_name":"channelWidth2g", "config_value":"20 MHz Only"}, 
{ "ap_id":3, "config_name":"channel5g",      "config_value":"Auto (DFS)"}, 
{ "ap_id":3, "config_name":"channel2g",      "config_value":"Auto"}, 
{ "ap_id":3, "config_name":"ssidBroadcast5g","config_value":"Enabled"}, 
{ "ap_id":3, "config_name":"ssidBroadcast2g","config_value":"Enabled"}, 
{ "ap_id":3, "config_name":"securityMode5g", "config_value":"Disabled"}, 
{ "ap_id":3, "config_name":"securityMode2g", "config_value":"Disabled"},

#dlink_dir655
{ "ap_id":4, "config_name":"vendor", "config_value":"ap:dlink"},
{ "ap_id":4, "config_name":"serial", "config_value":"F35F5B7051531"}, 
{ "ap_id":4, "config_name":"mac", "config_value":"84:c9:b2:4c:3b:88"}, 
{ "ap_id":4, "config_name":"ip", "config_value":"192.168.0.1"}, 
{ "ap_id":4, "config_name":"manageIp", "config_value":"10.1.10.38:8080"}, #to modify
{ "ap_id":4, "config_name":"submask", "config_value":"255.255.255.0"}, 
{ "ap_id":4, "config_name":"dhcp", "config_value":"Enabled"}, 
{ "ap_id":4, "config_name":"startIp", "config_value":"192.168.0.100"}, 
{ "ap_id":4, "config_name":"maxUser", "config_value":"100"}, 
{ "ap_id":4, "config_name":"dns", "config_value":"10.1.10.254"}, #to modify
{ "ap_id":4, "config_name":"admin", "config_value":"admin"},
{ "ap_id":4, "config_name":"password", "config_value":""},  #to modify
{ "ap_id":4, "config_name":"netMode2g", "config_value":"Mixed 802.11n, 802.11g and 802.11b"},
{ "ap_id":4, "config_name":"passphrase2g", "config_value":"12345678"}, 
{ "ap_id":4, "config_name":"ssid2g", "config_value":"dlink"}, 
{ "ap_id":4, "config_name":"channelScan2g", "config_value":"Enabled"}, 
{ "ap_id":4, "config_name":"channel2g", "config_value":"2.437 GHz - CH 6"}, 
{ "ap_id":4, "config_name":"channelWidth2g", "config_value":"20 MHz"}, 
{ "ap_id":4, "config_name":"transmissonRateBGN", "config_value":"Best (automatic)"}, 
{ "ap_id":4, "config_name":"transmissonRateGN", "config_value":"Best (automatic)"}, 
{ "ap_id":4, "config_name":"transmissonRateBG", "config_value":"Best (automatic)"}, 
{ "ap_id":4, "config_name":"transmissonRateN", "config_value":"Best (automatic)"}, 
{ "ap_id":4, "config_name":"transmissonRateG", "config_value":"Best (automatic)"}, 
{ "ap_id":4, "config_name":"transmissonRateB", "config_value":"Best (automatic)"}, 
{ "ap_id":4, "config_name":"transmissonRate", "config_value":"Best (automatic)"}, 
{ "ap_id":4, "config_name":"securityMode2g", "config_value":"None"},
{ "ap_id":4, "config_name":"ssidBroadcast2g", "config_value":"Enabled"}, 
{ "ap_id":4, "config_name":"algorithms2g", "config_value":"TKIP and AES"},
{ "ap_id":4, "config_name":"keyRenewal2g", "config_value":"3600"},

#CiscoWRT160n
{ "ap_id":5, "config_name":"vendor", "config_value":"ap:cisco"},
{ "ap_id":5, "config_name":"serial", "config_value":"CSE51K206461"},
{ "ap_id":5, "config_name":"mac", "config_value":"68:7F:74:19:DF:E7"},
{ "ap_id":5, "config_name":"ip", "config_value":"192.168.1.1"},
{ "ap_id":5, "config_name":"manageIp", "config_value":"10.1.10.35:8080"}, #to modify
{ "ap_id":5, "config_name":"submask", "config_value":"255.255.255.0"},
{ "ap_id":5, "config_name":"dhcp", "config_value":"Enabled"},
{ "ap_id":5, "config_name":"startIp", "config_value":"192.168.1.100"},
{ "ap_id":5, "config_name":"maxUser", "config_value":"50"},
{ "ap_id":5, "config_name":"dns", "config_value":"10.1.10.254"}, #to modify
{ "ap_id":5, "config_name":"admin", "config_value":"admin"},
{ "ap_id":5, "config_name":"password", "config_value":"myadmin"},  #to modify
{ "ap_id":5, "config_name":"channelWidth2g", "config_value":"20MHz only"},
{ "ap_id":5, "config_name":"netMode2g", "config_value":"Mixed"},
{ "ap_id":5, "config_name":"passphrase2g", "config_value":"password"},
{ "ap_id":5, "config_name":"ssid2g", "config_value":"linksys"},
{ "ap_id":5, "config_name":"channel2g", "config_value":"Auto"},
{ "ap_id":5, "config_name":"ssidBroadcast2g", "config_value":"Enabled"},
{ "ap_id":5, "config_name":"securityMode2g", "config_value":"Disabled"},

#NetgearWndr3700v3
{ "ap_id":6, "config_name":"vendor",         "config_value":"ap:netgear"},
{ "ap_id":6, "config_name":"serial",         "config_value":""}, 
{ "ap_id":6, "config_name":"mac",            "config_value":"74:44:01:51:E7:C7"}, 
{ "ap_id":6, "config_name":"ip",             "config_value":"192.168.1.1"}, 
{ "ap_id":6, "config_name":"manageIp",       "config_value":"10.1.10.12:8080"}, #to modify
{ "ap_id":6, "config_name":"submask",        "config_value":"255.255.255.0"}, 
{ "ap_id":6, "config_name":"dhcp",           "config_value":"Enabled"}, 
{ "ap_id":6, "config_name":"startIp",        "config_value":"192.168.1.2"}, 
{ "ap_id":6, "config_name":"maxUser",        "config_value":"253"}, 
{ "ap_id":6, "config_name":"dns",            "config_value":"10.1.10.254"}, #to modify
{ "ap_id":6, "config_name":"admin",          "config_value":"admin"},
{ "ap_id":6, "config_name":"password",       "config_value":"password"},  #to modify
{ "ap_id":6, "config_name":"netMode2g",      "config_value":"Up to 145 Mbps"}, 
{ "ap_id":6, "config_name":"netMode5g",      "config_value":"Up to 300 Mbps"}, 
{ "ap_id":6, "config_name":"passphrase5g",   "config_value":"12345678"}, 
{ "ap_id":6, "config_name":"passphrase2g",   "config_value":"12345678"}, 
{ "ap_id":6, "config_name":"ssid2g",         "config_value":"NETGEAR"}, 
{ "ap_id":6, "config_name":"ssid5g",         "config_value":"NETGEAR-5G"}, 
{ "ap_id":6, "config_name":"channel5g",      "config_value":"153"}, 
{ "ap_id":6, "config_name":"channel2g",      "config_value":"Auto"}, 
{ "ap_id":6, "config_name":"ssidBroadcast5g","config_value":"Enabled"}, 
{ "ap_id":6, "config_name":"ssidBroadcast2g","config_value":"Enabled"}, 
{ "ap_id":6, "config_name":"securityMode5g", "config_value":"Disabled"}, 
{ "ap_id":6, "config_name":"securityMode2g", "config_value":"Disabled"}
   ]

class DBTool(object):
    def __init__(self,user,passwd):
        self.userName = userName
        self.password = password
        self.conn = None
        self.cursor = None
        self.dbName = ""
        self.apTable = ""
        self.apInfo = ""
        self.caseLogTable = ""
        #self.tableData = ""
        #self.infoData = ""

    def connect(self):
        self.conn = MySQLdb.connect(host='localhost', user=userName, passwd=password)
        self.cursor = self.conn.cursor(cursorclass=MySQLdb.cursors.DictCursor)

    def disconnect(self):
        self.cursor.close()
        self.conn.close()

    def createDB(self,db):
        self.dbName = db
        command = 'create database ' + self.dbName + ';'
        self.cursor.execute(command)
        self.conn.select_db(dbName)
        print "create database %s." % self.dbName

    def deleteDB(self,db):
        self.dbName=""
        command = 'drop database ' + db + ';'
        self.cursor.execute(command)
        print "delete database %s." % db

    def addApTable(self,db,tablename):
        print "create table %s." % tablename
        self.dbName = db
        self.conn.select_db(self.dbName)
        if "" == self.apTable:
            self.apTable = tablename
            command = 'create table ' + self.apTable
            command += '('
            command +='id int AUTO_INCREMENT PRIMARY KEY'
            for key in tableKeys:
                command += ',' +key+' varchar(64)'
            command +=');'
            self.cursor.execute(command)
    
            for item in tableData:
                command = 'insert into ' + self.apTable
                command +=' values(id'
                for key in tableKeys:
                    command +=',%('+key+')s'
                command +=');'
                self.cursor.execute(command,item)

    def addCaseLogTable(self,db,tablename):
        print "create case log table %s." % tablename
        self.dbName = db
        self.conn.select_db(self.dbName)
        if "" == self.caseLogTable:
            self.caseLogTable = tablename
            command = 'create table ' + self.caseLogTable
            command += '('
            command +='id int AUTO_INCREMENT PRIMARY KEY'
            for key in caseLogKeys:
                if 'message' == key:
                    command += ','+key+' varchar(512)'
                    continue
                command += ','+key+' varchar(64)'
            command +=');'
            self.cursor.execute(command)

    def addApInfo(self,db,tablename):
        print "create table %s." % tablename
        self.dbName = db
        self.conn.select_db(self.dbName)
        if "" == self.apInfo:
            self.apInfo = tablename
            command = 'create table ' + self.apInfo
            command += '('
            command +='id int AUTO_INCREMENT PRIMARY KEY'
            for key in infoKeys:
                if 'ap_id' == key:
                    command += ','+key+' int'
                    continue
                command += ','+key+' varchar(64)'
            command +=');'
            self.cursor.execute(command)
    
            for item in infoData:
                command = 'insert into ' + self.apInfo +' values(id'
                for key in infoKeys:
                    command +=',%('+key+')s'
                command +=');'
                self.cursor.execute(command,item)

    def deleteTable(self,db,tablename):
        print "delete table %s." % tablename[:-1]
        self.dbName = db
        self.conn.select_db(self.dbName)
        command = 'drop table ' + tablename[:-1] + ';'
        self.cursor.execute(command)

def usage():
    print "Help info not available."
    print "Example:"
    print " *show help:"
    print " " + sys.argv[0] + " -h"
    print
    print " *create wirelessdb and tables to wirelessdb:"
    print " " + sys.argv[0] + " -C"
    print
    print " *add table to wirelessdb:"
    print " " + sys.argv[0] + " -a <tablename>"
    print
    print
    print " *delete table from wirelessdb:"
    print " " + sys.argv[0] + " -d <tablename>"
    print " Available table:apInfo,apTable,caseLogTable"
    print
    print " *delete wirelessdb:"
    print " " + sys.argv[0] + " -c"
    print
    sys.exit(1)

def createAndInsert(user,passwd,db,table,op="adddb:addtable:"):
    mysql = DBTool(user,passwd)
    mysql.connect()

    if -1 != op.find("adddb:"):
        mysql.createDB(db)
        mysql.addApTable(db,apTable)
        mysql.addApInfo(db,apInfo)
        mysql.addCaseLogTable(db,caseLogTable)
        
    elif -1 != op.find("addtable:"):
        if -1 != table.find(apTable):
            mysql.addApTable(db,apTable)
        if -1 != table.find(apInfo):
            mysql.addApInfo(db,apInfo)
        if -1 != table.find(caseLogTable):
            mysql.addCaseLogTable(db,caseLogTable)

    elif -1 != op.find("deltable:"):
        print table
        mysql.deleteTable(db,table)

    elif -1 != op.find("deldb:"):
        mysql.deleteDB(db)

    mysql.disconnect()

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'hCa:d:c', ['help','Create','add=','delete=','clean'])
    except getopt.GetoptError:
        usage()

    tableName = ""
    op=""

    if 0 == len(opts):
        usage()

    for o,v in opts:
        if o in ('-h', '--help'):
            usage()
        if o in ('-C', '--Create'):
            op+="adddb:"
        elif o in ('-a', '--add'):
            op+="addtable:"
            #tableName=apTable+":"+apInfo+":"+caseLogTable+":"
            tableName = v
        elif o in ('-d', '--delete'):
            tableName += (v+':')
            if "" != tableName:
                op+="deltable:"
        elif o in ('-c', '--clean'):
            op+="deldb:"
        else:
            usage()
    createAndInsert(userName,password,dbName,tableName,op)

if "__main__" == __name__:
    main()
