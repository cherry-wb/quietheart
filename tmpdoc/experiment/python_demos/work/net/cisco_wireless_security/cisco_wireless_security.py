#!/usr/bin/python
import sys
import urllib
import urllib2
import base64

def show_help():
	print
	print "NAME"
	print "	%s - Set wireless security mode, and corresponding password." % sys.argv[0]
	print
	print "SYNOPSIS"
	print "	%s <ip> <user>:<passwd> <5G mode> <5G passwd> <2.4G mode> <2.4G passwd>" % sys.argv[0]
	print
	print '''DESCRIPTION
	<ip>:
	means the ip address of cisco ap.
	<user>:
	means the control administrator name of cisco ap.
	<passwd>:
	means the control administrator password of cisco ap.
	<5G mode>:
	value can now be as following:
		"wpa_personal":set mode to "WPA Personal".
		"wpa2_personal":set mode to "WPA2/WPA Mixed Mode".???
		"wpa2_enterprise":set mode to "WPA2/WPA Enterprise Mixed Mode".???
		"disabled":disabled security mode.
	<5G passwd>:
	means the password of 5G mode.
	<2.4G mode>:
	value can now be as following:
		"wpa_personal"
		"wpa2_personal":set mode to "WPA2/WPA Mixed Mode".???
		"wpa2_enterprise":set mode to "WPA2/WPA Enterprise Mixed Mode".???
		"disabled":disabled security mode.
	<2.4G passwd>:
	means the password of 2.4G mode.
	'''
	print
	print "EXAMPLE"
	print "	%s 172.18.2.1 admin:admin wpa_personal abcdefgh wpa_personal 12345678" % sys.argv[0]

def set_security(ip, user, passwd, mode1, passwd1, mode2, passwd2):
	ip_addr=ip
	admin_user=user
	admin_pass=passwd
	smode_5=mode1
	passwd_5=passwd1
	smode_2_4=mode2
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
	if 7 == arglen:
		set_security(sys.argv[1],sys.argv[2][0:sys.argv[2].find(':')],
				sys.argv[2][sys.argv[2].find(':')+1:],sys.argv[3],
				sys.argv[4],sys.argv[5],sys.argv[6])
	else:
		show_help()
		sys.exit(1)
