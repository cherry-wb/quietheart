#!/usr/bin/python
import base64
import itertools
import mimetools
import mimetypes
import urllib
import urllib2
import sys

# Post file and form data to form (The key is file).
class MultiPartForm(object):
    """Accumulate the data to be used when posting a form."""

    def __init__(self):
        self.form_fields = []
        self.files = []
        self.boundary = mimetools.choose_boundary()
        return

    def get_content_type(self):
        return 'multipart/form-data; boundary=%s' % self.boundary

    def add_field(self, name, value):
        """Add a simple field to the form data."""
        self.form_fields.append((name, value))
        return

    def add_file(self, fieldname, filename, mimetype=None):
        """Add a file to be uploaded."""
        body = open(filename, "rb").read()
        if mimetype is None:
            #mimetype = (mimetypes.guess_type(filename)[0]
            #             or
            #             'application/octet-stream'
            #             )
            mimetype = ('application/octet-stream')
        self.files.append((fieldname, filename, mimetype, body))
        return

    def __str__(self):
        """Return a string representing the form data,
        including attached files.
        """
        # Build a list of lists, each containing "lines" of the
        # request.  Each part is separated by a boundary string.
        # Once the list is built, return a string where each
        # line is separated by '\r\n'. 
        parts = []
        part_boundary = '--' + self.boundary

        # Add the form fields
        parts.extend(
            [ part_boundary,
              'Content-Disposition: form-data; name="%s"' % name,
              '',
              value,
            ]
            for name, value in self.form_fields
            )

        # Add the files to upload
        parts.extend([
            part_boundary,
            #'Content-Disposition: file; name="%s"; filename="%s"' % \
            'Content-Disposition: form-data; name="%s"; filename="%s"' % \
               (field_name, filename),
            'Content-Type: %s' % content_type,
            '',
            body,
          ]
          for field_name, filename, content_type, body in self.files
          )

        # Flatten the list and add closing boundary marker, and
        # then return CR+LF separated data
        flattened = list(itertools.chain(*parts))
        flattened.append('--' + self.boundary + '--')
        flattened.append('')
        return '\r\n'.join(flattened)

def form_submitbelkin1(ipAddr):
    # Create the form with simple fields
    form = MultiPartForm()
    form.add_file('file', 'belkin_n+_router.cfg')
    body = str(form)

    request = urllib2.Request('http://'+ ipAddr +'/UploadCfgFile.cgi')
    request.add_header('Content-type', form.get_content_type())
    request.add_header('Content-length', len(body))
    request.add_data(body)

    try:
        res = urllib2.urlopen(request)
    except IOError, e:
        print "It looks like the username or password is wrong."
        print e
        sys.exit(1)

def login_belkin2(ipAddr):
    url = 'http://' + ipAddr
    request = urllib2.Request(url)
    response = urllib2.urlopen(request)
    try:
        res = urllib2.urlopen(request)
    except IOError, e:
        print e
        sys.exit(1)
    cookie = response.headers.get('Set-Cookie')

    request = urllib2.Request('http://'+ ipAddr +'/cgi-bin/login.exe')
    request.add_header('Content-type', "application/x-www-form-urlencoded")
    request.add_header('cookie', cookie)
    try:
        res = urllib2.urlopen(request)
    except IOError, e:
        print "It looks like the username or password is wrong."
        print e
        sys.exit(1)
    return cookie

def form_submitbelkin2(ipAddr):

    cookie = login_belkin2(ipAddr)

    form = MultiPartForm()
    form.add_file('webUpload', 'belkinf5d7234-4.conf')
    body = str(form)

    request = urllib2.Request('http://'+ ipAddr +'/cgi-bin/upgrade_config.exe')
    request.add_header('Content-type', form.get_content_type())
    request.add_header('Content-length', len(body))
    request.add_header('cookie', cookie)

    request.add_data(body)
    print "==="

    try:
        res = urllib2.urlopen(request)
    #except IOError, e:
    except urllib2.URLError, e:
        print "url error"
        print e
        print e.reason
        sys.exit(1)
    except urllib2.HTTPError, e:
        print "http error"
        print e
        print e.code

def form_submitbelkin3(ipAddr):


    form = MultiPartForm()
    form.add_file('file', 'nvrambak.bin')
    body = str(form)

    request = urllib2.Request('http://'+ ipAddr +'/nvram.cgi')
    authheader = "Basic %s" % base64.encodestring('%s:%s' % ("admin", "admin"))[:-1]
    request.add_header("Authorization", authheader)
    request.add_header('Content-type', form.get_content_type())
    request.add_header('Content-length', len(body))

    request.add_data(body)

    try:
        res = urllib2.urlopen(request)
    except IOError, e:
        print "It looks like the username or password is wrong."
        print e
        sys.exit(1)

