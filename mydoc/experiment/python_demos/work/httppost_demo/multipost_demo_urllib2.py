#!/usr/bin/python

import base64
import urllib2
import itertools
import mimetools
import mimetypes
import time

class MultiForm(object):
    """Class used for http multi post."""
    def __init__(self, user, password, ip, formAction):
        self.user = user
        self.password = password
        self.ip = ip
        self.url = str('http://'+ self.ip +'/' + formAction)
        self.boundary = mimetools.choose_boundary()
        self.partBoundary = '--' + self.boundary
        self.parts = []
        #single file for 'form-data' and multi file for 'file'
        #self.contentDisposition = 'form-data'
        self.contentDisposition = 'file'

    def addField(self, fieldName, fieldValue):
        fieldInfo = [(fieldName, fieldValue)]
        self.parts.extend(
            [ self.partBoundary,
              'Content-Disposition: form-data; name="%s"' % name,
              '',
              value,
            ]
            for name, value in fieldInfo
            )

    def addFile(self, fieldName, fileName):
        contentType = (mimetypes.guess_type(fileName)[0] or 'application/octet-stream')
        fileContent = open(fileName, "rb").read()
        fileInfo = [(fieldName, fileName, contentType, fileContent)]
        self.parts.extend([
            self.partBoundary,
            'Content-Disposition: %s; name="%s"; filename="%s"' % (self.contentDisposition, name, fname),
            'Content-Type: %s' %ctype,
            '',
            fbody,
            ]
            for name,fname,ctype,fbody in fileInfo
            )

    def submit(self):
        print "Begin to upload."
        request = urllib2.Request(self.url)

        #Body content.
        flattened = list(itertools.chain(*self.parts))
        flattened.append('--' + self.boundary + '--')
        flattened.append('')
        body = str('\r\n'.join(flattened))
        request.add_data(body)

        #Header content.
        authheader = "Basic %s" % base64.encodestring('%s:%s' % (self.user, self.password))[:-1]
        headerType = 'multipart/form-data; boundary=%s' % self.boundary
        request.add_header('Authorization', authheader)
        request.add_header('Content-type', headerType)
        request.add_header('Content-length', len(body))

        #Post body and header.
        try:
            urllib2.urlopen(request)
        except IOError, e:
            errMsg = str(e)
            print(errMsg)
        finally:
            print "Upload Ok."


def upload():
#for ddwrt and ciscoe3000's ap restore.
    user = "admin"
    password = "admin"
    ip = "10.126.1.81"
    multiForm = MultiForm(user, password, ip, "nvram.cgi")
    #multiForm = MultiForm(user, password, ip, "restore.cgi")

    #The html element name for file to be uploaded.
    fieldName = "file"
    #fieldName = "restore"
    #The file to be uploaded.
    fileName = "ddwrtv24single.bin"
    #fileName = "Linksys_E3000V1_v1.0.01.cfg"
    multiForm.addFile(fieldName, fileName)

    multiForm.submit()

    time.sleep(10)

if __name__ == '__main__':
    upload()
