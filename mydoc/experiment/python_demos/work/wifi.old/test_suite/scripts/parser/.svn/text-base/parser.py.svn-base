#!/usr/bin/python

import sys
import os
import json
import parser_api
import scripts.lib.logtools as logtools
import scripts.lib.exceptions as exceptions

from scripts.factory import factory as factory

logger = logtools.logger
main_dir = sys.path[0]
scenarios_dir = main_dir + os.sep + "scenarios"
scripts_dir = main_dir + os.sep + "scripts"
scripts_parser = scripts_dir + os.sep + "parser"

#logtools.logger = logtools.getLogger()

class ScenarioBase:
    ''' a scenario.

        '''
    def __init__(self):
        self.m_name = ""
        self.m_catagory = ""
        self.m_vendor = ""
        self.m_serial = ""
        self.m_mac = ""
        self.m_type = "seq"
        self.m_file = ""
        self.m_parameters = {}
        self.mScenarios = []

    def set_name(self, n):
        self.m_name = n

    def set_type(self, t):
#TODO Currently no use
        if "" != t:
            self.m_type = t

    def set_script(self, fname):
        self.m_file = fname

    def set_vendor(self, vendor):
        scenario_catagory = self.m_catagory
        if vendor[scenario_catagory].has_key("model"):
            self.m_vendor = vendor[scenario_catagory]["model"]

        if vendor[scenario_catagory].has_key("serial"):
            self.m_serial = vendor[scenario_catagory]["serial"]

        if vendor[scenario_catagory].has_key("mac"):
            self.m_mac = vendor[scenario_catagory]["mac"]

        for scenario in self.mScenarios:
            scenario.set_vendor(vendor)

    def action(self):
        ''' excute the scenario.

            '''
        logger.info("--->Action Scenario: %s ." % (self.m_name))
        if(0 != len(self.m_file)):
            submodule = self.m_file.replace(os.sep, '.')
            submodule = submodule.replace('.py', '.run(self)')
            submodule = submodule[submodule.find("scenarios"):]
            exec "import " + submodule[:submodule.find(".run")]
            logger.debug("module to run is: %s ." % (submodule))
            try:
                exec submodule
            except Exception, e:
                logger.error(repr(e))
                raise exceptions.CustomException("Scenario:" + self.m_name + " excute error.")
        else:
            for scenario in self.mScenarios:
                logger.debug("subscenario:{" + scenario.m_name)
                scenario.action()
                logger.debug("}")

