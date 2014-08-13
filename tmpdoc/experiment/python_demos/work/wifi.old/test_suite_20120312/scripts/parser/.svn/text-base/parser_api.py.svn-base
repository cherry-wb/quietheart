#!/usr/bin/python
import os
import time
import json
######Internal function.######
def __list_type(list_args,dirname,fname):
	for i in fname:
		if os.path.isfile(dirname+os.sep+i) and (os.path.splitext(dirname+os.sep+i)[1] 
				in list_args["types"]):
			list_args["scripts"].append(dirname+os.sep+i)

######Public function.######
def list_type(topdir,types):
	''' list all the files recursively in 'topdir' whose extension name is list in 'types'.
	
		return the the file list match 'types'.
		'''
	scripts=[]
	args={"types":types,"scripts":scripts}
	os.path.walk(topdir,__list_type,args)
	return scripts

def report_result(fname, msg):
	''' report result message to fname.

		'''
	msg = "<<<<<<<<<%s<<<<<<<<<<<\n"%(time.strftime('%Y-%m-%d-%H:%M:%S')) + msg + "\n"
	msg += ">>>>>>>>>%s>>>>>>>>>>>\n"%(time.strftime('%Y-%m-%d-%H:%M:%S'))
	f=file(fname,'a')
	f.write(msg)
	f.close()


######Public class.######
class Parser:
	def __init__(self):
		self.m_name = ''
		self.m_type = {}
		self.m_description = ''
		self.m_scenarios = []

	def __str__(self):
		ret = "m_name:" + self.m_name +'\n'
		ret += "m_type:" + str(self.m_type) + '\n'
		ret += "m_description:" + str(self.m_description) + '\n'
		ret += "m_scenarios:" + str(self.m_scenarios) + '\n'
		return ret

	def parse_json(self,fname):
		''' parse a json file into this object.

	'''
		f = file(fname)
		s = json.load(f)
		f.close()
		self.parse_jsons(s)

	def parse_jsons(self,jstr):
		''' parse a json string into this object.

			'''
		for key in jstr.keys():
			if "name" == key:
				self.m_name=jstr["name"]
			elif "type" == key:
				self.m_type=jstr["type"]
			elif "description" == key:
				self.m_description=jstr["description"]
			elif "scenarios" == key:
				for scenario in jstr[key]:
					self.m_scenarios.append(scenario)
