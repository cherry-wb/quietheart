#!/usr/bin/python
import sys,urllib,urllib2,base64
import getopt,time,random,re

def show_help():
    print "NAME"
    print "    %s - Clock in/out for kq.neusoft.com." % sys.argv[0]
    print
    print "SYNOPSIS"
    print "    %s [-i <ip>] [-u <user> -p <userpasswd>]" % sys.argv[0]
    print
    print '''DESCRIPTION
    Options:
    -i <ip>,--ip=<ip>
          Specify the ip address of card system.
          Default address is:
          kq.neusoft.com

    -u <username>,--user=<username>
          Specify the username.

    -p <password>,--password=<password>
          Specify the password.

    -h,--help
          Print this help.
    '''
    print
    print "EXAMPLE"
    print "    *Clock in/out with command line by specify user and password:"
    print "    $%s -i kq.neusoft.com -u lv-k -p 12345678" % sys.argv[0]
    print "    *Clock in/out with interaction mode:"
    print "    $%s " % sys.argv[0]
    print
    print "COPYRIGHT"
    print "    There's no copyright unless you can pay for me if they know who am I."


def get_inputs(whole_page, user=None, passwd=None):
    #Extract Form source.
    formReg = r"<form.*?</form>"
    formMatch = re.search(formReg, whole_page, re.S)
    formContent = formMatch.group(0)

    inputReg = r"\s*?<input .*? name.*?>"
    inputMatch = re.findall(inputReg, formContent, re.S)

    #Collect all input fields.
    inputs = {}
    for inputItem in inputMatch:
        nameMatch = re.search(r".*?name\s*?=\s*?\"(\S*?)\"",inputItem, re.S)
        if nameMatch:
            itemName = nameMatch.group(1)
        else:
            continue
        valueMatch = re.search(r".*?value\s*?=\s*?\"(\S*?)\"",inputItem, re.S)
        if valueMatch:
            itemValue = valueMatch.group(1)
        inputs[itemName] = itemValue

        #Process userName and password specially.
        if re.search(r".*?type\s*?=\s*?\"password\"",inputItem, re.S):
            inputs[itemName] = passwd
        elif re.search(r".*?class\s*?=\s*?\"textfield\"",inputItem, re.S):
            inputs[itemName] = user
        else:
            pass

    return inputs

def login(ip, user, passwd):
    url = 'http://' + ip
    request = urllib2.Request(url)
    response = urllib2.urlopen(request)
    whole_page = response.read()
    inputs = get_inputs(whole_page, user, passwd)
    cookie = response.headers.get('Set-Cookie')

    action = "/login_wkq1103_3023.jsp"
    url += action

    data = urllib.urlencode(inputs)
    request = urllib2.Request(url,data)
    request.add_header('cookie', cookie)
    response = urllib2.urlopen(request)

    return cookie


def logout(ip,cookie):
    url = 'http://' + ip
    request = urllib2.Request(url+"/attendance.jsp")
    request.add_header('cookie', cookie)
    response = urllib2.urlopen(request)
    whole_page = response.read()
    inputs = get_inputs(whole_page)

    action = "/close.jsp"
    url += action
    data = urllib.urlencode(inputs)
    request = urllib2.Request(url,data)
    request.add_header('cookie', cookie)
    response = urllib2.urlopen(request)

def action(ip,cookie):
    url = 'http://' + ip
    request = urllib2.Request(url+"/attendance.jsp")
    request.add_header('cookie', cookie)
    response = urllib2.urlopen(request)
    whole_page = response.read()
    inputs = get_inputs(whole_page)

    page = "/record.jsp"
    url += page
    data = urllib.urlencode(inputs)
    request = urllib2.Request(url,data)
    request.add_header('cookie', cookie)
    response = urllib2.urlopen(request)

    return cookie

def pit_card(ip_addr,user,passwd):
    try:
        cookie = login(ip_addr,user,passwd)
        cookie = action(ip_addr,cookie)
        logout(ip_addr,cookie)
    except Exception,e:
        print repr(e)

def interact(ip):
    print
    print
    print "Welcome come here for %s." % ip
    user = str(raw_input("User:"))
    password = str(raw_input("Password:"))
    clockin = str(raw_input("Clockin Time (HH:MM, for example,09:00):"))
    if "" == clockin:
        clockin = "09:00"
    clockout = str(raw_input("Clockout Time (HH:MM, for example,18:00):"))
    if "" == clockout:
        clockout = "18:00"
    return (user,password,clockin,clockout)

def running(user,passwd,inTime,outTime):
    print "orig clockin:",inTime
    print "orig clockout:",outTime
    formatStr = "%H:%M"
    diffRange = 300
    equalDiff = 10
    dayHour = 24
    hourSecond = 3600
    while True:
        randomNum = random.randint(0,diffRange)

        curTime = time.localtime()
        curTime = time.strftime(formatStr,curTime)
        curTime = time.strptime(curTime,formatStr)
        rawCurTime = time.mktime(curTime)
        curTime = time.strftime(formatStr,time.localtime(rawCurTime))

        clockin=inTime
        clockin = time.strptime(clockin,formatStr)
        rawClockin = time.mktime(clockin)
        rawClockin -= randomNum #in case be late
        clockin = time.strftime(formatStr,time.localtime(rawClockin))

        clockout=outTime
        clockout = time.strptime(clockout,formatStr)
        rawClockout = time.mktime(clockout)
        rawClockout += randomNum #in case leave early
        clockout = time.strftime(formatStr,time.localtime(rawClockout))

        sleepTime = 0
        if max(rawCurTime,max(rawClockout,rawClockin)) == rawCurTime:
            rawClockin = rawClockin + (dayHour * hourSecond)
            sleepTime = rawClockin - rawCurTime
        else:
            if rawCurTime == min(rawCurTime,rawClockin):
                sleepTime = rawClockin - rawCurTime
            else:
                sleepTime = rawClockout - rawCurTime

        randomSecond = randomNum%60
        print "-" * 20
        print "current time:",curTime
        print "modified clockin:",clockin
        print "modified clockout:",clockout
        print "sleepTime:",sleepTime+randomSecond

        if sleepTime > equalDiff:
            time.sleep(sleepTime)
        time.sleep(randomSecond)

        #if 0 == cmp(curTime,clockin) or 0 == cmp(curTime,clockout):
        if True:
            print "begin to pit, ip:%s,User:%s, Pass:%s" %(ip_addr,user,passwd)
            pit_card(ip_addr,user,passwd)
            print "pittime:", time.strftime("%H:%M:%S",time.localtime())
            time.sleep(diffRange+equalDiff+1) #in case pit many times in a short time.
    

if "__main__" == __name__:
    ip_addr="kq.neusoft.com"
    user=""
    passwd=""

    if 1 == len(sys.argv):
        show_help()
        user,passwd,clockin,clockout=interact(ip_addr)
        running(user,passwd,clockin,clockout)
    else:
        try:
            opts, args = getopt.getopt(sys.argv[1:], 'hi:u:p:', ['help','ip=','user=','password='])
        except getopt.GetoptError:
            show_help()
            sys.exit(1)
    
        for o,v in opts:
            if o in ('-h', '--help'):
                show_help()
                sys.exit(1)
            elif o in ('-i', '--ip'):
                ip_addr=v
            elif o in ('-u', '--user'):
                user=v
            elif o in ('-p', '--password'):
                passwd=v
        pit_card(ip_addr,user,passwd)
