#!/usr/bin/python
import sys
import urllib
import urllib2
import base64

def show_help():
	print "NAME"
	print "	%s - Set password of wireless security." % sys.argv[0]
	print
	print "SYNOPSIS"
	print "	%s <ip> <user>:<userpasswd> <password1> [<password2>]" % sys.argv[0]
	print
	print '''DESCRIPTION
	<ip>:
	means the ip address of cisco ap.
	<user>:
	means the control administrator name of cisco ap.
	<passwd>:
	means the control administrator password of cisco ap.
	<password1>: 
	5g band password if <password2> exits, or 5g and 2.4g band password.
	<password2>: 
	2.4g band password if exits.
	'''
	print
	print "EXAMPLE"
	print "	$%s 172.18.2.1 admin:admin 12345678" % sys.argv[0]

def set_passwd(ip,user,userpasswd,passwd1,passwd2):
	ip_addr=""
	admin_user=""
	admin_pass=""
	smode_5=""
	passwd_5=""
	smode_2_4=""
	passwd_2_4=""
	
	ip_addr=ip
	admin_user=user
	admin_pass=userpasswd
	passwd_5=passwd1
	passwd_2_4=passwd2

	authheader = "Basic %s" % base64.encodestring('%s:%s' % (admin_user, admin_pass))[:-1]
	ip_addr = 'http://' + ip_addr
	page = "/apply.cgi"
	params = {"submit_button":"WL_WPATable",
		"change_action":"", 
		"submit_type":"",
		"action":"Apply",
		"security_mode_last":"",
		"wl_wep_last":"",
		"wait_time":"3",
		"wsc_nwkey0":passwd_5,
		"wsc_nwkey1":passwd_2_4,
		"wl0_crypto":"tkip%2Baes",
		"wl1_crypto":"tkip%2Baes",
		"wsc_security_auto":"0",
		"wl1_security_mode":smode_5,
		"wl1_wpa_psk":passwd_5,
		"wl0_security_mode":smode_2_4,
		"wl0_wpa_psk":passwd_2_4}
	data = urllib.urlencode(params)
	req = urllib2.Request(ip_addr+page,data)
	req.add_header("Authorization", authheader)
	try:
		res = urllib2.urlopen(req)
	except IOError, e:
		print "It looks like the username or password is wrong."
		sys.exit(1)

if "__main__" == __name__:
	arglen=len(sys.argv)
	if 4 == arglen:
		set_passwd(sys.argv[1],sys.argv[2][0:sys.argv[2].find(':')],
				sys.argv[2][sys.argv[2].find(':')+1:],sys.argv[3],sys.argv[3])
	elif 5 == arglen:
		set_passwd(sys.argv[1],sys.argv[2][0:sys.argv[2].find(':')],
				sys.argv[2][sys.argv[2].find(':')+1:],sys.argv[3],sys.argv[4])
	else:
		show_help()
		sys.exit(1)