class CaseParser(parser_api.Parser):
    def __init__(self):
        parser_api.Parser.__init__(self)

    def __str__(self):
        ret = parser_api.Parser.__str__(self)
        return ret

    def parse_json(self, fname):
        ''' parse a json file into this object.
    '''
        logger.debug("Begin to parse case.")
        try:
            f = file(fname)
            s = json.load(f)
            f.close()
            self.parse_jsons(s)
        except Exception, e:
            logger.error(repr(e))
            raise exceptions.CustomException("Case json file:" + fname + " format error.")

    def parse_jsons(self, jstr):
        ''' parse a json string into this object.
    '''
        parser_api.Parser.parse_jsons(self, jstr)

        self.mScenarios = []
        for config in self.mScenarioConfig:
            scenario_obj = self.__get_scenario(config)
            self.mScenarios.append(scenario_obj)

        if not jstr.has_key("scenarios"):#TODO patch for old to be deleted
            self.supportOld=True
        else:
            self.supportOld=False

    def set_scenario_vendor(self,scenarioObj,vendor=None):
        if None != vendor:
            scenarioObj.set_vendor(vendor)

    def parse_subscenario(self, scenario, fname):
        scenarioGroupConfig = ScenariosGroup()
        scenarioGroupConfig.parse_json(fname)
        scenario.mScenarios = scenarioGroupConfig.mScenarios

        if scenarioGroupConfig.supportOld:#TODO patch for old to be deleted
            scenario.m_file = fname[:-4]+"py"


    def parse_scenario(self, scenario_name,vendor, scenario_catagory, s_fname, s_type_nam, s_type_param, s_param):
        logger.debug("Begin to parse scenario.")
        scenario_obj = ScenarioBase()
        scenario_obj.m_name = scenario_name
        scenario_obj.m_catagory = scenario_catagory
        scenario_obj.set_type(s_type_nam)
        #scenario_obj.set_type_param(s_type_param)
        scenario_obj.m_parameters = s_param
        self.set_scenario_vendor(scenario_obj,vendor)

        if '.py' == os.path.splitext(s_fname)[1]:
            scenario_obj.m_file = s_fname
        elif '.json' == os.path.splitext(s_fname)[1]:
            self.parse_subscenario(scenario_obj,s_fname)
        else:
            return None

        return scenario_obj

    def __get_scenario(self, config, vendor=None):
        scenario_catagory = ""
        scenario_fname = ""
        scenario_type_name = ""
        scenario_type_param = {}
        scenario_param = {}
        if(0 == len(config.keys())):
            return None

        if("fname" in config[config.keys()[0]]):
            if("catagory" in config[config.keys()[0]]):
                scenario_catagory = config[config.keys()[0]]["catagory"]
                scenario_fname = scenarios_dir + os.sep + self.map_dir[scenario_catagory] + os.sep + config[config.keys()[0]]["fname"]
            else:
                scenario_fname = config[config.keys()[0]]["fname"]

        if("type" in config[config.keys()[0]]):
            if("name" in config[config.keys()[0]]["type"]):
                scenario_type_name = config[config.keys()[0]]["type"]["name"]
            if("parameter" in config[config.keys()[0]]["type"]):
                scenario_type_param = config[config.keys()[0]]["type"]["parameter"]
        if("parameter" in config[config.keys()[0]]):
            scenario_param = config[config.keys()[0]]["parameter"]

        logger.debug("Scenario path:%s " % (scenario_fname))
        scenario_obj = self.parse_scenario(config.keys()[0],vendor, scenario_catagory, scenario_fname, \
                scenario_type_name, scenario_type_param, scenario_param)
        return scenario_obj

    def action(self, vendor):
        logger.debug("Begin to action Case: %s ." % (self.m_name))
        for scenario in self.mScenarios:
            self.set_scenario_vendor(scenario,vendor)

        if "seq" == self.m_type["name"]:
            for scenario in self.mScenarios:
                scenario.action()
        elif "loop" == self.m_type["name"]:
            if self.m_type.has_key("parameter"):
                if self.m_type["parameter"].isdigit():
                    count = int(self.m_type["parameter"])
                    for i in range(1, count + 1):
                        for scenario in self.mScenarios:
                            scenario.action()

    def run(self):
        logInfo = logtools.CaseDBLog()
        caseLog = {"caseLog":logInfo}
        logger.debug("Begin to run Case: %s ." % (self.m_name))
        logger.debug("Case ap:" + str(self.m_aps))

        if len(self.m_aps) > 0 and 0 == len(self.m_duts):
            for ap in self.m_aps:
                logger.debug("%s " % ("-----------------"))
                parser_api.g_context.set_ap_obj(factory.create(ap["model"], ap["mac"]))
                vendor = {}
                vendor["ap"] = ap
                try:
                    self.action(vendor)
                except Exception, e:
                    logger.error(e)
                    logInfo.name = self.m_name
                    logInfo.apModel = ap["model"]
                    logInfo.apMac = ap["mac"]
                    logInfo.status = "FAIL"
                    msg = "[%s] Case:'%s'." % (logInfo.status, logInfo.name)
                    msg += "ap:'%s',mac:'%s'." % (logInfo.apModel, logInfo.apMac)
                    logger.info(msg, extra = caseLog)
                    continue
                else:
                    logInfo.name = self.m_name
                    logInfo.apModel = ap["model"]
                    logInfo.apMac = ap["mac"]
                    logInfo.status = "OK"
                    msg = "[%s] Case:'%s'." % (logInfo.status, logInfo.name)
                    msg += "ap:'%s',mac:'%s'." % (logInfo.apModel, logInfo.apMac)
                    logger.info(msg, extra = caseLog)
                finally:
                    parser_api.g_context.clear()
                logger.debug("%s " % ("-----------------"))
            return

        if len(self.m_duts) > 0 and 0 == len(self.m_aps):
            for dut in self.m_duts:
                logger.debug("%s " % ("-----------------"))
                parser_api.g_context.set_dut_obj(factory.create(dut["model"], dut["mac"]))
                vendor = {}
                vendor["dut"] = dut

                try:
                    self.action(vendor)
                except Exception, e:
                    logger.error(e)
                    logInfo.name = self.m_name
                    logInfo.dutModel = dut["model"]
                    logInfo.dutMac = dut["mac"]
                    logInfo.status = "FAIL"
                    msg = "[%s] Case:'%s'." % (logInfo.status, logInfo.name)
                    msg += "dut:'%s',mac:'%s'." % (logInfo.dutModel, logInfo.dutMac)
                    logger.info(msg, extra = caseLog)
                    continue
                else:
                    logInfo.name = self.m_name
                    logInfo.dutModel = dut["model"]
                    logInfo.dutMac = dut["mac"]
                    logInfo.status = "OK"
                    msg = "[%s] Case:'%s'." % (logInfo.status, logInfo.name)
                    msg += "dut:'%s',mac:'%s'." % (logInfo.dutModel, logInfo.dutMac)
                    logger.info(msg, extra = caseLog)
                finally:
                    parser_api.g_context.clear()
                logger.debug("%s " % ("-----------------"))
            return

        if len(self.m_duts) > 0 and len(self.m_aps) > 0:
            for ap in self.m_aps:
                for dut in self.m_duts:
                    logger.debug("%s " % ("-----------------"))
                    parser_api.g_context.set_ap_obj(factory.create(ap["model"], ap["mac"]))
                    parser_api.g_context.set_dut_obj(factory.create(dut["model"], dut["mac"]))

                    vendor = {}
                    vendor["ap"] = ap
                    vendor["dut"] = dut

                    try:
                        self.action(vendor)
                    except Exception, e:
                        logger.error(e)
                        logInfo.name = self.m_name
                        logInfo.apModel = ap["model"]
                        logInfo.apMac = ap["mac"]
                        logInfo.dutModel = dut["model"]
                        logInfo.dutMac = dut["mac"]
                        logInfo.status = "FAIL"
                        msg = "[%s] Case:'%s'." % (logInfo.status, logInfo.name)
                        msg += "ap:'%s',mac:'%s'." % (logInfo.apModel, logInfo.apMac)
                        msg += "dut:'%s',mac:'%s'." % (logInfo.dutModel, logInfo.dutMac)
                        logger.info(msg, extra = caseLog)
                        continue
                    else:
                        logInfo.name = self.m_name
                        logInfo.apModel = ap["model"]
                        logInfo.apMac = ap["mac"]
                        logInfo.dutModel = dut["model"]
                        logInfo.dutMac = dut["mac"]
                        logInfo.status = "OK"
                        msg = "[%s] Case:'%s'." % (logInfo.status, logInfo.name)
                        msg += "ap:'%s',mac:'%s'." % (logInfo.apModel, logInfo.apMac)
                        msg += "dut:'%s',mac:'%s'." % (logInfo.dutModel, logInfo.dutMac)
                        logger.info(msg, extra = caseLog)
                    finally:
                        parser_api.g_context.clear()
                    logger.debug("%s " % ("-----------------"))
            return

class ScenariosGroup(CaseParser):
    def __init__(self):
        CaseParser.__init__(self)

    def __str__(self):
        CaseParser.__str__(self)
        return ret


def run(case_dir):
    cases_dir = main_dir + os.sep + case_dir
    cases_list = []
    if os.path.isfile(cases_dir) and (os.path.splitext(cases_dir)[1] == '.json'):#single file
        cases_list.append(cases_dir)
    else:
        file_type = ['.json']
        cases_list = parser_api.list_type(cases_dir, file_type)
        cases_list.sort()

    for fname in cases_list:
        c = CaseParser()

        try:
            c.parse_json(fname)
            logger.debug("Case name:%s " % (c.m_name))
        except Exception, e:
            logger.error(e)
            continue
        c.run()

######Main function.######
if "__main__" == __name__:
    cases_dir = main_dir + os.sep + "cases"
    run(cases_dir)
