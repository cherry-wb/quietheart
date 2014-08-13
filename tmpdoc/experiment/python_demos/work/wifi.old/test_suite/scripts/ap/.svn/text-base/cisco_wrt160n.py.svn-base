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
Cisco WRT160N Access point .
"""

class CiscoWRT160N(ApBase):
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
        #TODO, getDefaults() not reasonable, need to restructure
        db.connect()
        cursor = db.getDefaults(self)
        db.disconnect()

        defaultValue = {}
        for field in cursor:
            configName = field[DBApInfoColumns.ConfigName]
            memberName = db2memberTables[configName]
            defaultValue[memberName] = field[DBApInfoColumns.ConfigValue]
  
        self.__setWirelessMode(defaultValue[ApMemberName.NETMODE2G])
        self.__setChannelWidth(defaultValue[ApMemberName.CHANNELWIDTH2G])
        self.__setChannel(defaultValue[ApMemberName.CHANNEL2G])
        self.__setSSID(defaultValue[ApMemberName.SSID2G])
        self.__setSsidBroadcast(defaultValue[ApMemberName.SSIDBROADCAST2G])
        self.__setSecurityMode(defaultValue[ApMemberName.SECURITYMODE2G])
       
    def openWebDriver(self, params=None):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(20)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip

    def setParkingState(self):
        ApBase.setParkingState(self)

    def setDns(self, params):
        ipaddr = params["DNS"]
        driver = self.driver
        driver.get(self.base_url + "/")
        #clear the first num of Static DNS 1
        driver.find_element_by_id("dns00").clear()
        #set the first num of Static DNS 1
        driver.find_element_by_id("dns00").send_keys(self.dns.split('.')[0])
        driver.find_element_by_id("dns01").clear()
        driver.find_element_by_id("dns01").send_keys(self.dns.split('.')[1])
        driver.find_element_by_id("dns02").clear()
        driver.find_element_by_id("dns02").send_keys(self.dns.split('.')[2])
        driver.find_element_by_id("dns03").clear()
        driver.find_element_by_id("dns03").send_keys(self.dns.split('.')[3])
        driver.find_element_by_id("divBT1").click()
        #click Save Settings button
        driver.find_element_by_name("btaction").click()
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
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.dhcp=dictDhcp[dhcp[key]]
        


    def __setWirelessMode(self, netMode):
        driver = self.driver
        driver.get(self.base_url + "/")
        #click Wireless
        driver.find_element_by_link_text("Wireless").click()
	    #Select netMode 
        Select(driver.find_element_by_name("wl_net_mode")).select_by_visible_text(netMode)
        #click Save Settings button 
        driver.find_element_by_id("divBT1").click()
	    #click continue
        driver.find_element_by_name("btaction").click()
        self.netMode2g = netMode

    def setWirelessMode(self, params):
        netMode= params["netMode"]
        dictMode= {"M":"Mixed", "B":"Wireless-B Only", "G":"Wireless-G Only", "N":"Wireless-N Only", "BG":"BG-Mixed"}
        for key in netMode.keys():
            if "2G" == key:
                if netMode[key]=='D':                  
                    self.setRadioOFF(params)
                else:
                    self.__setWirelessMode(dictMode[netMode[key]])

    def setRadioOFF(self, params):
        netMode = params["netMode"]
        #there is a blank before this value
        dictMode = {"D":" Disabled"} 
        for key in  netMode.keys():
            if "2G" == key:
               self.__setWirelessMode(dictMode[netMode[key]])

    def __setSSID(self, ssid):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        #clear Network Name (SSID)
        driver.find_element_by_name("wl_ssid").clear()
        #set Network Name (SSID)
        driver.find_element_by_name("wl_ssid").send_keys(ssid)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.ssid2g = ssid

    def setSSID(self, params):
        #there is a blank before this value
        if self.netMode2g == ' Disabled':
            pass
        else:
            ssid = params['ssid']
            for key in ssid.keys():
                if key == '2G':
                    self.__setSSID(ssid[key])
                else:
                    pass
    
    def __setChannelWidth(self, channelWidth):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        #Select channelWidth
        Select(driver.find_element_by_name("_wl_nbw")).select_by_visible_text(channelWidth)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        if channelWidth=='Auto (20MHz or 40MHz)':
            self.channelWidth2g=channelWidth
            self.channel2g='Auto'
        else:
            self.channelWidth2g=channelWidth         

    def setChannelWidth(self, params):
        channelWidth= params["channelwidth"]
        dictChannelWidth= {"20":"20MHz only", "A":"Auto (20MHz or 40MHz)"}
        if " Disabled" == self.netMode2g or "Wireless-B Only"== self.netMode2g or "Wireless-G Only"== self.netMode2g or "BG-Mixed"== self.netMode2g:
            pass
        else:
            for key in channelWidth.keys():
                if "2G" == key:
                    self.__setChannelWidth(dictChannelWidth[channelWidth[key]])
 
    def __setChannel(self, channel):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
		#Select channel option
        Select(driver.find_element_by_name("wl_schannel")).select_by_visible_text(channel)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.channel2g=channel

    def setChannel(self, params):
        channel= params["channel"]
        dictChannel={'A':"Auto"}
        #there is a blank before this value
        if " Disabled" == self.netMode2g :
            pass
        elif self.channelWidth2g=='Auto (20MHz or 40MHz)':
            self.channel2g='Auto'
        else:
            for key in channel.keys():
                if "2G" == key:
                    if "A"==channel['2G']:
                        self.__setChannel(dictChannel[channel[key]])                    
                    else:
                        self.__setChannel(channel[key])

    def __setSsidBroadcast(self, ssidBroadcast):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        #set ssidBroadcast
        if ssidBroadcast =='Disabled':
            #click Enabled
			driver.find_element_by_xpath("(//input[@name='wl_closed'])[2]").click()
        elif ssidBroadcast =='Enabled':
            #click Disabled
        	driver.find_element_by_name("wl_closed").click()
        #Save
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.ssidBroadcast2g = ssidBroadcast

    def setSsidBroadcast(self, params):
        ssidBroadcast = params['ssidBroadcast']
        dictSsidBroadcast = {'E':'Enabled', 'D':'Disabled'}
        #there is a blank before this value
        if self.netMode2g ==' Disabled':
            pass
        else:
            for key in ssidBroadcast.keys():
                if key == '2G':
                    self.__setSsidBroadcast(dictSsidBroadcast[ssidBroadcast[key]])

    def __setSecurityMode(self,securityMode):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        #click wireless Security
        driver.find_element_by_link_text("Wireless Security").click()
        #select securityMode
        Select(driver.find_element_by_name("security_mode2")).select_by_visible_text(securityMode)
        #set passphrase
        if securityMode!='Disabled': 
            driver.find_element_by_name("wl_wpa_psk").clear()
            driver.find_element_by_name("wl_wpa_psk").send_keys(self.passphrase2g)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.securityMode2g = securityMode
        
        
    def setSecurityMode(self, params):
        securityMode = params["s_mode"]
        dictSecurityMode = {'WPA2':'WPA2 Personal', 'WPA':'WPA Personal','D':'Disabled'}
        for key in securityMode.keys():
            if key == '2G':
                self.__setSecurityMode(dictSecurityMode[securityMode[key]])

    def __setAlgorithms(self,algorithms):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        driver.find_element_by_link_text("Wireless Security").click()
        #select Encryption
        Select(driver.find_element_by_css_selector("select[name=\"wl_crypto\"]")).select_by_visible_text(algorithms)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.algorithms2g=algorithms

    def setAlgorithms(self, params):
        algorithms = params["algorithms"]
        dictAlgorithms = {'A':'AES','T/A':'TKIP+AES'}
        for key in algorithms.keys():
            if key == '2G':
                if self.securityMode2g == 'WPA2 Personal':
                    self.__setAlgorithms(dictAlgorithms[algorithms[key]])
                else:
                    pass

    def __setPassphrase(self,passphrase):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        #click Wireless Security
        driver.find_element_by_link_text("Wireless Security").click()
        #clear Passphrase
        driver.find_element_by_name("wl_wpa_psk").clear()
        #set Passphrase
        driver.find_element_by_name("wl_wpa_psk").send_keys(passphrase)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.passphrase2g=passphrase

    def setPassphrase(self, params):
        passphrase = params["passphrase"]
        dictSecurityMode = {'WPA2':'WPA2 Personal', 'WPA':'WPA Personal','D':'Disabled'}
        for key in passphrase.keys():
            if key == '2G':
                if self.securityMode2g == "Disabled":
                    pass                   
                else:
                    self.__setPassphrase(passphrase[key])
    
    def __setKeyRenewal(self,keyRenewal):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_link_text("Wireless").click()
        driver.find_element_by_link_text("Wireless Security").click()
        #clear KeyRenewal
        driver.find_element_by_name("wl_wpa_gtk_rekey").clear()
        #set KeyRenewal
        driver.find_element_by_name("wl_wpa_gtk_rekey").send_keys(keyRenewal)
        driver.find_element_by_id("divBT1").click()
        driver.find_element_by_name("btaction").click()
        self.keyRenewal2g = keyRenewal
    
    def setKeyRenewal(self, params):
        keyRenewal = params['keyRenewal']
        for key in keyRenewal.keys():
            if key == '2G':
                if self.securityMode2g == 'Disabled':
                    pass
                else:
                    self.__setKeyRenewal(keyRenewal[key])                    

