""" 
Cisco E3000 Access point .
"""

from base import ApBase

from selenium import webdriver
from selenium.webdriver.support.ui import Select

class CiscoE3000(ApBase):
    def setParameters(self, params):
        self.model = params['name']
        self.ip = params['ip']
        self.submask = params['submask']
        self.dns = params['dns']
        self.admin = params['admin']
        self.password = params['password']

    def turnOn(self):
        ApBase.turnOn(self)
        print 'CiscoE3000 turnOn'

    def turnOff(self):
        ApBase.turnOff(self)
        print 'CiscoE3000 turnOff'

    def openWebDriver(self):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(20)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip

    def closeWebDriver(self):
        self.driver.quit()

    def reboot(self):
        ApBase.reboot(self)
        print 'CiscoE3000 reboot'

    def setChannelWidth_24G(self,ChannelWidth):
        dict_ChannelWidth={"Auto":"Auto(20MHz or 40MHz)","20":"20MHz only"}
        self.ChannelWidth24g=dict_ChannelWidth[ChannelWidth]
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        Select(driver.find_element_by_name("_wl0_nbw")).select_by_visible_text(self.ChannelWidth24g)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def setChannelWidth_5G(self,ChannelWidth):
        dict_ChannelWidth={"Auto":"Auto(20MHz or 40MHz)","20":"20MHz only","40":"40MHz only"}
        self.ChannelWidth5g=dict_ChannelWidth[ChannelWidth]
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        Select(driver.find_element_by_name("_wl1_nbw")).select_by_visible_text(self.ChannelWidth5g)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()

    def setSSIDEn_24G(self, mode):
        self.enable_24g = mode
        if self.enable_24g == 'enable':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
            driver.find_element_by_name("wl0_closed").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        elif self.enable_24g == 'disable':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
            driver.find_element_by_xpath("(//input[@name='wl0_closed'])[2]").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def setSSIDEn_5G(self, mode):
        self.enable_5g = mode
        if self.enable_5g == 'enable':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
            driver.find_element_by_name("wl1_closed").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        elif self.enable_5g == 'disable':
            driver = self.driver
            driver.get(self.base_url + "/")
            driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
            driver.find_element_by_xpath("(//input[@name='wl1_closed'])[2]").click()
            driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def setWirelessMode_24G(self, wmode):
        dict_wmode = {'B/G':'Wireless-B/G Only', 'B':'Wireless-B Only', 'G':'Wireless-G Only', 'M':'Mixed', 'N':'Wireless-N Only'}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(dict_wmode[wmode])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def setRadioOFF_24G(self, wmode):
        dict_wmode = {'D':'Disabled'}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(dict_wmode[wmode])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def setDns(self,ipaddr):
        self.dns=ipaddr
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("a").click()
        driver.find_element_by_id("dns00").clear()
        driver.find_element_by_id("dns00").send_keys(self.dns.split('.')[0])
        driver.find_element_by_id("dns01").clear()
        driver.find_element_by_id("dns01").send_keys(self.dns.split('.')[1])
        driver.find_element_by_id("dns02").clear()
        driver.find_element_by_id("dns02").send_keys(self.dns.split('.')[2])
        driver.find_element_by_id("dns03").clear()
        driver.find_element_by_id("dns03").send_keys(self.dns.split('.')[3])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def setWirelessMode_5G(self, wmode):
        dict_wmode = {'A':'Wireless-A Only', 'N':'Wireless-N Only', 'M':'Mixed'}

        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        # ERROR: Caught exception [ERROR: Unsupported command [getConfirmation]]
        Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(dict_wmode[wmode])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def setParkingState(self):
        ApBase.setParkingState(self)
        print 'CiscoE3000 setParkingState'

    def dump(self):
        ApBase.dump(self)

    def setChannel_5G(self,channel):
        dict_channel = {'36':'36 - 5.180GHz', '40':'40 - 5.200GHz', '44':'44 - 5.220GHz', '48':'48 - 5.240GHz', '149':'149 - 5.745GHz', '153':'153 - 5.765GHz', '157':'157 - 5.785GHz', '161':'161 - 5.805GHz',"A":"Auto (DFS)"}
        self.channel_5g = dict_channel[channel]
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        Select(driver.find_element_by_name("_wl1_channel")).select_by_visible_text(self.channel_5g)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
    def setChannel_24G(self,channel):
        dict_channel = {'1':'1 - 2.412GHZ', '2':'2 - 2.417GHZ', '3':'3 - 2.422GHZ', '4':'4 - 2.427GHZ', '5':'5 - 2.432GHZ', '6':'6 - 2.437GHZ', '7':'7 - 2.442GHZ', '8':'8 - 2.447GHZ','9':'9 - 2.452GHZ', '10':'10 - 2.457GHZ', '11':'11 - 2.462GHZ',"A":"Auto"}
        self.channel_24g = dict_channel[channel]
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        Select(driver.find_element_by_name("_wl0_channel")).select_by_visible_text(self.channel_24g)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
    def setSSID_5G(self,ssid):
        self.ssid=ssid
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_name("wl1_ssid").clear()
        driver.find_element_by_name("wl1_ssid").send_keys(self.ssid)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
    def setSSID_24G(self,ssid):
        self.ssid24=ssid
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_name("wl0_ssid").clear()
        driver.find_element_by_name("wl0_ssid").send_keys(self.ssid24)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
    def set_radio_off_5G(self, wmode):
        dict_wmode = {'D':'Disabled'}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        # ERROR: Caught exception [ERROR: Unsupported command [getConfirmation]]
        Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(dict_wmode[wmode])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()

    def restore_factory_default(self):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[7]/p/font/a").click()
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[3]/td/table/tbody/tr/td[11]/a").click()
        driver.find_element_by_name("restore_b").click()
        # ERROR: Caught exception [ERROR: Unsupported command [getConfirmation]]

if __name__ == '__main__':
    e3000 = CiscoE3000()
    e3000.setParameters({'name':'E3000', 'ip':'10.1.10.32:8080', 'submask':'255.255.255.0', 'dns':'10.1.10.254', 'admin':'admin', 'password':'myadmin'})
    e3000.openWebDriver()
    e3000.setWirelessMode_5G('N')
    e3000.setChannel_5G('36')
    e3000.setChannel_24G('A')
    e3000.setSSID_5G('Cisco6300')
    e3000.closeWebDriver()
    e3000.setSSIDEn_24G('enable')
    e3000.setSSIDEn_5G('enable')
    e3000.setWirelessMode_24G('B/G')
