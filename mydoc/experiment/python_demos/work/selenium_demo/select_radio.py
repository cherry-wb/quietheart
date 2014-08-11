#!/usr/bin/python
from selenium import webdriver
from selenium.webdriver.support.ui import Select

url = "http://10.126.1.29/wirelesssetup_radiosetup.html"
#####select
name = "80211bg_mode"
text = "802.11g Only "
firefox = webdriver.Firefox()
firefox.get(url)
Select(firefox.find_element_by_name(name)).select_by_visible_text(text)
Select(firefox.find_element_by_name(name)).select_by_value(value)



######radio
name = "channel_width"
firefox = webdriver.Firefox()
firefox.get(url)
radio_elements = firefox.find_elements_by_name(name)
for ele in radio_elements:
    print ele.get_attribute("value")
    print ele.text
    #ele.click()
    print radio_elements.index(ele)
