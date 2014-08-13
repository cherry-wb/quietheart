#!/usr/bin/python
import base64

#provides data  for encoding and decoding arbitrary binary strings into text strings that can be safely sent by email, used as parts of URLs, or included as part of an HTTP POST request. 

myStr = "hello world"
print "myStr:%s" % myStr

encodeStr = base64.urlsafe_b64encode(myStr)
print "encodeStr:%s" % encodeStr

decodeStr = base64.urlsafe_b64decode(str(encodeStr))
print "decodeStr:%s" % decodeStr
