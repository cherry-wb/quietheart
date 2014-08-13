#!/usr/bin/python
from selenium import webdriver

#url = "http://10.126.1.29/wirelesssetup_radiosetup.html"
#url = "http://10.126.1.29/advancedsetup_lanipdhcpsettings.html"
#url = "http://10.126.1.29/wirelesssetup_basicsettings.html"
#url = "http://10.126.1.29/wirelesssetup_radiosetup.html"
#url = "http://10.126.1.29/wirelesssetup_multiplessid.html"
url = "http://admin:admin@10.126.1.15/Wireless_Basic.asp"
formName = 'wireless'
firefoxDriver = webdriver.Firefox()

firefoxDriver.get(url)
#content = firefoxDriver.execute_script("return document.forms['%s'].outerHTML;" % (formName))
#content = firefoxDriver.execute_script("return document.forms['%s'].outerHTML" %(formName))
content = firefoxDriver.execute_script("return document.forms[0].outerHTML")
print content
firefoxDriver.quit()
