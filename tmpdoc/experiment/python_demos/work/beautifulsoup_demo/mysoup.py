#!/usr/bin/python
import sys
import base64
import urllib
import urllib2
import re

from BeautifulSoup import BeautifulSoup
#from BeautifulSoup import BeautifulStoneSoup
#import BeautifulSoup

class MySoup(object):
    def __init__(self):
        self.soup = None

    def openURL(self,url):
        regexp = r'(?P<prefix>http://)(?P<user>\w+):(?P<password>\w+)@(?P<address>.*)'
        pattern = re.compile(regexp,re.S)
        match = pattern.match(url)

        username = match.group("user")
        password = match.group("password")
        url = match.group("prefix") + match.group("address")

        base64string = base64.encodestring('%s:%s' % (username, password))[:-1]
        authheader =  "Basic %s" % base64string

        request = urllib2.Request(url)
        request.add_header("Authorization", authheader)
        try:
            res = urllib2.urlopen(request)
            page_src = res.read()
            self.soup = BeautifulSoup(page_src)
        except IOError, e:
            print "It looks like the username or password is wrong."
            print e
            sys.exit(1)
        return self.soup
    
    
    def selectElementByNameValue(self, name, value):
        #Select(driver.find_element_by_name(name)).select_by_value(value)
        soup = self.soup
        form_tags = soup.findAll("form")
        for form_tag in form_tags:
            form_name = form_tag["name"] if form_tag.has_key("name") else "noname"
            form_action = form_tag["action"] if form_tag.has_key("action") else "action"
            print "form name:", form_tag["name"]
            print "form action:", form_tag["action"]
            print "-" * 50

            input_tags = form_tag.findAll("input")
            for input_tag in input_tags:
                tag_name = input_tag["name"] if input_tag.has_key("name") else "noname"
                tag_value = input_tag["value"] if input_tag.has_key("value") else ''
                tag_text = input_tag["text"] if input_tag.has_key("text") else ''
                print "input name:" , tag_name
                print "input value:" , tag_value
                print "input text:" , tag_text

            select_tags = form_tag.findAll("select")
            for select_tag in select_tags:
                select_name = select_tag["name"] if select_tag.has_key("name") else "noname"
                select_value = select_tag["value"] if select_tag.has_key("value") else "novalue"
                select_text = select_tag["text"] if select_tag.has_key("text") else "notext"
                print "select name:",select_name
                print "select value:",select_value
                print "select text:",select_text
                print "select:",select_tag
                option_tags = select_tag.findAll("option")
                print len(option_tags)
                for option_tag in option_tags:
                    option_value = option_tag["value"] if option_value.has_key("value") else "novalue"
                    option_text = option_tag["text"] if option_value.has_key("text") else "novalue"
                    option_selected = True if option_value.has_key("selected") else False
                    print "option value:",option_value
                    print "option text:",option_text
                    print "option selected:",option_selected,
            print "-" * 50
        #time.sleep(1)
    
    
def openURL(url):
    mysoup = MySoup()
    mysoup.openURL(url)
    return mysoup

def setWirelessMode(mode):
    ip_addr = "http://admin:admin@10.126.1.14"
    url_page = "Wireless_Basic.asp"
    full_url = ip_addr + '/' + url_page
    
    modeElement = "net_mode_5g"
    modeValue = "a-only"
    
    mysoup = openURL(full_url)
    mysoup.selectElementByNameValue(modeElement,modeValue)


#wirelessMode2gMap = {
#    WifiTerms.WIRELESS_MODE_D:'0',
#    WifiTerms.WIRELESS_MODE_B:'1',
#    WifiTerms.WIRELESS_MODE_G:'2',
#    WifiTerms.WIRELESS_MODE_BG:'3',
#    WifiTerms.WIRELESS_MODE_N:'4',
#    WifiTerms.WIRELESS_MODE_MIXED:'7',
#}

setWirelessMode(2)
