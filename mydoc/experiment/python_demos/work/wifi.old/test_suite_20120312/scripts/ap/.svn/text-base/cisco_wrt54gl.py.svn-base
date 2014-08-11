""" 
Cisco WRT54GL Access point .
"""

from base import ApBase

from selenium import webdriver
from selenium.webdriver.support.ui import Select

class CiscoWRT54GL(ApBase):
    def setParameters(self, params):
        self.model = params['name']
        self.ip = params['ip']
        self.submask = params['submask']
        self.dns = params['dns']
        self.admin = params['admin']
        self.password = params['password']

    def turnOn(self):
        ApBase.turnOn(self)
        print 'CiscoWRT54GL turnOn'

    def turnOff(self):
        ApBase.turnOff(self)
        print 'CiscoWRT54GL turnOff'

    def openWebDriver(self):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(20)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip

    def closeWebDriver(self):
        self.driver.quit()

    def reboot(self):
        ApBase.reboot(self)
        print 'CiscoWRT54GL reboot'

    def setChannel(self,channel):
        pass

    def setRadioOFF(self,wmode):
        pass

    def setWirelessMode(self,wmode):
        pass

    def setDns(self,ipaddr):
        pass

    def setParkingState(self):
        ApBase.setParkingState(self)
        print 'CiscoWRT54GL setParkingState'

    def dump(self):
        ApBase.dump(self)
   
    def setSSID(self,ssid):
        self.ssid=ssid
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_name("wl_ssid").clear()
        driver.find_element_by_name("wl_ssid").send_keys(self.ssid)
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()

    def setSsidBroadcast(self):
        pass

    def setSecurityModeAndKey(self):
        pass

    def setSharedKey(self):
        pass

    def setAlgorithms(self):
        pass

    def setKeyRenewal(self):
        pass

if __name__ == '__main__':
    wrt54gl = CiscoWRT54GL()
if __name__ == '__main__':
    wrt54gl = CiscoWRT54GL()
if __name__ == '__main__':
    wrt54gl = CiscoWRT54GL()
    wrt54gl.setParameters({'name':'WRT54GL', 'ip':'10.1.10.92:8080', 'submask':'255.255.255.0', 'dns':'10.1.10.254', 'admin':'admin', 'password':'myadmin'})
    wrt54gl.openWebDriver()
    wrt54gl.setSSID()
    wrt54gl.closeWebDriver()
