#!/usr/bin/python
from selenium import webdriver
from selenium.webdriver.support.ui import Select

#url = "http://10.126.1.29/wirelesssetup_radiosetup.html"
#url = "http://10.126.1.29/advancedsetup_lanipdhcpsettings.html"
#url = "http://10.126.1.29/wirelesssetup_basicsettings.html"
#url = "http://10.126.1.29/wirelesssetup_radiosetup.html"
#url = "http://10.126.1.29/wirelesssetup_multiplessid.html"
#url = "http://admin:admin@10.126.1.13/Wireless_Basic.asp"
url = "http://admin:admin@10.126.1.13/WL_WPATable.asp"
elementName = 'wl_crypto'
firefoxDriver = webdriver.Firefox()

firefoxDriver.get(url)
element = firefoxDriver.find_element_by_name(elementName)
print element
#value = Select(selectElement).first_selected_option.get_attribute("value")
value = element.get_attribute("value")
print value

#We only get the value of first element with the same.(the latter version can do this.)
elements = firefoxDriver.find_elements_by_name(elementName)
print elements
value = elements[0].get_attribute("value")
print value
value = elements[1].get_attribute("value")
print value


#use javascript we can get the value of the elements with the same name.
jsValue = firefoxDriver.execute_script("return document.forms[0].wl_crypto.value")
print "jsValue of wl_crypto:'%s'" %jsValue

jsElementLen = firefoxDriver.execute_script("return document.getElementsByName('wl_crypto').length")
print "jselement length with same name of wl_crypto:'%s'" %jsElementLen
jsValue0 = firefoxDriver.execute_script("return document.getElementsByName('wl_crypto')[0].value")
print "jsValue of wl_crypto[0]:'%s'" %jsValue0
jsValue1 = firefoxDriver.execute_script("return document.getElementsByName('wl_crypto')[1].value")
print "jsValue of wl_crypto[1]:'%s'" %jsValue1

firefoxDriver.quit()

