#!/usr/bin/python
import json
#Function:Analyze json script
#Json is a script can descript data structure as xml, 
#for detail, please refer to "http://json.org/json-zh.html".

#Note:
#1.Also, if you write json script from python,
#you should use dump instead of load.  pleaser refer to "help(json)".

#json file:
#The file content of temp.json is:
#{
#	"name":"00_sample_case1",
#	"description":"an example."
#}
f = file("temp.json");
s = json.load(f)
print s
f.close

#json string:
s = json.loads('{"name":"test", "type":{"name":"seq", "parameter":["1", "2"]}}')
print s
print s["name"]
print s["type"]["name"]
print s["type"]["parameter"][1]

