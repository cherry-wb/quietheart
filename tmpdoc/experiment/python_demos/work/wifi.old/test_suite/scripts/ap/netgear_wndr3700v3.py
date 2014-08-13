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
Netgear Wndr3700v3 Access point .
"""

class NetgearWndr3700v3(ApBase):
    def __init__(self, mac):
        self.mac = mac

    def initAp(self, dbcursor):
        for field in dbcursor:
            configName = field[DBApInfoColumns.ConfigName]
            memberName = db2memberTables[configName]
            configValue = field[DBApInfoColumns.ConfigValue]
            exec 'self.' + memberName + ' = configValue'

    def setDefaults(self, cursor):
        self.initAp(cursor)
    
    def resetDefault(self):
        self.openWebDriver()
        self.resetRoute()
        self.closeWebDriver()

    def resetRoute(self):
        def_params = {}
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
        self.__setWirelessMode('5G', defaultValue[ApMemberName.NETMODE5G])
        self.__setWirelessMode('2G', defaultValue[ApMemberName.NETMODE2G])
        self.__setChannel('5G', defaultValue[ApMemberName.CHANNEL5G])
        self.__setChannel('2G', defaultValue[ApMemberName.CHANNEL2G])
        self.__setSSID('5G', defaultValue[ApMemberName.SSID5G])
        self.__setSSID('2G', defaultValue[ApMemberName.SSID2G])
        self.__setSsidBroadcast('5G', defaultValue[ApMemberName.SSIDBROADCAST5G])
        self.__setSsidBroadcast('2G', defaultValue[ApMemberName.SSIDBROADCAST2G])


    def openWebDriver(self, params = None):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(30)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip
        self.driver.get(self.base_url + "/MNU_access_multiLogin2.htm")
        self.driver.find_element_by_name("yes").click()

    def setDns(self,params):
        ipaddr = params["DNS"]
        driver = self.driver
        driver.get(self.base_url + "/start.htm")
        #click Interent
        driver.find_element_by_css_selector("#INT_menu > span").click()
        #open the DNS frame 
        driver.get(self.base_url + "/BAS_ether.htm")
        time.sleep(3)
        #click radio box :Use These DNS Servers
        driver.find_element_by_xpath("(//input[@name='DNSAssign'])[2]").click()
        driver.find_element_by_name("DAddr1").clear()
        driver.find_element_by_name("DAddr1").send_keys(ipaddr["2G"].split('.')[0])
        driver.find_element_by_name("DAddr2").clear()
        driver.find_element_by_name("DAddr2").send_keys(ipaddr["2G"].split('.')[1])
        driver.find_element_by_name("DAddr3").clear()
        driver.find_element_by_name("DAddr3").send_keys(ipaddr["2G"].split('.')[2])
        driver.find_element_by_name("DAddr4").clear()
        driver.find_element_by_name("DAddr4").send_keys(ipaddr["2G"].split('.')[3])
        driver.find_element_by_name("apply").click()
        time.sleep(30)
        self.dns = ipaddr["2G"]
    
    def setParkingState(self):
        ApBase.setParkingState(self)

    def __setWirelessMode(self,band,netMode):
        driver = self.driver
        self.driver.get(self.base_url + "/start.htm")
        #click Wireless
        self.driver.find_element_by_css_selector("#WLS_menu > span").click()
        #open the Wireless frame 
        self.driver.get(self.base_url + "/WLG_wireless_dual_band.htm")       
        if band == '2G' :
            if self.securityMode2g == "WPA Personal":
                pass
            else:
                if self.securityMode2g == "Disabled" or self.securityMode2g == "WPA2 Personal":
                    #select Mode options of 2G
                    Select(driver.find_element_by_name("opmode")).select_by_visible_text(netMode)
                elif self.securityMode2g == "WPA2/WPA mixed Mode":
                    if netMode == "Up to 54 Mbps":
                        Select(driver.find_element_by_name("opmode")).select_by_visible_text(netMode)
                    else:
                        Select(driver.find_element_by_name("opmode")).select_by_visible_text(netMode)
                        # alert the dialog and accept
                        alert = driver.switch_to_alert()
                        alert.accept()
        elif band == '5G' :
            if self.securityMode5g == "WPA Personal":
                pass
            else:
                if self.securityMode5g == "Disabled" or self.securityMode5g == "WPA2 Personal":
                    #select Mode options of 5G
                    Select(driver.find_element_by_name("opmode_an")).select_by_visible_text(netMode)
                elif self.securityMode5g == "WPA2/WPA mixed Mode":
                    if netMode == "Up to 54 Mbps":                       
                        Select(driver.find_element_by_name("opmode_an")).select_by_visible_text(netMode)
                    else:
                        Select(driver.find_element_by_name("opmode_an")).select_by_visible_text(netMode)
                        alert = driver.switch_to_alert()
                        alert.accept()
        driver.find_element_by_name("Apply").click()
        time.sleep(30)
        if band == '2G':
            self.netMode2g = netMode
        if band == '5G':
            self.netMode5g = netMode

    def setWirelessMode(self,params):
        dictMode5g = {'A':'Up to 54 Mbps', 'N':'Up to 145 Mbps', 'NH':'Up to 300 Mbps'}
        dictMode2g = {'B':'Up to 54 Mbps', 'G':'Up to 145 Mbps', 'N':'Up to 300 Mbps'}
        netMode = params["netMode"]
        for key in netMode.keys():
            if "2G" == key :
                self.__setWirelessMode(key,dictMode2g[netMode[key]])
            elif "5G" == key :
                self.__setWirelessMode(key,dictMode5g[netMode[key]])

    def __setSecurityMode(self,band,securityMode):
        driver = self.driver
        self.driver.get(self.base_url + "/start.htm")
        self.driver.find_element_by_css_selector("#WLS_menu > span").click()
        self.driver.get(self.base_url + "/WLG_wireless_dual_band.htm")
        if band == '5G' :
            if self.netMode5g == "Up to 54 Mbps":
                if securityMode == "Disabled" :
                    #click Security Options->None option of 5G
                    driver.find_element_by_name("security_type_an").click()
                elif securityMode == "WPA Personal" :
                    #click Security Options->WPA-PSK [TKIP] option of 5G
                    driver.find_element_by_xpath("(//input[@name='security_type_an'])[3]").click()
                    driver.find_element_by_name("passphrase_an").clear()
                    #set Passphrase of 5G
                    driver.find_element_by_name("passphrase_an").send_keys(self.passphrase5g)
                elif securityMode == "WPA2 Personal" :
                    #click Security Options->WPA2-PSK [AES] option of 5G
                    driver.find_element_by_xpath("(//input[@name='security_type_an'])[4]").click()
                    driver.find_element_by_name("passphrase_an").clear()
                    driver.find_element_by_name("passphrase_an").send_keys(self.passphrase5g)
                elif securityMode == "WPA2/WPA mixed Mode" :
                    #click Security Options->WPA-PSK [TKIP] + WPA2-PSK [AES] option of 5G
                    driver.find_element_by_xpath("(//input[@name='security_type_an'])[5]").click()
                    driver.find_element_by_name("passphrase_an").clear()
                    driver.find_element_by_name("passphrase_an").send_keys(self.passphrase5g)
            else:
                if securityMode == "Disabled" :
                    driver.find_element_by_name("security_type_an").click()
                elif securityMode == "WPA2 Personal" :
                    driver.find_element_by_xpath("(//input[@name='security_type_an'])[4]").click()
                    driver.find_element_by_name("passphrase_an").clear()
                    driver.find_element_by_name("passphrase_an").send_keys(self.passphrase5g)
                elif securityMode == "WPA Personal" :
                    driver.find_element_by_xpath("(//input[@name='security_type_an'])[3]").click()
                    alert = driver.switch_to_alert()
                    alert.accept()
                    driver.find_element_by_name("passphrase_an").clear()
                    driver.find_element_by_name("passphrase_an").send_keys(self.passphrase5g)
                    self.netMode5g = "Up to 54 Mbps"
                elif securityMode == "WPA2/WPA mixed Mode" and self.securityMode5g != "WPA2/WPA mixed Mode":
                    if securityMode == "WPA2/WPA mixed Mode" and self.securityMode5g == "WPA Personal":
                        driver.find_element_by_xpath("(//input[@name='security_type_an'])[5]").click()
                    else:
                        driver.find_element_by_xpath("(//input[@name='security_type_an'])[5]").click()
                        alert = driver.switch_to_alert()
                        alert.accept()
                    driver.find_element_by_name("passphrase_an").clear()
                    driver.find_element_by_xpath("(//input[@name='passphrase_an'])").send_keys(self.passphrase5g)
                  #  driver.find_element_by_name("passphrase_an").send_keys(self.passphrase5g)

        elif band == '2G' :
            if self.netMode2g == "Up to 54 Mbps":
                if securityMode == "Disabled" :
                    #click Security Options->None option of 2G
                    driver.find_element_by_name("security_type").click()
                elif securityMode == "WPA Personal" :
                    #click Security Options->WPA-PSK [TKIP] option of 2G
                    driver.find_element_by_xpath("(//input[@name='security_type'])[3]").click()
                    driver.find_element_by_name("passphrase").clear()
                    driver.find_element_by_name("passphrase").send_keys(self.passphrase2g)
                elif securityMode == "WPA2 Personal" :
                    #click Security Options->WPA2-PSK [AES] option of 2G
                    driver.find_element_by_xpath("(//input[@name='security_type'])[4]").click()
                    driver.find_element_by_name("passphrase").clear()
                    driver.find_element_by_name("passphrase").send_keys(self.passphrase2g)
                elif securityMode == "WPA2/WPA mixed Mode" :
                    #click Security Options->WPA-PSK [TKIP] + WPA2-PSK [AES] option of 2G
                    driver.find_element_by_xpath("(//input[@name='security_type'])[5]").click()
                    driver.find_element_by_name("passphrase").clear()
                    driver.find_element_by_name("passphrase").send_keys(self.passphrase2g)
            else:
                if securityMode == "Disabled" :
                    driver.find_element_by_name("security_type").click()
                elif securityMode == "WPA2 Personal" :
                    driver.find_element_by_xpath("(//input[@name='security_type'])[4]").click()
                    driver.find_element_by_name("passphrase").clear()
                    driver.find_element_by_name("passphrase").send_keys(self.passphrase2g)
                elif securityMode == "WPA Personal" :
                    driver.find_element_by_xpath("(//input[@name='security_type'])[3]").click()
                    alert = driver.switch_to_alert()
                    alert.accept()
                    driver.find_element_by_name("passphrase").clear()
                    driver.find_element_by_name("passphrase").send_keys(self.passphrase2g)
                    self.netMode2g = "Up to 54 Mbps"
                elif securityMode == "WPA2/WPA mixed Mode" and self.securityMode2g != "WPA2/WPA mixed Mode":
                    if securityMode == "WPA2/WPA mixed Mode" and self.securityMode2g != "WPA Personal":
                        driver.find_element_by_xpath("(//input[@name='security_type'])[5]").click()
                    else:
                        driver.find_element_by_xpath("(//input[@name='security_type'])[5]").click()
                        alert = driver.switch_to_alert()
                        alert.accept()
                    driver.find_element_by_name("passphrase").clear()
                    driver.find_element_by_name("passphrase").send_keys(self.passphrase2g)

        driver.find_element_by_name("Apply").click()
        time.sleep(35)
        if band == '5G':
            self.securityMode5g = securityMode
        if band == '2G':
            self.securityMode2g = securityMode

    def setSecurityMode(self,params):
        security_mode = params["s_mode"]
        dict_SecurityMode_5G = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        dict_SecurityMode_2G = {"WPA2/WPA":"WPA2/WPA mixed Mode", "WPA2":"WPA2 Personal", "WPA":"WPA Personal", "D":"Disabled"}
        for key in security_mode.keys():
               self.__setSecurityMode(key, dict_SecurityMode_5G[security_mode[key]])


    def __setSSID(self,band,ssid):
         driver = self.driver
         driver.get(self.base_url + "/start.htm")
         driver.find_element_by_css_selector("#WLS_menu > span").click()
         driver.get(self.base_url + "/WLG_wireless_dual_band.htm")   
         if "2G" ==band :
             driver.find_element_by_name("ssid").clear()
             #set Name (SSID) of 2G
             driver.find_element_by_name("ssid").send_keys(ssid)
         if "5G" == band:
             driver.find_element_by_name("ssid_an").clear()
             ##set Name (SSID) of 5G
             driver.find_element_by_name("ssid_an").send_keys(ssid)
         driver.find_element_by_name("Apply").click()
         driver.switch_to_default_content
         time.sleep(30)
         if "5G" == band:
             self.ssid5g = ssid
         if "2G" == band :
             self.ssid2g = ssid

    def setSSID(self,params):
        ssid = params["ssid"]
        if ssid["2G"] == ssid["5G"]:
            pass
        else :
            for key in ssid.keys():
                self.__setSSID(key,ssid[key])

    def __setSsidBroadcast(self,band,ssidBroadcast):
        self.ssidBroadcast2g = ssidBroadcast
        driver = self.driver
        driver.get(self.base_url + "/start.htm")
        driver.find_element_by_css_selector("#WLS_menu > span").click()
        driver.get(self.base_url + "/WLG_wireless_dual_band.htm")
        if "2G" ==band:
            if (driver.find_element_by_name("ssid_bc").is_selected() and ssidBroadcast == "Enabled") or ( driver.find_element_by_name("ssid_bc").is_selected() == False and ssidBroadcast == "Disabled") :
               pass
            else:
                #click Enable SSID Broadcast of 2G
                driver.find_element_by_name("ssid_bc").click()
        if "5G" ==band:
            if (driver.find_element_by_name("ssid_bc").is_selected() and ssidBroadcast == "Enabled") or ( driver.find_element_by_name("ssid_bc").is_selected() == False and ssidBroadcast == "Disabled") :
               pass
            else:
                #click Enable SSID Broadcast of 5G
                driver.find_element_by_name("ssid_bc_an").click()
        driver.find_element_by_name("Apply").click()
        time.sleep(30)
        if "5G" == band:
            self.ssidBroadcast5g = ssidBroadcast
        if "2G" == band:
            self.ssidBroadcast2g = ssidBroadcast

    def setSsidBroadcast(self,params):
        dictSsidBroadcast={"E":"Enabled","D":"Disabled"}
        ssidBroadcast = params["ssidBroadcast"]
        for key in ssidBroadcast.keys() :
            self.__setSsidBroadcast(key,dictSsidBroadcast[ssidBroadcast[key]])

    def __setChannel(self,band,channel):
        option ="option[value=\""+channel+"\"]"
        driver = self.driver
        driver.get(self.base_url + "/start.htm")
        driver.find_element_by_css_selector("#WLS_menu > span").click()
        driver.get(self.base_url + "/WLG_wireless_dual_band.htm")
        #select Channel option 
        driver.find_element_by_name("w_channel_an").click()
        if "5G" == band :
            Select(driver.find_element_by_name("w_channel_an")).select_by_visible_text(channel)
            if int(channel) < 149 and int(self.channel5g) >= 149:
               #alert the dialog
               alert=driver.switch_to_alert();
               alert.accept()
            driver.find_element_by_css_selector(option).click()
        if "2G" == band:
            Select(driver.find_element_by_name("w_channel")).select_by_visible_text(channel)
        driver.find_element_by_name("Apply").click()
        time.sleep(30)
        if "5G" == band:
            self.channel5g = channel
        if "2G" == band:
            self.channel2g = channel

    def setChannel(self,params):
        dictChannel5g = {'36':'36', '40':'40', '44':'44', '48':'48', '149':'149', '153':'153', '157':'157', '161':'161', '165':'165'}
        dictChannel2g = {'1':'01', '2':'02', '3':'03', '4':'04', '5':'05', '6':'06', '7':'07', '8':'08', '9':'09', '10':'10', '11':'11', "A":"Auto"}
        channel = params["channel"]
        for key in channel.keys() :
            if "5G" == key and "Disabled" != self.netMode5g :
                self.__setChannel(key,dictChannel5g[channel[key]])
            if "2G" == key and "Disabled" != self.netMode2g :
                self.__setChannel(key,dictChannel2g[channel[key]])

    def __setPassphrase(self,band,passphrase):
        driver = self.driver
        driver.get(self.base_url + "/start.htm")
        driver.find_element_by_css_selector("#WLS_menu > span").click()
        driver.get(self.base_url + "/WLG_wireless_dual_band.htm")
        if band=='5G':
            if 'Disabled' ==self.securityMode5g or 'WEP' ==self.securityMode5g:
                pass
            else:
                driver.find_element_by_name("passphrase_an").clear()
                driver.find_element_by_name("passphrase_an").send_keys(passphrase)
                driver.find_element_by_name("Apply").click()
                time.sleep(30)
                self.passphrase5g = passphrase;
        if band=='2G':
            if 'Disabled' ==self.securityMode2g or 'WEP' ==self.securityMode2g:
                pass
            else:
                driver.find_element_by_name("passphrase").clear()
                driver.find_element_by_name("passphrase").send_keys(passphrase)
                driver.find_element_by_name("Apply").click()
                time.sleep(30)
                self.passphrase2g = passphrase;

    def setPassphrase(self,params):
        passphrase = params["passphrase"]
        for key in passphrase.keys():
            self.__setPassphrase(key,passphrase[key])

