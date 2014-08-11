#!/usr/bin/python
class Base:
	''' base class of access point.

		'''
	def __init__(self):
		self.m_name = "base"
		self.m_mode = ""
		self.m_ip = ""
		self.m_dns = ""
		self.m_submask = ""
	
	def turn_on(self):
		print "turn on."
		print self.turn_on.__name__
		print __name__

	def turn_off(self):
		print "turn off."

b = Base()
b.turn_on()