def form_submitmf300n(ipAddr):
    form = MultiPartForm()
    form.add_field('submit-url', '/saveconf.asp')
    form.add_file('binary', 'dci_mzk_mf300N_config.dat')
    form.add_field('load', 'Upload')
    body = str(form)

    request = urllib2.Request('http://'+ ipAddr +'/goform/formSaveConfig')
    authheader = "Basic %s" % base64.encodestring('%s:%s' % ("admin", "password"))[:-1]
    request.add_header("Authorization", authheader)
    request.add_header('Content-type', form.get_content_type())
    request.add_header('Content-length', len(body))

    request.add_header('Connection', "keep-alive")
    request.add_header('User-Agent', 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/535.2 (KHTML, like Gecko) Ubuntu/11.10 Chromium/15.0.874.106 Chrome/15.0.874.106 Safari/535.2')
    request.add_header('Accept-Language', 'en-US,en;q=0.8')
    request.add_header('Accept-Encoding', 'gzip,deflate,sdch')
    request.add_header('Accept-Charset', 'ISO-8859-1,utf-8;q=0.7,*;q=0.3')
    request.add_header('Referer','http://10.126.1.34/saveconf.asp')
    request.add_header('Origin','http://10.126.1.34')
    request.add_header('Cookie','language=en')

    request.add_data(body)

    try:
        res = urllib2.urlopen(request)
    except IOError, e:
        print "It looks like the username or password is wrong."
        print e
        sys.exit(1)

def form_submitmf300n2(ipAddr):
    boundary = mimetools.choose_boundary()
    parts = []
    part_boundary = '--' + boundary
    field_name = "binary"
    file_name = "dci_mzk_mf300N_config.dat"
    file_content = open(file_name, "rb").read()
    content_type = 'application/octet-stream'

    parts.extend([
        part_boundary,
        'Content-Disposition: form-data; name="%s"; filename="%s\r\n"' % (field_name, file_name),
        'Content-Type: %s\r\n\r\n' %content_type,
        '',
        file_content,
      ]
      )
    flattened = list(itertools.chain(*parts))
    flattened.append('--' + boundary + '--')
    flattened.append('')
    body = '\r\n'.join(flattened)

    request = urllib2.Request('http://'+ ipAddr +'/goform/formSaveConfig')

    authheader = "Basic %s" % base64.encodestring('%s:%s' % ("admin", "password"))[:-1]
    request.add_header("Authorization", authheader)
    header_type = 'multipart/form-data; boundary=%s' % boundary
    request.add_header('Content-type', header_type)
    request.add_header('Content-length', len(body))

    request.add_data(body)

    try:
        res = urllib2.urlopen(request)
    except IOError, e:
        print "It looks like the username or password is wrong."
        print e
        sys.exit(1)

def form_submite1000(ipAddr):
    boundary = mimetools.choose_boundary()
    parts = []
    part_boundary = '--' + boundary

    #form_fields = []
    #form_fields.append(("submit_button","Restore"))
    #form_fields.append(("small_screen",""))
    #form_fields.append(("wait_time","25"))
    #parts.extend(
    #    [ part_boundary,
    #      'Content-Disposition: form-data; name="%s"' % name,
    #      '',
    #      value,
    #    ]
    #    for name, value in form_fields
    #    )

    files = []
    field_name = "restore"
    file_name = "E1000_v2.1.00.cfg"
    content_type = 'application/octet-stream'
    file_content = open(file_name, "rb").read()

    files.append((field_name,file_name,content_type,file_content))
    parts.extend([
        part_boundary,
        'Content-Disposition: form-data; name="%s"; filename="%s"' % (name, fname),
        'Content-Type: %s' %ctype,
        '',
        fbody,
      ]
      for name,fname,ctype,fbody in files
      )

    flattened = list(itertools.chain(*parts))
    flattened.append('--' + boundary + '--')
    flattened.append('')
    body = '\r\n'.join(flattened)

    request = urllib2.Request('http://'+ ipAddr +'/restore.cgi')

    authheader = "Basic %s" % base64.encodestring('%s:%s' % ("admin", "admin"))[:-1]
    request.add_header("Authorization", authheader)
    header_type = 'multipart/form-data; boundary=%s' % boundary
    request.add_header('Content-type', header_type)
    request.add_header('Content-length', len(body))

    request.add_data(body)

    try:
        res = urllib2.urlopen(request)
    except IOError, e:
        print "It looks like the username or password is wrong."
        print e
        sys.exit(1)
if __name__ == '__main__':
    #form_submitbelkin('10.126.1.35/tools_backup.stm')
    #form_submitbelkin1('10.126.1.22')
    #form_submitbelkin2('10.126.1.35')
    #form_submitbelkin3('10.126.1.38')
    #form_submitmf300n('10.126.1.34')
    #form_submitmf300n2('10.126.1.34')
    #form_submitmf300n1('10.126.1.34')
    form_submite1000('10.126.1.51')
