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
Cisco E3200 Access point .
"""
class CiscoE3200(ApBase):
    def __init__(self, mac):
        "Initiate object and then initialize all members with initAp()"
        self.mac = mac

    def initAp(self, dbcursor):
        for field in dbcursor:
            configName = field[DBApInfoColumns.ConfigName]
            memberName = db2memberTables[configName]
            configValue = field[DBApInfoColumns.ConfigValue]
            exec 'self.' + memberName + ' = configValue'

    def setDefaults(self, cursor):
        self.initAp(cursor)

    #set wireless netmode Disabled        
    def setRadioOFF(self,params):
        netMode  = params["netMode"]
        dictMode = {'D':'Disabled'}
        driver   = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        for key in netMode.keys():
            if "5G" == key:
                netMode5g = netMode[key]
                Select(driver.find_element_by_name("net_mode_5g")).select_by_visible_text(dictMode[netMode5g])
            if "2G" == key :
                netMode2g = netMode[key]
                Select(driver.find_element_by_name("net_mode_24g")).select_by_visible_text(dictMode[netMode2g])
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("action").click()
        for key in netMode.keys():
            if "5G" == key:
                self.netMode5g = dictMode[netMode5g]
            if "2G" == key :
                self.netMode2g = dictMode[netMode2g]

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

    def openWebDriver(self, params = None):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(20)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip
  
    def setDns(self):
        ipaddr = params["DNS"]
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_id("dns00").clear()
        # set first number of DNS
        driver.find_element_by_id("dns00").send_keys(self.dns.split('.')[0])
        driver.find_element_by_id("dns01").clear()
        # set second number of DNS,and such as ....
        driver.find_element_by_id("dns01").send_keys(self.dns.split('.')[1])
        driver.find_element_by_id("dns02").clear()
        driver.find_element_by_id("dns02").send_keys(self.dns.split('.')[2])
        driver.find_element_by_id("dns03").clear()
        driver.find_element_by_id("dns03").send_keys(self.dns.split('.')[3])
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("action").click()
        self.dns = ipaddr["2G"]


    def setParkingState(self):
        logger = log.logger("setParkingState")
        ApBase.setParkingState(self)
        logger('CiscoE3200 setParkingState')
        


    def __setWirelessMode(self,band,netMode):
        logger = log.Logger("__setWirelessMode")
        logger.debug("")
        #All Security Mode 
        dictSecurityMode5G = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA     Personal", "D":"Disabled"}
        dictSecurityMode2G = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA     Personal", "D":"Disabled"}
        driver = self.driver
        driver.get(self.base_url + "/")
        #click the Wireless tab
        driver.find_element_by_link_text("Wireless").click()
        if "5G" == band :
            if (dictSecurityMode5G["WPA"] == self.securityMode5g or dictSecurityMode5G["WPA2/WPA"] == self.securityMode5g) and ("Mixed" == netMode or "Wireless-N Only" == netMode):
               if "Mixed" == self.netMode5g :
                   #select the net_mode
                   Select(driver.find_element_by_name("net_mode_5g")).select_by_visible_text(netMode)
               else :
                   Select(driver.find_element_by_name("net_mode_5g")).select_by_visible_text(netMode)
                    #if a window is popuped ,it will be click the 'OK'/'Accept' 
                   alert = driver.switch_to_alert()
                   alert.accept()
        else:
            Select(driver.find_element_by_name("net_mode_5g")).select_by_visible_text(netMode)
        if "2G" == band :
            if (dictSecurityMode2G["WPA"] == self.securityMode2g or dictSecurityMode2G["WPA2/WPA"] == self.securityMode2g) and ("Mixed" == netMode or "Wireless-N Only" == netMode):
                if "Mixed" == self.netMode2g:
                    Select(driver.find_element_by_name("net_mode_24g")).select_by_visible_text(netMode)
                else :
                    Select(driver.find_element_by_name("net_mode_24g")).select_by_visible_text(netMode)
                    alert = driver.switch_to_alert()
                    alert.accept()
        else:
            Select(driver.find_element_by_name("net_mode_24g")).select_by_visible_text(netMode)
         #click the save setting    
        driver.find_element_by_id("divBT1").click()
         #click the menu of continue
        driver.find_element_by_name("action").click()
        if "2G" == band:
           self.netMode2g = netMode
           if "Wireless-N Only" == netMode and self.securityMode2g != dictSecurityMode2G["WPA2"]:
               self.securityMode2g = dictSecurityMode2G["D"]
        if "5G" == band:
           self.netMode5g = netMode
           if "Wireless-N Only" == netMode and self.securityMode2g != dictSecurityMode5G["WPA2"]:
                self.securityMode5g = dictSecurityMode5G["D"]

    def setWirelessMode(self,params):
        logger = log.Logger("setWirelessMode")
        logger.debug("")
        dictMode5g = {'A':'Wireless-A Only', 'N':'Wireless-N Only', 'M':'Mixed'}
        dictMode2g = {'B/G':'Wireless-B/G Only', 'B':'Wireless-B Only', 'G':'Wireless-G Only', 'M':'M    ixed', 'N':'Wireless-N Only'}
        netMode = params["netMode"]
        for key in netMode.keys():
            if "2G" == key :
                self.__setWirelessMode(key,dictMode2g[netMode[key]])
            elif "5G" == key :
                self.__setWirelessMode(key,dictMode5g[netMode[key]])
       
    def __setSSID(self,band,ssid):
         logger = log.Logger("__setSSID")
         logger.debug("")
         driver = self.driver
         driver.get(self.base_url + "/")
        #click the Wireless tab
         driver.find_element_by_link_text("Wireless").click()
         if "5G" == band :
             driver.find_element_by_name("ssid_5g").clear()
             driver.find_element_by_name("ssid_5g").send_keys(ssid)
         if "2G" == band :
             driver.find_element_by_name("ssid_24g").clear()
             driver.find_element_by_name("ssid_24g").send_keys(ssid)
         #click the save setting    
         driver.find_element_by_id("divBT1").click()
         #click the menu of continue
         driver.find_element_by_name("action").click()

         if "5G" == band:
             self.ssid5g = ssid
         if "2G" == band :
             self.ssid2g = ssid

         #set the name of your wireless
    def setSSID(self,params):
        logger = log.Logger("setSSID")
        logger.debug("setSSID")
        ssid = params["ssid"]
        for key in ssid.keys():
            self.__setSSID(key,ssid[key])

    def __setSsidBroadcast(self,band,ssidBroadcast):
        logger = log.Logger("__setSsidBroadcast")
        logger.debug("")
        driver = self.driver
        driver.get(self.base_url + "/")
        #click the Wireless tab
        driver.find_element_by_link_text("Wireless").click()
        if "5G" == band and "Disabled" != self.netMode5g:
            if "Enabled"  == ssidBroadcast or "enabled"  == ssidBroadcast:
                driver.find_element_by_name("closed_5g").click()
            elif "Disabled" == ssidBroadcast :
                driver.find_element_by_xpath("(//input[@name='closed_5g'])[2]").click()
        if "2G" == band and "Disabled" != self.netMode2g:
            if "Enabled" == ssidBroadcast or "enabled" == ssidBroadcast :
                driver.find_element_by_name("closed_24g").click()
            elif "Disabled" == ssidBroadcast :
                driver.find_element_by_xpath("(//input[@name='closed_24g'])[2]").click()
         #click the save setting    
        driver.find_element_by_id("divBT1").click()
         #click the menu of continue
        driver.find_element_by_name("action").click()
        if "5G" == band and "Disabled" != self.netMode5g:
           self.ssidBroadcast5g = ssidBroadcast
        if "2G" == band and "Disabled" != self.netMode2g:
           self.ssidBroadcast2g = ssidBroadcast

     #set your wireless will be found and display SSID
    def setSsidBroadcast(self,params):
        logger = log.Logger("setSsidBroadcast")
        logger.debug("")
        dictSsidBroadcast={"E":"Enabled","D":"Disabled"}
        ssidBroadcast = params["ssidBroadcast"]
        for key in ssidBroadcast.keys() :
            self.__setSsidBroadcast(key,dictSsidBroadcast[ssidBroadcast[key]])


    def __setChannel(self,band,channel):
        logger = log.Logger("__setChannel")
        logger.debug("")
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        if "5G" == band :
            #'_wl1_channel' stand for the name of channel5g in web
            Select(driver.find_element_by_name("_wl1_channel")).select_by_visible_text(channel)
        if "2G" == band :
            #'_wl0_channel' stand for the name of channel2g in web
           Select(driver.find_element_by_name("_wl0_channel")).select_by_visible_text(channel)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("action").click()
        if "5G" == band :
           self.channel5g == channel
        if "2G" == band :
           self.channel2g == channel

    def setChannel(self,params):
        logger = log.Logger("setChannel")
        logger.debug("")
        dictChannel5g = {'36':'36 - 5.180GHz', '40':'40 - 5.200GHz', '44':'44 - 5.220GHz', '48':'48 - 5.240GHz', '149':'149 - 5.745GHz', '153':'153 - 5.    765GHz', '157':'157 - 5.785GHz', '161':'161 - 5.805GHz', "A":"Auto (DFS)"}
        dictChannel2g = {'1':'1 - 2.412GHZ', '2':'2 - 2.417GHZ', '3':'3 - 2.422GHZ', '4':'4 - 2.427GHZ', '5':'5 - 2.432GHZ', '6':'6 - 2.437GHZ', '7':'7     - 2.442GHZ', '8':'8 - 2.447GHZ', '9':'9 - 2.452GHZ', '10':'10 - 2.457GHZ', '11':'11 - 2.462GHZ', "A":"Auto"}
        channel = params["channel"]
        for key in channel.keys() :
            if "5G" == key and "Disabled" != self.netMode5g :
                self.__setChannel(key,dictChannel5g[channel[key]])
            if "2G" == key and "Disabled" != self.netMode2g :
                self.__setChannel(key,dictChannel2g[channel[key]])

    def __setChannelWidth(self,band,channelWidth):
        logger = log.Logger("__setChannelWidth")
        logger.debug("")
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        if "5G" == band:
            #'_wl1_nbw' stand for the name of channelWidth5g in web
            Select(driver.find_element_by_name("_wl1_nbw")).select_by_visible_text(channelWidth)
        if "2G" == band:
            Select(driver.find_element_by_name("_wl0_nbw")).select_by_visible_text(channelWidth)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("action").click()
        if "5G" == band and channelWidth != self.channelWidth5g:
            self.channelWidth5g = channelWidth
            self.channel5g  = "Auto (DFS)"
        if "2G" == band and channelWidth != self.channelWidth2g:
            self.channelWidth2g = channelWidth
            self.channel2g  = "Auto"

    def setChannelWidth(self,params):
        logger = log.Logger("setChannelWidth")
        logger.debug("")
        channelWidth = params["channelwidth"]
        dictChannelWidth2G = {"A":"Auto (20 MHz or 40 MHz)", "20":"20 MHz Only"}
        dictChannelWidth5G = {"A":"Auto (20 MHz or 40 MHz)", "20":"20 MHz Only", "40":"40 MHz Only"}
        for key in channelWidth.keys():
            if "5G" == key and "Disabled" != self.netMode5g and "Wireless-A Only" != self.netMode5g :
                self.__setChannelWidth(key,dictChannelWidth5G[channelWidth[key]])
            if "2G" == key and "Disabled" != self.netMode2g and "Wireless-A Only" != self.netMode2g :
                self.__setChannelWidth(key,dictChannelWidth2G[channelWidth[key]])

    def __setSecurityMode(self,band,securityMode):
       logger = log.Logger("__setSecurityMode")
       logger.debug("")
       driver = self.driver
       driver.get(self.base_url + "/")
       driver.find_element_by_link_text("Wireless").click()
       driver.find_element_by_link_text("Wireless Security").click()

       if band == '5G' :
           if self.netMode5g == 'Mixed' and  self.securityMode5g != 'WPA Personal':
              if securityMode == "WPA Personal" :
                   Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(securityMode)
                   alert = driver.switch_to_alert()
                   alert.accept()
              else :
                   Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(securityMode)
           else : 
                if self.netMode5g == 'Wireless-N Only' :
                   if securityMode == "WPA2/WPA mixed Mode" or securityMode == "WPA Personal":
                     logger.debug(" There are two modes : WPA2 Personal and Disabled")
                   else:   
                     Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(securityMode)
                Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(securityMode)
       if band == '2G' :
           if self.netMode2g == 'Mixed' and  self.securityMode2g != 'WPA Personal':
              if securityMode == "WPA Personal" :
                   Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(securityMode)
                   alert = driver.switch_to_alert()
                   alert.accept()
              else :
                   Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(securityMode)
           else : 
                if self.netMode2g == 'Wireless-N Only' :
                   if securityMode == "WPA2/WPA mixed Mode" or securityMode == "WPA Personal":
                     logger.debug(" There are two modes : WPA2 Personal and Disabled")
                   else:   
                     Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(securityMode)
                Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(securityMode)
       driver.find_element_by_id("divBT1").click()
       driver.find_element_by_name("action").click()
       if band == '5G':
           self.securityMode5g = securityMode
       if band == '2G':
            self.securityMode2g = securityMode

    def setSecurityMode(self,params):
        logger = log.Logger("setSecurityMode")
        logger.debug("")
        security_mode = params["s_mode"]
        dict_SecurityMode_5G = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        dict_SecurityMode_2G = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        for key in security_mode.keys():
               self.__setSecurityMode(key, dict_SecurityMode_5G[security_mode[key]])

    def __setPassphrase(self,band,passphrase):
        logger = log.Logger("__setPassphrase")
        logger.debug("")
        dictSecurityMode5G={"WPA2/WPA":"WPA2/WPA mixed Mode","WPA2":"WPA2 Personal","WPA":"WPA Personal","D":"Disabled"}
        dictSecurityMode2G={"WPA2/WPA":"WPA2/WPA mixed Mode","WPA2":"WPA2 Personal","WPA":"WPA Personal","D":"Disabled"}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        driver.find_element_by_link_text("Wireless Security").click()
        if "5G" == band :
           if dictSecurityMode5G["WPA2/WPA"] ==self.securityMode5g or dictSecurityMode5G["WPA2"] == self.securityMode5g or dictSecurityMode5G["WPA"] == self.securityMode5g:
                #'_wl1_wpa_psk' stand for the name of passphrase5g in web
                driver.find_element_by_name("wl1_wpa_psk").clear()
                driver.find_element_by_name("wl1_wpa_psk").send_keys(passphrase)
           elif dictSecurityMode5G["D"] ==self.securityMode5g:
                pass
        if "2G" == band :
           if dictSecurityMode2G["WPA2/WPA"] ==self.securityMode2g or dictSecurityMode2G["WPA2"] == self.securityMode2g or dictSecurityMode2G["WPA"] == self.securityMode2g:
                driver.find_element_by_name("wl0_wpa_psk").clear()
                driver.find_element_by_name("wl0_wpa_psk").send_keys(passphrase)
           elif dictSecurityMode2G["D"] ==self.securityMode2g:
                 pass
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("action").click()
        if band == "5G":
           if dictSecurityMode5G["WPA2/WPA"] ==self.securityMode5g or dictSecurityMode5G["WPA2"] == self.securityMode5g or dictSecurityMode5G["WPA"] == self.securityMode5g:
                self.passphrase5g = passphrase;
        if band == "2G":
           if dictSecurityMode2G["WPA2/WPA"] ==self.securityMode2g or dictSecurityMode2G["WPA2"] == self.securityMode2g or dictSecurityMode2G["WPA"] == self.securityMode2g:
                self.passphrase2g = passphrase;

    def setPassphrase(self,params):
        logger = log.Logger("setPassphrase")
        logger.debug("")
        passphrase = params["passphrase"]
        for key in passphrase.keys():
            self.__setPassphrase(key,passphrase[key])

