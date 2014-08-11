# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

from base import ApBase
from base import ApMemberName
from base import db2memberTables

from selenium import webdriver
from selenium.webdriver.support.ui import Select

from scripts.db.dbmanager import DBApInfoColumns
from scripts.db.dbmanager import database as db

from scripts.utils import log

import time

""" 
Cisco dir655 Access point .
"""

class DlinkDIR655(ApBase):

    def __init__(self, mac):
        "Initiate object and then initialize all members with initAp()"
        self.mac = mac

    def initAp(self, dbcursor):
        for field in dbcursor:
            configName = field[DBApInfoColumns.ConfigName]
            memberName = db2memberTables[configName]
            configValue = field[DBApInfoColumns.ConfigValue]
            exec 'self.' + memberName + ' = configValue'

    #TODO, workaround
    def setDefaults(self, cursor):
        self.initAp(cursor)

    def resetDefault(self):
        self.openWebDriver()
        self.resetRoute()
        self.closeWebDriver()

    def resetRoute(self):
        db.connect()
        cursor = db.getDefaults(self)
        db.disconnect()

        defaultValue = {}
        for field in cursor:
            configName = field[DBApInfoColumns.ConfigName]
            memberName = db2memberTables[configName]
            defaultValue[memberName] = field[DBApInfoColumns.ConfigValue]

        # reset all transmissonRate under different netMode
        if self.netMode2g == 'Disabled':
            self.__setRadio()
        if self.transmissonRateBGN != defaultValue[ApMemberName.TRANSMISSIONRATEBGN]:
            if self.netMode2g != 'Mixed 802.11n, 802.11g and 802.11b':
                self.__setWirelessMode('Mixed 802.11n, 802.11g and 802.11b')
            self.__setTransmissionRate(defaultValue[ApMemberName.TRANSMISSIONRATEBGN])
        if self.transmissonRateGN != defaultValue[ApMemberName.TRANSMISSIONRATEGN]:
            if self.netMode2g != 'Mixed 802.11n and 802.11g':
                self.__setWirelessMode('Mixed 802.11n and 802.11g')
            self.__setTransmissionRate(defaultValue[ApMemberName.TRANSMISSIONRATEGN])
        if self.transmissonRateBG != defaultValue[ApMemberName.TRANSMISSIONRATEBG]:
            if self.netMode2g != 'Mixed 802.11g and 802.11b':
                self.__setWirelessMode('Mixed 802.11g and 802.11b')
            self.__setTransmissionRate(defaultValue[ApMemberName.TRANSMISSIONRATEBG])
        if self.transmissonRateN != defaultValue[ApMemberName.TRANSMISSIONRATEN]:
            if self.netMode2g != '802.11n only':
                self.__setWirelessMode('802.11n only')
            self.__setTransmissionRate(defaultValue[ApMemberName.TRANSMISSIONRATEN])
        if self.transmissonRateN != defaultValue[ApMemberName.TRANSMISSIONRATEG]:
            if self.netMode2g != '802.11g only':
                self.__setWirelessMode('802.11g only')
            self.__setTransmissionRate(defaultValue[ApMemberName.TRANSMISSIONRATEG])
        if self.transmissonRateN != defaultValue[ApMemberName.TRANSMISSIONRATEB]:
            if self.netMode2g != '802.11b only':
                self.__setWirelessMode('802.11b only')
            self.__setTransmissionRate(defaultValue[ApMemberName.TRANSMISSIONRATEB])

        # reset netMode, ssid, ssidBroadcast, channel, channelWidth
        if self.netMode2g != defaultValue[ApMemberName.NETMODE2G]:
            self.__setWirelessMode(defaultValue[ApMemberName.NETMODE2G])
        if self.ssid2g != defaultValue[ApMemberName.SSID2G]:
            self.__setSSID(defaultValue[ApMemberName.SSID2G])
        if self.ssidBroadcast2g != defaultValue[ApMemberName.SSIDBROADCAST2G]:
            self.__setSsidBroadcast(defaultValue[ApMemberName.SSIDBROADCAST2G])
        if self.channel2g != defaultValue[ApMemberName.CHANNEL2G] :
            if self.channelScan2g == 'Enabled':
                self.__setChannelScan()
                self.channelScan2g = 'Disabled'
            self.__setChannel(defaultValue[ApMemberName.CHANNEL2G])
            self.__setChannelScan()
            self.channelScan2g = 'Enabled'
        if self.channelWidth2g != defaultValue[ApMemberName.CHANNELWIDTH2G]:
            self.__setChannelWidth(defaultValue[ApMemberName.CHANNELWIDTH2G])

        #reset algorithms, keyRenewal, passphrase, securityMode
        if self.securityMode2g == 'None':
            self.__setSecurityWPA('WPA-Personal')
        if self.algorithms2g != defaultValue[ApMemberName.ALGORITHMS2G]:
            self.__setAlgorithms(defaultValue[ApMemberName.ALGORITHMS2G])
        if self.keyRenewal2g != defaultValue[ApMemberName.KEYRENEWAL2G]:
            self.__setKeyRenewal(defaultValue[ApMemberName.KEYRENEWAL2G])
        if self.passphrase2g != defaultValue[ApMemberName.PASSPHRASE2G]:
            self.__setPassphrase(defaultValue[ApMemberName.PASSPHRASE2G])
        if self.securityMode2g != defaultValue[ApMemberName.SECURITYMODE2G]:
            self.__setSecurityWPA(defaultValue[ApMemberName.SECURITYMODE2G])

    def openWebDriver(self, params = None):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(30)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip

    def __setTransmissionRate(self, transmissonRate):
        dictMode = {"Mixed 802.11n, 802.11g and 802.11b":"bgn", "Mixed 802.11n and 802.11g":"gn","Mixed 802.11g and 802.11b":"bg","802.11n only":"n","802.11b only":"b", "802.11g only":"g"}
        dictNetMode = {"M":"Mixed 802.11n, 802.11g and 802.11b", "G/N":"Mixed 802.11n and 802.11g","B/G":"Mixed 802.11g and 802.11b","N":"802.11n only","B":"802.11b only", "G":"802.11g only"}
        option = '11'+dictMode[self.netMode2g]+'_txrate'
        driver = self.driver
        driver.get(self.base_url + "/")
        # login
        driver.find_element_by_id("login").click()
        # choose setup table
        driver.find_element_by_link_text("SETUP").click()
        # choose wireless settings
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        # choose manual wireless connection setup
        driver.find_element_by_name("wizard").click()
        # select transmissonRate, then change and save
        Select(driver.find_element_by_id(option)).select_by_visible_text(transmissonRate)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        
        self.transmissonRate = transmissonRate
        if self.netMode2g == dictNetMode['M']:
            self.transmissonRateBGN = transmissonRate
        if self.netMode2g == dictNetMode['G/N']:
            self.transmissonRateGN = transmissonRate
        if self.netMode2g == dictNetMode['B/G']:
            self.transmissonRateBG = transmissonRate
        if self.netMode2g == dictNetMode['N']:
            self.transmissonRateN = transmissonRate
        if self.netMode2g == dictNetMode['G']:
            self.transmissonRateG = transmissonRate
        if self.netMode2g == dictNetMode['B']:
            self.transmissonRateB = transmissonRate
  
    def setTransmissionRate(self, params):
        dictTransRate = {"Mixed 802.11n, 802.11g and 802.11b":self.transmissonRateBGN, "Mixed 802.11n and 802.11g":self.transmissonRateGN,"802.11n only":self.transmissonRateN}
        # for 6 different netMode
        dictModeB = {"1":"1","2":"2","5.5":"5.5","11":"11","B":"Best (automatic)"}
        dictModeG = {"6":"6","9":"9","12":"12","18":"18","24":"24","36":"36","48":"48","54":"54","B":"Best (automatic)"}
        dictModeN = {"M0":"MCS 0 - 6.5 [13.5]","M1":"MCS 1 - 13 [27]","M2":"MCS 2 - 19.5 [40.5]","M3":"MCS 3 - 26 [54]","M4":"MCS 4 - 39 [81]","M5":"MCS 5 - 52 [108]","M6":"MCS 6 - 58.5 [121.5]","M7":"MCS 7 - 65 [135]","M8":"MCS 8 - 13 [27]","M9":"MCS 9 - 26 [54]","M10":"MCS 10 - 39 [81]","M11":"MCS 11 - 52 [108]","M12":"MCS 12 - 78 [162]","M13":"MCS 13 - 104 [216]","M14":"MCS 14 - 117 [243]","M15":"MCS 15 - 130 [270]","B":"Best (automatic)"}
        dictModeBG = dict(dictModeB, **dictModeG)
        dictModeGN = dict(dictModeG, **dictModeN)
        dictModeBGN = dict(dictModeBG, **dictModeN)
        dictNetMode = {"Mixed 802.11n, 802.11g and 802.11b": dictModeBGN, "Mixed 802.11n and 802.11g":dictModeGN,"Mixed 802.11g and 802.11b":dictModeBG,"802.11n only":dictModeN,"802.11b only":dictModeB, "802.11g only":dictModeG}
        transmissonRate = params["transmissonRate"]
        
        if "Disabled" == self.netMode2g :
            pass
        else :
            for key in transmissonRate.keys():
                if "2G" == key:
                    if dictNetMode[self.netMode2g].has_key(transmissonRate[key]) and dictNetMode[self.netMode2g][transmissonRate[key]] != dictTransRate[self.netMode2g]:
                        self.__setTransmissionRate(dictNetMode[self.netMode2g][transmissonRate[key]])

    def __setChannelScan(self):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # select auto_channel and click
        driver.find_element_by_id("auto_channel").click()
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()

    def setChannelScan(self, params):
        channelScan = params["channel"]
        dictMode = {"D":"Disabled","E":"Enabled","A":"Enabled"}
        for key in channelScan.keys():
            if "2G" == key:
                if self.channelScan2g == dictMode[channelScan[key]]:
                    pass
                elif dictMode[channelScan[key]] == "Disabled":
                    self.__setChannelScan()
                    self.channelScan2g = "Disabled"
                elif dictMode[channelScan[key]] == "Enabled":
                    self.__setChannelScan()
                    self.channelScan2g = "Enabled"

    def __setChannel(self, channel):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # select channel, then click and save
        Select(driver.find_element_by_id("sel_wlan0_channel")).select_by_visible_text(channel)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.channel2g = channel

    def setChannel(self, params):
        channel = params["channel"]
        dictChannel = {"1":"2.412 GHz - CH 1", "2":"2.417 GHz - CH 2", "3":"2.422 GHz - CH 3", "4":"2.427 GHz - CH 4", "5":"2.432 GHz - CH 5", "6":"2.437 GHz - CH 6", "7":"2.442 GHz - CH 7", "8":"2.447 GHz - CH 8", "9":"2.452 GHz - CH 9", "10":"2.457 GHz - CH 10", "11":"2.462 GHz - CH 11","A":"Enabled"}
        if "Disabled" == self.netMode2g :
            pass
        else:
            for key in channel.keys():
                if "2G" == key:
                    if channel[key] == "A":
                        self.setChannelScan(params)
                    elif self.channelScan2g == "Enabled":
                        self.__setChannelScan()
                        self.channelScan2g = 'Disabled'
                        if self.channel2g == dictChannel[channel[key]]:
                            pass
                        else :
                            self.__setChannel(dictChannel[channel[key]])
                    elif self.channelScan2g == "Disabled" and dictChannel[channel[key]] != self.channel2g:
                        self.__setChannel(dictChannel[channel[key]])

    def __setChannelWidth(self, channelWidth):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # select channelWidth, then click and save
        Select(driver.find_element_by_id("11n_protection")).select_by_visible_text(channelWidth)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.channelWidth2g = channelWidth

    def setChannelWidth(self, params):
        channelWidth = params['channelWidth']
        dictMode = {"20":"20 MHz","A":"Auto 20/40 MHz"}
        dictNetMode = {"Mixed 802.11n, 802.11g and 802.11b": dictMode, "Mixed 802.11n and 802.11g":dictMode,"802.11n only":dictMode}
        if "Disabled" == self.netMode2g :
            pass
        else:
            for key in channelWidth.keys():
                if "2G" == key:
                    if dictNetMode.has_key(self.netMode2g) and dictMode[channelWidth[key]] != self.channelWidth2g:
                        self.__setChannelWidth(dictMode[channelWidth[key]])
        
    def __setRadio(self):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        driver.find_element_by_id("w_enable").click()
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()

    def setRadioOFF(self, params):
        netMode = params["netMode"]
        dictMode = {"D":"Disabled"}
        for key in netMode.keys():
            if "2G" == key and self.netMode2g != dictMode[netMode[key]]:
                self.__setRadio()
                self.netMode2g = dictMode[netMode[key]]

    def __setWirelessMode(self, netMode):
        dictMode = {"Mixed 802.11n, 802.11g and 802.11b":"bgn", "Mixed 802.11n and 802.11g":"gn","Mixed 802.11g and 802.11b":"bg","802.11n only":"n","802.11b only":"b", "802.11g only":"g"}
        option = "option[value=\"11" + dictMode[netMode] + "\"]"
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # select netMode, then click and save
        Select(driver.find_element_by_id("dot11_mode")).select_by_visible_text(netMode)
        driver.find_element_by_css_selector(option).click()
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.netMode2g = netMode

    def setWirelessMode(self, params):
        netMode = params["netMode"]
        dictMode = {"M":"Mixed 802.11n, 802.11g and 802.11b", "G/N":"Mixed 802.11n and 802.11g","B/G":"Mixed 802.11g and 802.11b","N":"802.11n only","B":"802.11b only", "G":"802.11g only"}
        dictModeLit = {"Mixed 802.11g and 802.11b":"B/G", "802.11b only":"B", "802.11g only":"G"}
        for key in netMode.keys():
            if "2G" == key:
                if netMode[key] == 'D':
                    self.setRadioOFF(params)
                elif dictMode[netMode[key]] == self.netMode2g:
                    pass
                elif (self.algorithms2g == "TKIP" or self.algorithms2g == 'TKIP and AES') and netMode[key] == 'N':
                    pass
                else:
                    if self.netMode2g == "Disabled":
                        self.__setRadio()
                    if (dictModeLit.has_key(self.netMode2g) and (dictModeLit.has_key(netMode[key]) == False)):
                        self.__setWirelessMode(dictMode[netMode[key]])
                        self.channelWidth2g = '20 MHz'
                    else:
                        self.__setWirelessMode(dictMode[netMode[key]])

    def __setDns(self, ipaddr):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_name("button2").click()
        # clear and set DNS
        driver.find_element_by_id("wan_primary_dns").clear()
        driver.find_element_by_id("wan_primary_dns").send_keys(ipaddr)
        driver.find_element_by_name("button").click()
        time.sleep(65)
        driver.find_element_by_id("button").click()
        self.dns = ipaddr

    def setDns(self, params):
        ipaddr = params["DNS"]
        if ipaddr['2G'] == self.dns:
            pass
        else:
            self.__setDns(ipaddr['2G'])

    def setDHCP(self, params):
        dhcp = params['dhcp']
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("NETWORK SETTINGS").click()
        
        if dhcp['2G'] == 'E':
            if driver.find_element_by_id("dhcpsvr").is_selected() == False:
                driver.find_element_by_id("dhcpsvr").click()
                driver.find_element_by_id("button").click()
                time.sleep(30)
                self.dhcp = 'Enabled'
                driver.find_element_by_id("button").click()
        elif dhcp['2G'] == 'D':
            if driver.find_element_by_id("dhcpsvr").is_selected():
                driver.find_element_by_id("dhcpsvr").click()
                driver.find_element_by_id("button").click()
                time.sleep(30)
                self.dhcp = 'Disabled'
                driver.find_element_by_id("button").click()

    def __setSSID(self, ssid):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # clear and set ssid
        driver.find_element_by_id("show_ssid").clear()
        driver.find_element_by_id("show_ssid").send_keys(ssid)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.ssid2g = ssid

    def setSSID(self, params):
        if self.netMode2g == 'Disabled':
            pass
        else:
            ssid = params['ssid']
            for key in ssid.keys():
                if key == '2G':
                    if self.ssid2g == ssid[key]:
                        pass
                    else:    
                        self.__setSSID(ssid[key])

    def __setSsidBroadcast(self, ssidBroadcast):
        if ssidBroadcast =='Disabled':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_id("login").click()
            driver.find_element_by_link_text("SETUP").click()
            driver.find_element_by_link_text("WIRELESS SETTINGS").click()
            driver.find_element_by_name("wizard").click()
            # set ssidBroadcast disabled and save
            driver.find_element_by_xpath("(//input[@id='wlan0_ssid_broadcast'])[2]").click()
            driver.find_element_by_id("button").click()
            time.sleep(25)
            driver.find_element_by_id("button").click()
            self.ssidBroadcast2g = ssidBroadcast
        elif ssidBroadcast =='Enabled':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_id("login").click()
            driver.find_element_by_link_text("SETUP").click()
            driver.find_element_by_link_text("WIRELESS SETTINGS").click()
            driver.find_element_by_name("wizard").click()
            # set ssidBroadcast enabled and save
            driver.find_element_by_id("wlan0_ssid_broadcast").click()
            driver.find_element_by_id("button").click()
            time.sleep(25)
            driver.find_element_by_id("button").click()
            self.ssidBroadcast2g = ssidBroadcast

    def setSsidBroadcast(self, params):
        dictMode = {'D':'Disabled','E':'Enabled'}
        if self.netMode2g == 'Disabled':
            pass
        else:
            ssidBroadcast = params['ssidBroadcast']
            for key in ssidBroadcast.keys():
                if key == '2G':
                    if self.ssidBroadcast2g == dictMode[ssidBroadcast[key]]:
                        pass
                    else:   
                        self.__setSsidBroadcast(dictMode[ssidBroadcast[key]])

    def __setSecurityWPA(self, securityMode):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # select and set wpa_type as Wpa-Personal
        Select(driver.find_element_by_id("wep_type")).select_by_visible_text(securityMode)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.securityMode2g = securityMode

    def __setSecurityMode(self, securityMode):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # select and set securityMode
        Select(driver.find_element_by_id("wpa_mode")).select_by_visible_text(securityMode)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.securityMode2g = securityMode
 
    def setSecurityMode(self, params):
        sMode = params["s_mode"]
        dictSecurityMode = {"WPA2/WPA":'Auto (WPA or WPA2)', 'WPA2':'WPA2 Only','WPA':'WPA Only','D':'None' ,'E':'WPA-Personal'}
        for key in sMode.keys():
            if key == '2G':
                securityMode = dictSecurityMode[sMode[key]]
                if securityMode == self.securityMode2g :
                    pass
                elif securityMode == dictSecurityMode['D']:
                    self.__setSecurityWPA(securityMode)
                elif self.securityMode2g != dictSecurityMode['D']:
                    self.__setSecurityMode(securityMode)
                elif self.securityMode2g == dictSecurityMode['D']:
                    self.__setSecurityWPA(dictSecurityMode['E'])
                    if dictSecurityMode['WPA2/WPA'] != securityMode:
                        self.__setSecurityMode(securityMode)

    def __setPassphrase(self, passphrase):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # clear and set passphrase
        driver.find_element_by_id("wlan0_psk_pass_phrase").clear()
        driver.find_element_by_id("wlan0_psk_pass_phrase").send_keys(passphrase)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.passphrase2g = passphrase

    def setPassphrase(self, params):
        passphrase = params["passphrase"]
        if self.securityMode2g != 'None' and self.netMode2g != "Disabled":
            for key in passphrase.keys():
                if key == '2G':
                    if self.passphrase2g == passphrase[key]:
                        pass
                    else:   
                        self.__setPassphrase(passphrase[key])

    def __setAlgorithms(self, algorithms):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # select and set algorithms(Cipher Type)
        Select(driver.find_element_by_id("c_type")).select_by_visible_text(algorithms)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.algorithms2g = algorithms

    def setAlgorithms(self, params):
        dictAlg = {'T':'TKIP','A':'AES','T/A':'TKIP and AES'}
        algorithms = params["algorithms"]
        if self.securityMode2g == 'None' or self.netMode2g == "Disabled":
            pass
        else:
            for key in algorithms.keys():
                if key == '2G':
                    if self.algorithms2g == dictAlg[algorithms[key]]:
                        pass
                    if self.netMode2g == '802.11n only' and (algorithms[key] == 'T' or algorithms[key] == 'T/A'):
                        pass
                    else:
                        self.__setAlgorithms(dictAlg[algorithms[key]])

    def __setKeyRenewal(self, keyRenewal):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("login").click()
        driver.find_element_by_link_text("SETUP").click()
        driver.find_element_by_link_text("WIRELESS SETTINGS").click()
        driver.find_element_by_name("wizard").click()
        # clear and set keyRenewal(Group Key Update Interval)
        driver.find_element_by_id("wlan0_gkey_rekey_time").clear()
        driver.find_element_by_id("wlan0_gkey_rekey_time").send_keys(keyRenewal)
        driver.find_element_by_id("button").click()
        time.sleep(25)
        driver.find_element_by_id("button").click()
        self.keyRenewal2g = keyRenewal

    def setKeyRenewal(self, params):
        if self.securityMode2g == 'None' or self.netMode2g == "Disabled":
            pass
        else:
            keyRenewal = params['keyRenewal']
            for key in keyRenewal.keys():
                if key == '2G':
                    if self.keyRenewal2g == keyRenewal[key]:
                        pass
                    else:   
                        self.__setKeyRenewal(keyRenewal[key])
