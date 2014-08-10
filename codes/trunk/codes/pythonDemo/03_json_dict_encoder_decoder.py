#!/usr/bin/python
import json

class MyServer(object):
#encode dict to json str.
    def buildResponse(self, result, data=None):
        jstr = {}
        jstr['result'] = result
        jstr['data'] = data

        return json.JSONEncoder().encode(jstr)

class MyClient(object):
#decode json str to dict.
    def getResponse(self, jstr):
        result = json.JSONDecoder().decode(jstr)
        return result


svr = MyServer()
rsp = svr.buildResponse("server result.", ['data1', 'data2'])
print type(rsp),rsp

cli = MyClient()
result = cli.getResponse(rsp)
print type(result),result

