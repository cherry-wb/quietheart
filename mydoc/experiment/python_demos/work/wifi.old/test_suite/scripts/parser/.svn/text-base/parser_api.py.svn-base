
import os
import time
import json

import scripts.db.dbmanager as dbtools

class Parser:
    def __init__(self):
        self.m_name = ''
        self.m_type = {"name":"seq"}
        self.m_aps = []
        self.m_duts = []
        self.m_description = ''
        self.mScenarioConfig = []
        self.mScenarios = []
        self.map_dir = {"ap":"ap", "dut":"device"}

    def __str__(self):
        ret = "m_name:" + self.m_name +'\n'
        ret += "m_type:" + str(self.m_type) + '\n'
        ret += "m_description:" + str(self.m_description) + '\n'
        ret += "mScenarioConfig:" + str(self.mScenarioConfig) + '\n'
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
            elif "ap" == key:
                self.m_aps=jstr["ap"]
                for ap in self.m_aps:
                    if "all" == ap["model"] and "all" == ap["mac"]:
                        self.m_aps = []
                        dbtools.database.connect()
                        aps = dbtools.database.getApVendorMacs()
                        dbtools.database.disconnect()
                        for model,mac in aps:
                            item = {"model":model,"mac":mac}
                            self.m_aps.append(item)
                        break
            elif "dut" == key:
                self.m_duts=jstr["dut"]
                for dut in self.m_duts:
#TODO for "all" Keyword of dut
                    if "all" == dut["model"] and "all" == dut["mac"]:
                        pass
            elif "description" == key:
                self.m_description=jstr["description"]
            elif "scenarios" == key:
                for scenario in jstr[key]:
                    self.mScenarioConfig.append(scenario)

class Context:
    ''' Store the ap and dut information.
        '''
    def __init__(self):
        self.ap_obj = None
        self.dut_obj = None

    def set_ap_obj(self,ap):
        self.ap_obj = ap
        
    def get_ap_obj(self):
        return self.ap_obj

    def set_dut_obj(self,dut):
        self.dut_obj = dut

    def get_dut_obj(self):
        return self.dut_obj


    def clear(self):
        self.ap_obj = None
        self.dut_obj = None

g_context = Context()

def __list_type(list_args,dirname,fname):
    for i in fname:
        if os.path.isfile(dirname+os.sep+i) and (os.path.splitext(dirname+os.sep+i)[1] 
                in list_args["types"]):
            list_args["scripts"].append(dirname+os.sep+i)

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


