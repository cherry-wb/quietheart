# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

from scripts.ap.cisco_e3000 import CiscoE3000
from scripts.ap.cisco_e3200 import CiscoE3200
from scripts.ap.cisco_wrt54gl import CiscoWRT54GL
from scripts.ap.cisco_wrt160n import CiscoWRT160N
from scripts.ap.dlink_dir655 import DlinkDIR655
from scripts.ap.netgear_wndr3700v3 import NetgearWndr3700v3

from scripts.dut.tate import Tate

from scripts.db.dbmanager import database as db

class Factory:
    vendor2constructorTable = {
        "ap:cisco:e3000":           "CiscoE3000",
        "ap:cisco:e3200":           "CiscoE3200",
        "ap:cisco:wrt54gl":         "CiscoWRT54GL",
        "ap:cisco:wrt160n":         "CiscoWRT160N",
        "ap:dlink:dir655":          "DlinkDIR655",
        "ap:netgear:wndr3700v3":    "NetgearWndr3700v3",
        "device:tate":              "Tate"
    }

    objectDict = {}

    def __create(self, vendor, mac):
        if not self.vendor2constructorTable.has_key(vendor):
            return None
        else:
            if not self.objectDict.has_key(vendor):
                self.objectDict[vendor] = {}
            if not self.objectDict[vendor].has_key(mac):
                constructor = self.vendor2constructorTable[vendor]
                exec 'self.objectDict["' + vendor + '"]["'+mac+'"]=' + constructor + '(mac)'
                db.connect()
                params = db.getDefaults(Factory.objectDict[vendor][mac])
                Factory.objectDict[vendor][mac].setDefaults(params)
                db.disconnect()

            return  self.objectDict[vendor][mac]

    #TODO, workaround
    def create(self, vendor, mac):
        return self.__create(vendor, mac)

    def getObject(self, scenario):
        vendor = scenario.m_vendor
        mac = scenario.m_mac
        return self.__create(vendor, mac)

factory = Factory()
