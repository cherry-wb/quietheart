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
Cisco WRT54GL Access point .
"""

class CiscoWRT54GL(ApBase):

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

        self.__setWirelessMode(defaultValue[ApMemberName.NETMODE2G])
        self.__setSSID(defaultValue[ApMemberName.SSID2G])
        self.__setSsidBroadcast(defaultValue[ApMemberName.SSIDBROADCAST2G])
        self.__setChannel(defaultValue[ApMemberName.CHANNEL2G])
        self.__setSecurityMode(defaultValue[ApMemberName.SECURITYMODE2G])

    def openWebDriver(self, params = None):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(20)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip

    def reboot(self):
        ApBase.reboot(self)
        logger = log.Logger("CiscoWRT54GL reboot")

    def __setChannel(self, channel):
        driver = self.driver
        driver.get(self.base_url + "/")
        #choose wireless setting page
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        #choose wireless channel and click
        Select(driver.find_element_by_name("wl_channel")).select_by_visible_text(channel)
        #save changes
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        self.channel2g = channel

    def setChannel(self, params):
        channel = params["channel"]
        dictChannel = {"1":" 1 - 2.412GHZ", "2":" 2 - 2.417GHZ", "3":" 3 - 2.422GHZ", "4":" 4 - 2.427GHZ", "5":" 5 - 2.432GHZ", "6":" 6 - 2.437GHZ", "7":" 7 - 2.442GHZ", "8":" 8 - 2.447GHZ", "9":" 9 - 2.452GHZ", "10":" 10 - 2.457GHZ", "11":" 11 - 2.462GHZ"}
        dictMode = {"M":" Mixed", "B":" B-Only", "G":" G-Only", "D":" Disabled"}
        if "Disabled" == self.netMode2g :
            pass
        else:
            for key in channel.keys():
                if "2G" == key:
                    self.__setChannel(dictChannel[channel[key]])

    def setRadioOFF(self, params):
        netMode = params["netMode"]
        dictMode = {"D":" Disabled"}
        driver = self.driver
        driver.get(self.base_url + "/")
        #choose wireless setting page
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        for key in netMode.keys():
            if "2G" == key:
                Select(driver.find_element_by_name("wl_net_mode")).select_by_visible_text(dictMode[netMode["2G"]])
                driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
                driver.find_element_by_name("action").click()
                self.netMode2g = dictMode[netMode["2G"]]
    
    def __setWirelessMode(self, netMode):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        #choose Wireless Network Mode and click
        Select(driver.find_element_by_name("wl_net_mode")).select_by_visible_text(netMode)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        #click continue button
        driver.find_element_by_name("action").click()
        self.netMode2g = netMode

    def setWirelessMode(self, params):
        netMode = params["netMode"]
        dictMode = {"M":" Mixed", "B":" B-Only", "G":" G-Only"}#there is a blank befor a value
        for key in netMode.keys():
            if "2G" == key:
                self.__setWirelessMode(dictMode[netMode[key]])

    def setDns(self, params):
        ipaddr = params["DNS"]
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_name("wan_dns0_0").clear()
        #set the first num of Static DNS 1
        driver.find_element_by_name("wan_dns0_0").send_keys(self.dns.split('.')[0])
        driver.find_element_by_name("wan_dns0_1").clear()
        driver.find_element_by_name("wan_dns0_1").send_keys(self.dns.split('.')[1])
        driver.find_element_by_name("wan_dns0_2").clear()
        driver.find_element_by_name("wan_dns0_2").send_keys(self.dns.split('.')[2])
        driver.find_element_by_name("wan_dns0_3").clear()
        driver.find_element_by_name("wan_dns0_3").send_keys(self.dns.split('.')[3])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        self.dns = ipaddr['2G']

    def setDHCP(self, params):
        dhcp = params['dhcp']
        driver = self.driver
        driver.get(self.base_url + "/")
        if dhcp['2G'] == 'D':
            driver.find_element_by_xpath("(//input[@name='lan_proto'])[2]").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
            driver.find_element_by_name("action").click()
            self.dhcp = 'Disabled'
        elif dhcp['2G'] == 'E':
            driver.find_element_by_name("lan_proto").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
            driver.find_element_by_name("action").click()
            self.dhcp = 'Enabled'

    def setParkingState(self):
        ApBase.setParkingState(self)
        logger = log.Logger("CiscoWRT54GL ParkingState")

    def __setSSID(self, ssid):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_name("wl_ssid").clear()
        #set Wireless Network Name  (SSID)
        driver.find_element_by_name("wl_ssid").send_keys(ssid)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        self.ssid2g = ssid

    def setSSID(self, params):
        if self.netMode2g == 'Disabled':
            pass
        else:
            ssid = params['ssid']
            for key in ssid.keys():
                if key == '2G':
                    self.__setSSID(ssid[key])

    def __setSsidBroadcast(self, ssidBroadcast):
        if ssidBroadcast == 'Disabled':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
            #click Wireless SSID Broadcast Disabled: 
            driver.find_element_by_xpath("(//input[@name='wl_closed'])[2]").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
            driver.find_element_by_name("action").click()
            self.ssidBroadcast2g = ssidBroadcast
        elif ssidBroadcast == 'Enabled':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
            #click Wireless SSID Broadcast Enabled: 
            driver.find_element_by_name("wl_closed").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
            self.ssidBroadcast2g = ssidBroadcast

    def setSsidBroadcast(self, params):
        dictMode = {'D':'Disabled','E':'Enabled'}
        if self.netMode2g == 'Disabled':
            pass
        else:
            ssidBroadcast = params['ssidBroadcast']
            for key in ssidBroadcast.keys():
                if key == '2G':
                    self.__setSsidBroadcast(dictMode[ssidBroadcast[key]])

    def __setSecurityMode(self, securityMode):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        #choose wireless Security page
        driver.find_element_by_css_selector("td.small > a").click()
        #select Security Mode option
        Select(driver.find_element_by_name("security_mode2")).select_by_value(securityMode)
        if securityMode != 'disabled':
            driver.find_element_by_name("wl_wpa_psk").clear()
            #set WPA Shared  Key
            driver.find_element_by_name("wl_wpa_psk").send_keys(self.passphrase2g)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        self.securityMode2g = securityMode
 
    def setSecurityMode(self, params):
        securityMode = params["s_mode"]
        dictSecurityMode = {'WPA2':'wpa2_personal', 'WPA':'wpa_personal','D':'disabled'}
        for key in securityMode.keys():
            if key == '2G':
                self.__setSecurityMode(dictSecurityMode[securityMode[key]])

    def setPassphrase(self, params):
        passphrase = params["passphrase"]
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("td.small > a").click()
        for key in passphrase.keys():
            if key == '2G':
                if self.securityMode2g != "Disabled":
                    driver.find_element_by_name("wl_wpa_psk").clear()
                    driver.find_element_by_name("wl_wpa_psk").send_keys(passphrase['2G'])
                else:
                    pass
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        for key in passphrase.keys():
            if key == '2G':
                if self.securityMode2g != "Disabled":
                    self.passphrase2g = passphrase['2G']

    def setAlgorithms(self, params):
        self.securityMode2g = 'wpa2_personal'
        algorithms = params["algorithms"]
        dictAlgorithms = {'T':'TKIP','A':'AES','T/A':'TKIP+AES'}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("td.small > a").click()
        for key in algorithms.keys():
            if key == '2G':
                if (dictAlgorithms[algorithms['2G']]== 'TKIP'and self.securityMode2g !='wpa_personal')or(dictAlgorithms[algorithms['2G']] == 'TKIP+AES'and self.securityMode2g != 'wpa2_personal') or self.securityMode2g == 'disabled':
                    pass
                else:
                    #select WPA Algorithms option
                    Select(driver.find_element_by_name("wl_crypto")).select_by_visible_text(dictAlgorithms[algorithms['2G']])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        self.algorithms2g =dictAlgorithms[algorithms['2G']]

    def setKeyRenewal(self, params):
        if self.securityMode2g == 'disabled':
            pass
        else:
            keyRenewal = params['keyRenewal']
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
            driver.find_element_by_css_selector("td.small > a").click()
            driver.find_element_by_name("wl_wpa_gtk_rekey").clear()
            #set Group Key  Renewal
            driver.find_element_by_name("wl_wpa_gtk_rekey").send_keys(keyRenewal['2G'])
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
            self.keyRenewal2g = keyRenewal['2G']

