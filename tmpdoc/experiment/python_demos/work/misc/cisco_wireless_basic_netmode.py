#!/usr/bin/python
import sys
import urllib
import urllib2
import base64

def show_help():
	print
	print "NAME"
	print "	%s - Basic wireless setup." % sys.argv[0]
	print
	print "SYNOPSIS"
	print "	%s <ip> <user>:<passwd> <5g mode> <2.4g mode>" % sys.argv[0]
	print
	print '''DESCRIPTION
	<ip>:
	means the ip address of cisco ap.
	<user>:
	means the control administrator name of cisco ap.
	<passwd>:
	means the control administrator password of cisco ap.
	<5g mode>:
	means the 5g net workmode.Values can be:
	"disabled": Disabled, also called 'radio off'.
	"mixed": Mixed.
	"a-only": Wireless-A Only
	"n-only": Wireless-N Only
	<2.4g mode>:
	means the 2.4g network mode.
	"disabled": Disabled, also called 'radio off'.
	"mixed": Mixed.
	"b-only": Wireless-B Only
	"g-only": Wireless-G Only
	"n-only": Wireless-N Only
	"bg-mixed": Wireless-B/G Only
	'''
	print
	print "EXAMPLE"
	print "	%s 172.18.2.1 admin:admin disabled disabled" % sys.argv[0]

def basic_netmode(ip, user, passwd, mode1, mode2):
	ip_addr=ip
	admin_user=user
	admin_pass=passwd
	nmode_5g=mode1
	ssid_5g="Cisco04218"
	nbw_5g="20"
	channel_5g="0"
	colsed_5g="0"

	nmode_2_4g=mode2
	ssid_2_4g="Cisco04218"
	nbw_2_4g="20"
	channel_2_4g="0"
	colsed_2_4g="0"

	authheader = "Basic %s" % base64.encodestring('%s:%s' % (admin_user, admin_pass))[:-1]
	ip_addr = 'http://' + ip_addr
	page = "/apply.cgi"
	params = {"submit_button":"Wireless_Basic",
		"action":"Apply",
		"submit_type":"",
		"change_action":"", 
		"next_page":"",
		"commit":"1",
		"wl0_nctrlsb":"none",
		"wl1_nctrlsb":"none",
		"channel_5g":"0",
		"channel_24g":"0",
		"nbw_5g":"20",
		"nbw_24g":"20",
		"wait_time":"3",
		"guest_ssid":"Cisco04218-guest",
		"wsc_security_mode":"",
		"wsc_smode":"1",
		"net_mode_5g":nmode_5g,
		"ssid_5g":ssid_5g,
		"_wl1_nbw":nbw_5g,
		"_wl1_channel":channel_5g,
		"closed_5g":colsed_5g,
		"net_mode_24g":nmode_2_4g,
		"ssid_24g":ssid_2_4g,
		"_wl0_nbw":nbw_2_4g,
		"_wl0_channel":channel_2_4g,
		"closed_24g":colsed_2_4g}
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
	if 5 == arglen:
		basic_netmode(sys.argv[1],sys.argv[2][0:sys.argv[2].find(':')],
				sys.argv[2][sys.argv[2].find(':')+1:],sys.argv[3],sys.argv[4])
	else:
		show_help()
		sys.exit(1)
