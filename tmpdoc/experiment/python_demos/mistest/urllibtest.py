#!/usr/bin/python
import re
import urllib
import urllib2
import sys
import base64

def fix_html(content):
    content = content.replace("\r", "")
    content = content.replace("\n", "")

    commentPat = re.compile(r"<!--.*?-->")
    content = commentPat.sub("", content)
    return content

def get_form(htmlText, name = None, index = None):
    formPat = re.compile(r"<form.*?</form>")
    formList = formPat.findall(htmlText)
    if name == None and index == None:
        index = 0
    elif name != None:
        for form in formList:
            formTextMatch = re.search(r'<form.*?>', form)
            formNameMatch = re.search(r'.*?name\s*=\s*(.*?)\s.*', formTextMatch.group(0))
            if formNameMatch != None and formNameMatch.group(1) == name:
                index = formList.index(form)
    if index != None:
        formText = formList[index]
    else:
        formText = None
    return formText

def get_inputs(formText):
    pass
#replace <input .../input> <INPUT .../INPUT> to <input...>
#replace <script language=JavaScript .../script> to <input> (search document.write...)

username = 'admin'
password = 'admin'
base64string = base64.encodestring('%s:%s' % (username, password))[:-1]
authheader =  "Basic %s" % base64string
theurl = 'http://10.126.1.53'
thepage = "/index.stm?title=Wireless-Basic Wireless Settings"
#params = {
#	}
#data = urllib.urlencode(params)
#req = urllib2.Request(theurl+thepage,data)
req = urllib2.Request(theurl+thepage)
req.add_header("Authorization", authheader)
try:
	handle = urllib2.urlopen(req)
    #print req.get_selector()
    #print req.header_items()
    #print req.get_full_url()
except IOError, e:
	print "It looks like the username or password is wrong."
	sys.exit(1)
#print handle.geturl()
#print handle.info()
thepage = handle.read() 

thepage = fix_html(thepage)

formText = get_form(thepage, 'theForm')

inputs = get_inputs(formText)
