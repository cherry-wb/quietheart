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
Cisco E3000 Access point .
"""

class CiscoE3000 (ApBase):
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

    def setRadioOFF(self, param):
        netMode = param["netMode"]
        dictWmode = {'D':'Disabled'}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        for key in netMode.keys():
            if key == '2G':
                netmode2g = netMode["2G"]
                Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(dictWmode[netmode2g])
            if key == "5G":
                netmode5g = netMode["5G"]
                Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(dictWmode[netmode5g])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        for key in netMode.keys():
            if key == '2G':
                self.netmode2g = dictWmode[netmode2g]
        for key in netMode.keys():
            if key == "5G":
                self.netmode5g = dictWmode[netmode5g]

    #TODO, workaround
    def resetDefault(self):
        self.openWebDriver()
        self.resetRoute()
        self.closeWebDriver()

    def resetRoute(self):
        #TODO, getDefaults() not reasonable, need to restructure
        db.connect()
        cursor = db.getDefaults(self)
        db.disconnect()

        defaultValue = {}
        for field in cursor:
            configName = field[DBApInfoColumns.ConfigName]
            memberName = db2memberTables[configName]
            defaultValue[memberName] = field[DBApInfoColumns.ConfigValue]

        self.__setSecurityMode('5G', defaultValue[ApMemberName.SECURITYMODE5G])
        self.__setSecurityMode('2G', defaultValue[ApMemberName.SECURITYMODE2G])
        self.__setPassphrase('5G', defaultValue[ApMemberName.PASSPHRASE5G])
        self.__setPassphrase('2G', defaultValue[ApMemberName.PASSPHRASE2G])
        self.__setWirelessMode('5G', defaultValue[ApMemberName.NETMODE5G])
        self.__setWirelessMode('2G', defaultValue[ApMemberName.NETMODE2G])
        self.__setChannelWidth('5G', defaultValue[ApMemberName.CHANNELWIDTH5G])
        self.__setChannelWidth('2G', defaultValue[ApMemberName.CHANNELWIDTH2G])
        self.__setChannel('5G', defaultValue[ApMemberName.CHANNEL5G])
        self.__setChannel('2G', defaultValue[ApMemberName.CHANNEL2G])
        self.__setSSID('5G', defaultValue[ApMemberName.SSID5G])
        self.__setSSID('2G', defaultValue[ApMemberName.SSID2G])
        self.__setSsidBroadcast('5G', defaultValue[ApMemberName.SSIDBROADCAST5G])
        self.__setSsidBroadcast('2G', defaultValue[ApMemberName.SSIDBROADCAST2G])

    # 'params' is reserved
    def openWebDriver(self, params = None):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(30)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip

    def __setChannel(self, band, channel):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        if band == '5G':
            #'_wl1_channel' stand for the name of channel5g in web
            Select(driver.find_element_by_name("_wl1_channel")).select_by_visible_text(channel)
        if band == '2G':
            #'_wl0_channel' stand for the name of channel2g in web
            Select(driver.find_element_by_name("_wl0_channel")).select_by_visible_text(channel)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        if band == '5G':
            self.channel5g = channel
        if band == '2G':
            self.channel2g = channel

    def setChannel(self, param):
        dictChannel5g = {'36':'36 - 5.180GHz', '40':'40 - 5.200GHz', '44':'44 - 5.220GHz', '48':'48 - 5.240GHz', '149':'149 - 5.745GHz', '153':'153 - 5.765GHz', '157':'157 - 5.785GHz', '161':'161 - 5.805GHz', "A":"Auto (DFS)"}
        dictChannel2g = {'1':'1 - 2.412GHZ', '2':'2 - 2.417GHZ', '3':'3 - 2.422GHZ', '4':'4 - 2.427GHZ', '5':'5 - 2.432GHZ', '6':'6 - 2.437GHZ', '7':'7 - 2.442GHZ', '8':'8 - 2.447GHZ', '9':'9 - 2.452GHZ', '10':'10 - 2.457GHZ', '11':'11 - 2.462GHZ', "A":"Auto"}
        channel = param["channel"]
        for key in channel.keys():
            if key == '5G' and self.netMode5g != "Disabled":
                self.__setChannel(key, dictChannel5g[channel[key]])
            if key == '2G' and self.netMode2g != "Disabled":
                self.__setChannel(key, dictChannel2g[channel[key]])

    def __setChannelWidth(self, band, channelWidth):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        if band == '5G':
            Select(driver.find_element_by_name("_wl1_nbw")).select_by_visible_text(channelWidth)
        if band == '2G':
            Select(driver.find_element_by_name("_wl0_nbw")).select_by_visible_text(channelWidth)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        if band == '5G' and channelWidth != self.channelWidth5g:
            self.channelWidth5g = channelWidth
            self.channel5g = 'Auto (DFS)'
        elif band == '5G' and channelWidth == self.channelWidth5g:
            self.channelWidth5g = channelWidth
        if band == '2G' and channelWidth != self.channelWidth2g:
            self.channelWidth2g = channelWidth
            self.channel2g = 'Auto'
        elif band == '2G' and channelWidth == self.channelWidth2g:
            self.channelWidth2g = channelWidth

    def setChannelWidth(self, param):
        dictChannelWidth2G = {"A":"Auto(20MHz or 40MHz)", "20":"20MHz only"}
        dictChannelWidth5G = {"A":"Auto(20MHz or 40MHz)", "20":"20MHz only", "40":"40MHz only"}
        ChannelWidth = param["channelwidth"]
        for key in ChannelWidth.keys():
            if key == '5G'and self.netMode5g != "Disabled" and self.netMode5g != 'Wireless-A Only':
                self.__setChannelWidth(key, dictChannelWidth5G[ChannelWidth[key]])
            if key == '2G'and self.netMode2g != "Disabled" and self.netMode2g != 'Wireless-B/G Only' and  self.netMode2g != 'Wireless-B Only' and self.netMode2g != 'Wireless-G Only':
                self.__setChannelWidth(key, dictChannelWidth2G[ChannelWidth[key]])

    def __setSecurityMode(self, band, securityMode):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("td.small > a").click()
        if band == '5G' and securityMode != "Disabled":
            if self.netMode5g == 'Mixed' and securityMode == "WPA Personal" and self.securityMode5g != 'WPA Personal':
                Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(securityMode)
                alert = driver.switch_to_alert()
                alert.accept()
            elif self.netMode5g == 'Wireless-N Only' and securityMode != "WPA2 Personal" and securityMode != "Disabled":
                pass
            else:
                Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(securityMode)
        elif band == '5G' and securityMode == "Disabled":
            Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(securityMode)

        if band == '2G' and securityMode != "Disabled":
            if self.netMode2g == 'Mixed' and securityMode == "WPA Personal" and self.securityMode2g != 'WPA Personal':
                Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(securityMode)
                #if a window is popuped ,it will be click the 'OK'/'Accept' 
                alert = driver.switch_to_alert()
                alert.accept()
            elif  self.netMode2g == 'Wireless-N Only' and securityMode != 'WPA2 Personal' and securityMode != "Disabled":
                pass
            else:
                Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(securityMode)
        elif securityMode == "Disabled":
            Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(securityMode)
         #click the save setting    
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
         #click the menu of continue
        driver.find_element_by_name("action").click()
        if band == '5G':
            self.securityMode5g = securityMode
        if band == '2G':
            self.securityMode2g = securityMode

    def setSecurityMode(self, param):
        security_mode = param["s_mode"]
        dictSecurityMode5g = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        dictSecurityMode2g = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        for key in security_mode.keys():
            if key == '5G':
                self.__setSecurityMode(key, dictSecurityMode5g[security_mode[key]])
            if key == '2G':
                self.__setSecurityMode(key, dictSecurityMode2g[security_mode[key]])

    def __setWirelessMode(self, band, netMode):
        dictSecurityMode5g = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        dictSecurityMode2g = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        if "2G" == band:
            if (dictSecurityMode2g["WPA"] == self.securityMode2g or dictSecurityMode2g["WPA2/WPA"] == self.securityMode2g) and ("Mixed" == netMode or "Wireless-N Only" == netMode):
                if "Mixed" == self.netMode2g:
                    Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(netMode)
                else:
                    Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(netMode)
                    alert = driver.switch_to_alert()
                    alert.accept()
            else :
                Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(netMode)

        if "5G" == band:
            if (dictSecurityMode5g["WPA"] == self.securityMode5g or dictSecurityMode5g["WPA2/WPA"] == self.securityMode5g) and ("Mixed" == netMode or "Wireless-N Only" == netMode):
                if "Mixed" == self.netMode5g :
                    Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(netMode)
                else :
                    Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(netMode)
                    alert = driver.switch_to_alert()
                    alert.accept()
            else:
                Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(netMode)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()

        if "2G" == band:
            self.netMode2g = netMode
            if "Wireless-N Only" == netMode and self.securityMode2g != dictSecurityMode2g["WPA2"]:
                self.securityMode2g = dictSecurityMode2g["D"]
        if "5G" == band:
            self.netMode5g = netMode
            if "Wireless-N Only" == netMode and self.securityMode2g != dictSecurityMode5g["WPA2"]:
                self.securityMode5g = dictSecurityMode5g["D"]

    def setWirelessMode(self, param):
        dictMode5g = {'A':'Wireless-A Only', 'N':'Wireless-N Only', 'M':'Mixed'}
        dictMode2g = {'B/G':'Wireless-B/G Only', 'B':'Wireless-B Only', 'G':'Wireless-G Only', 'M':'Mixed', 'N':'Wireless-N Only'}
        netMode = param["netMode"]
        for key in netMode.keys():
            if "2G" == key:
                if netMode[key]=='D':                  
                    self.setRadioOFF(param)
                else:
                    self. __setWirelessMode(key, dictMode2g[netMode[key]])
            if "5G" == key:
                if netMode[key]=='D':
                    self.setRadioOFF(param)
                else:
                    self. __setWirelessMode(key, dictMode5g[netMode[key]])


    def setDns(self, params):
        ipaddr = params['DNS']
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("a").click()
        # set first number of DNS
        driver.find_element_by_id("dns00").clear()
        driver.find_element_by_id("dns00").send_keys(self.dns.split('.')[0])
        # set second number of DNS,and such as ....
        driver.find_element_by_id("dns01").clear()
        driver.find_element_by_id("dns01").send_keys(self.dns.split('.')[1])
        driver.find_element_by_id("dns02").clear()
        driver.find_element_by_id("dns02").send_keys(self.dns.split('.')[2])
        driver.find_element_by_id("dns03").clear()
        driver.find_element_by_id("dns03").send_keys(self.dns.split('.')[3])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        self.dns = ipaddr['2G']
        
    def setDhcp(self, params):
        dhcp = params["dhcp"]
        dictDhcp= {"E":"Enabled", "D":"Disabled"}
        driver = self.driver
        driver.get(self.base_url + "/")
        for key in dhcp.keys():
            if "2G" == key:
                if dhcp[key]=='D':
                    driver.find_element_by_xpath("(//input[@name='lan_proto'])[2]").click()
                elif dhcp[key]=='E':
                    driver.find_element_by_name("lan_proto").click()
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        self.dhcp=dictDhcp[dhcp[key]]

    def setParkingState(self):
        logger = log.Logger('setParkingState')
        ApBase.setParkingState(self)
        Logger.info('CiscoE3000 setParkingState')

         #set the name of your wireless
    def __setSSID(self, band, ssid):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        if band == '5G' and self.netMode5g != "Disabled":
            driver.find_element_by_name("wl1_ssid").clear()
            driver.find_element_by_name("wl1_ssid").send_keys(ssid)
        if band == '2G' and self.netMode2g != "Disabled":
            driver.find_element_by_name("wl0_ssid").clear()
            driver.find_element_by_name("wl0_ssid").send_keys(ssid)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        if band == '5G' and self.netMode5g != "Disabled":
            self.ssid5g = ssid
        if band == '2G' and self.netMode2g != "Disabled":
            self.ssid2g = ssid

    def setSSID(self, params):
        ssid = params["ssid"]
        for key in ssid.keys():
            self.__setSSID(key, ssid[key])

    def __setSsidBroadcast(self, band, ssidBroadcast):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        if band == '5G' and self.netMode5g != "Disabled":
            if ssidBroadcast == 'Enabled':
                driver.find_element_by_name("wl1_closed").click()
            elif ssidBroadcast == 'Disabled':
                driver.find_element_by_xpath("(//input[@name='wl1_closed'])[2]").click()
        if band == '2G' and self.netMode2g != "Disabled":
            if ssidBroadcast == 'Enabled':
                driver.find_element_by_name("wl0_closed").click()
            elif ssidBroadcast == 'Disabled':
                driver.find_element_by_xpath("(//input[@name='wl0_closed'])[2]").click()
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        if band == '5G' and self.netMode5g != "Disabled":
            self.ssidBroadcast5g = ssidBroadcast
        if band == '2G' and self.netMode2g != "Disabled":
            self.ssidBroadcast2g = ssidBroadcast

     #set your wireless will be found and display SSID
    def setSsidBroadcast(self, params):
        dictMode = {'D':'Disabled', 'E':'Enabled'}
        ssidBroadcast = params['ssidBroadcast']
        for key in ssidBroadcast.keys():
            self.__setSsidBroadcast(key, dictMode[ssidBroadcast[key]])

    def __setPassphrase(self, band, passphrase):
        #All Security Mode 
        dictSecurityMode5g = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        dictSecurityMode2g = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        driver = self.driver
        driver.get(self.base_url + "/")
        #click the Wireless tab
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("td.small > a").click()
        if band == "5G":
            if dictSecurityMode5g["WPA2/WPA"] == self.securityMode5g or dictSecurityMode5g["WPA2"] == self.securityMode5g or dictSecurityMode5g["WPA"] == self.securityMode5g:
                #'_wl1_wpa_psk' stand for the name of passphrase5g in web
                driver.find_element_by_name("wl1_wpa_psk").clear()
                driver.find_element_by_name("wl1_wpa_psk").send_keys(passphrase)
            elif dictSecurityMode5g["D"] == self.securityMode5g:
                pass
        if band == "2G":
            if dictSecurityMode2g["WPA2/WPA"] == self.securityMode2g or dictSecurityMode2g["WPA2"] == self.securityMode2g or dictSecurityMode2g["WPA"] == self.securityMode2g:
                driver.find_element_by_name("wl0_wpa_psk").clear()
                driver.find_element_by_name("wl0_wpa_psk").send_keys(passphrase)
            elif dictSecurityMode2g["D"] == self.securityMode2g:
                pass
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        if band == "5G":
            if dictSecurityMode5g["WPA2/WPA"] == self.securityMode5g or dictSecurityMode5g["WPA2"] == self.securityMode5g or dictSecurityMode5g["WPA"] == self.securityMode5g:
                self.passphrase5g = passphrase;
        if band == "2G":
            if dictSecurityMode2g["WPA2/WPA"] == self.securityMode2g or dictSecurityMode2g["WPA2"] == self.securityMode2g or dictSecurityMode2g["WPA"] == self.securityMode2g:
                self.passphrase2g = passphrase;

    def setPassphrase(self, param):
        passphrase = param["passphrase"]
        for key in passphrase.keys():
            self.__setPassphrase(key, passphrase[key])
