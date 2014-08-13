# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

"""
Access point base class
"""
class ApMemberName (object):
    VENDOR = "vendor"
    SERIAL = "serial"
    MAC = "mac"
    RAWIP = "rawIp"
    IP = "ip"
    SUBMASK = "submask"
    DHCP = "dhcp"
    DNS = "dns"
    STARTIP = "startIp"
    MAXUSER = "maxUser"
    ADMIN = "admin"
    PASSWORD = "password"
    #TODO, should be band abgn or frequency
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

class ApBase (object):
    def __init__(self):
        self.vendor = ""
        self.serial = ""
        self.mac = ""
        self.rawIp = ""
        self.ip = ""
        self.submask = ""
        self.dhcp = ""
        self.dns = ""
        self.startIp = ""
        self.maxUser = ""
        self.admin = ""
        self.password = ""
        self.netMode5g = ""
        self.netMode2g = ""
        self.passphrase5g = ""
        self.passphrase2g = ""
        self.ssid5g = ""
        self.ssid2g = ""
        self.channelWidth5g = ""
        self.channelWidth2g = ""
        self.keyRenewal5g = ""
        self.keyRenewal2g = ""
        self.securityMode2g = ""
        self.securityMode2g = ""
        self.algorithms5g = ""
        self.algorithms2g = ""
        self.transmissonRate = ""
        self.transmissonRateBGN = ""
        self.transmissonRateGN = ""
        self.transmissonRateBG = ""
        self.transmissonRateN = ""
        self.transmissonRateG = ""
        self.transmissonRateB = ""
        self.channelScan5g = ""
        self.channelScan2g = ""

        self.driver = ""
        self.baseURL = ""

    def initAp(self, dbcursor):
        ""

    def resetRoute(self):
        ""

    def openWebDriver(self, param):
        ""

    def closeWebDriver(self):
        self.driver.quit()

    def setRadioOff(self, netMode):
        ""

    def setDns(self, dns):
        ""

    def setDHCP(self, dhcp):
        ""

    def setChannel(self, channel):
        ""

    def setPassphrase(self, phrase):
        ""

    def setSSID(self, ssid):
        ""
    
    def setSsidBroadcast(self, ssidBroadcast):
        ""

    def setAlgorithms(self, algorithms):
        ""

    def setChannelWidth(self, width):
        ""

    def setWirelessMode(self, mode):
        ""

    def setSecurityMode(self, security):
        ""

    def setKeyRenewal(self, keyRenewal):
        ""

    def getWirelessMode(self, band = '2G'):
        if band == '2G':
            return self.netMode2g
        elif band == '5G':
            return self.netMode5g

    def getSSID(self, band = '2G'):
        if band == '2G':
            return self.ssid2g
        elif band == '5G':
            return self.ssid5g

    def getSecurityMode(self, band = '2G'):
        if band == '2G':
            return self.securityMode2g
        elif band == '5G':
            return self.securityMode5g

    def getPassphrase(self, band = '2G'):
        if band == '2G':
            return self.passphrase2g
        elif band == '5G':
            return self.passphrase5g
        

from scripts.db.dbmanager import DBApConfigName
db2memberTables = {
    DBApConfigName.VENDOR               :ApMemberName.VENDOR,
    DBApConfigName.SERIAL               :ApMemberName.SERIAL,
    DBApConfigName.MAC                  :ApMemberName.MAC,
    DBApConfigName.IP                   :ApMemberName.RAWIP,
    DBApConfigName.MANAGEIP             :ApMemberName.IP,
    DBApConfigName.SUBMASK              :ApMemberName.SUBMASK,
    DBApConfigName.DHCP                 :ApMemberName.DHCP,
    DBApConfigName.DNS                  :ApMemberName.DNS,
    DBApConfigName.STARTIP              :ApMemberName.STARTIP,
    DBApConfigName.MAXUSER              :ApMemberName.MAXUSER,
    DBApConfigName.ADMIN                :ApMemberName.ADMIN,
    DBApConfigName.PASSWORD             :ApMemberName.PASSWORD,
    DBApConfigName.NETMODE5G            :ApMemberName.NETMODE5G,
    DBApConfigName.NETMODE2G            :ApMemberName.NETMODE2G,
    DBApConfigName.PASSPHRASE5G         :ApMemberName.PASSPHRASE5G,
    DBApConfigName.PASSPHRASE2G         :ApMemberName.PASSPHRASE2G,
    DBApConfigName.SSID5G               :ApMemberName.SSID5G,
    DBApConfigName.SSID2G               :ApMemberName.SSID2G,
    DBApConfigName.CHANNELWIDTH5G       :ApMemberName.CHANNELWIDTH5G,
    DBApConfigName.CHANNELWIDTH2G       :ApMemberName.CHANNELWIDTH2G,
    DBApConfigName.CHANNEL5G            :ApMemberName.CHANNEL5G,
    DBApConfigName.CHANNEL2G            :ApMemberName.CHANNEL2G,
    DBApConfigName.SSIDBROADCAST5G      :ApMemberName.SSIDBROADCAST5G,
    DBApConfigName.SSIDBROADCAST2G      :ApMemberName.SSIDBROADCAST2G,
    DBApConfigName.SECURITYMODE5G       :ApMemberName.SECURITYMODE5G,
    DBApConfigName.SECURITYMODE2G       :ApMemberName.SECURITYMODE2G,
    DBApConfigName.KEYRENEWAL5G         :ApMemberName.KEYRENEWAL5G,
    DBApConfigName.KEYRENEWAL2G         :ApMemberName.KEYRENEWAL2G,
    DBApConfigName.ALGORITHMS5G         :ApMemberName.ALGORITHMS5G,
    DBApConfigName.ALGORITHMS2G         :ApMemberName.ALGORITHMS2G,
    DBApConfigName.TRANSMISSIONRATE     :ApMemberName.TRANSMISSIONRATE,
    DBApConfigName.TRANSMISSIONRATEB    :ApMemberName.TRANSMISSIONRATEB,
    DBApConfigName.TRANSMISSIONRATEG    :ApMemberName.TRANSMISSIONRATEG,
    DBApConfigName.TRANSMISSIONRATEN    :ApMemberName.TRANSMISSIONRATEN,
    DBApConfigName.TRANSMISSIONRATEBG   :ApMemberName.TRANSMISSIONRATEBG,
    DBApConfigName.TRANSMISSIONRATEGN   :ApMemberName.TRANSMISSIONRATEGN,
    DBApConfigName.TRANSMISSIONRATEBGN  :ApMemberName.TRANSMISSIONRATEBGN,
    DBApConfigName.CHANNELSCAN5G        :ApMemberName.CHANNELSCAN5G,
    DBApConfigName.CHANNELSCAN2G        :ApMemberName.CHANNELSCAN2G
}
