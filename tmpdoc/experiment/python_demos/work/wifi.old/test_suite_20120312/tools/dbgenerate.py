#!/usr/bin/python
'''Here make a tool write default configure for every ap to mysql, for reading.'''
import MySQLdb
import sys
import getopt

def show_help():
    print "Help info not available."
    print "Example:"
    print " *show help:"
    print " " + sys.argv[0] + " -h"
    print
    print " *add wirelessdb:"
    print " " + sys.argv[0] + " -D"
    print
    print " *add tables to wirelessdb:"
    print " " + sys.argv[0] + " -a"
    print
    print " *add wirelessdb and add tables to wirelessdb:"
    print " " + sys.argv[0] + " -D -a"
    print
    print " *delete table 'ap_cisco_e3000' from wirelessdb:"
    print " " + sys.argv[0] + " -d ap_cisco_e3000"
    print
    print " *delete wirelessdb:"
    print " " + sys.argv[0] + " -c"
    print
    sys.exit(1)

def main(db,user,passwd,table,op):
    dbName=db
    userName=user
    password=passwd
    conn = MySQLdb.connect(host='localhost', user=userName, passwd=password)
    cursor = conn.cursor(cursorclass=MySQLdb.cursors.DictCursor)

    if -1 != op.find("adddb"):
        print "create database %s." % dbName 
        command = 'create database ' + dbName + ';'
        cursor.execute(command)
    conn.select_db(dbName)

    apTable="ap_cisco_e3000"
    apData ={
        "serial":"CVQ01k634585",
        "mac":"68:7F:74:C5:CA:82",
        "ip":"192.168.1.1",
        "manageip":"192.168.1.1", #needs change
        "submask":"255.255.255.0", 
        "dhcp":"enable",
        "dns":"10.1.10.254", #default 0.0.0.0
        "admin":"admin",
        "password":"myadmin",
        "netMode5g":"Mixed",
        "netMode2g":"Mixed",
        "passphrase5g":"password",
        "passphrase2g":"password",
        "ssid5g":"Cisco34585",
        "ssid2g":"Cisco34585",
        "channelWidth5g":"Auto(20MHz or 40MHz)",
        "channelWidth2g":"20MHz only",
        "channel5g":"Auto (DFS)",
        "channel2g":"Auto",
        "ssidBroadcast5g":"enable",
        "ssidBroadcast2g":"enable"
    }
    if -1 != op.find("addtable"):
        print "create table %s." % apTable
        command = 'create table ' + apTable + '(serial varchar(32), mac varchar(32), ip varchar(32), manageip varchar(32), submask varchar(32), dhcp varchar(32), dns varchar(32), admin varchar(32), password varchar(32), netMode5g varchar(32), netMode2g varchar(32), passphrase5g varchar(32), passphrase2g varchar(32), ssid5g varchar(32), ssid2g varchar(32), channelWidth5g varchar(32), channelWidth2g varchar(32), channel5g varchar(32), channel2g varchar(32), ssidBroadcast5g varchar(32), ssidBroadcast2g varchar(32));'
        cursor.execute(command)
        command = 'insert into ' + apTable + ' values(%(serial)s,%(mac)s,%(ip)s,%(manageip)s,%(submask)s,%(dhcp)s,%(dns)s,%(admin)s,%(password)s,%(netMode5g)s,%(netMode2g)s,%(passphrase5g)s,%(passphrase2g)s,%(ssid5g)s,%(ssid2g)s,%(channelWidth5g)s,%(channelWidth2g)s,%(channel5g)s,%(channel2g)s,%(ssidBroadcast5g)s,%(ssidBroadcast2g)s);'
        cursor.execute(command,apData)

    if -1 != op.find("deltable"):
        print "delete table %s." % table 
        command = 'drop table ' + table + ';'
        cursor.execute(command)

    if -1 != op.find("deldb"):
        print "delete database %s." % dbName
        command = 'drop database ' + dbName + ';'
        cursor.execute(command)

    
    cursor.close()

if "__main__" == __name__:
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'hDad:c', ['help','DB','add','delete=','clean'])
    except getopt.GetoptError:
        show_help()

    dbName = "wirelessdb"
    userName = "root"
    password = "12345678"
    tableName = ""
    op=""

    if 0 == len(opts):
        show_help()

    for o,v in opts:
        if o in ('-h', '--help'):
            show_help()
        if o in ('-D', '--DB'):
            op+="adddb:"
        elif o in ('-a', '--add'):
            op+="addtable:"
        elif o in ('-d', '--delete'):
            tableName = v
            if "" != tableName:
                op+="deltable:"
        elif o in ('-c', '--clean'):
            op+="deldb:"
        else:
            show_help()
    main(dbName,userName,password,tableName,op)
