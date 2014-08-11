# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

class TestCase (object):
    def __init__(self):
        self.name = ""
        self.apList = []
        self.dutList = []
        self.scenarioList = []

    def run(self):
        pairList = self._pairApDut(self.apList, self.dutList)
        for pair in pairList:
            for scenario in self.scenarioList:
                context = self._getContext()
                context['ap'] = pair['ap']
                context['dut'] = pair['dut']
                context['category'] = scenario.category
                context['parameter'] = scenario.parameter
                scenario.run(context)

    def _pairApDut(self, apList, dutList):
        apList = []
        dutList = []
        pairList = []

        #ApList
        if len(self.apList) == 1 and self.apList[0]['model'] == 'all':
            """
            TODO, database is reconstructing
            """
        elif len(self.apList) == 0:
            apList.append(None)
        else:
            apList = self.apList

        #DutList
        if len(self.dutList) == 1 and self.dutList[0]['model'] == 'all':
            """
            TODO, how to get dut from database
            """
        elif len(self.dutList) == 0:
            dutList.append(None)
        else:
            dutList = self.dutList

        #Associate them
        for ap in apList:
            for dut in dutList:
                pair = {"ap":ap, "dut":dut}
                pairList.append(pair)

        return pairList

    def _getContext(self):
        context = {}
        return context


class Scenario (object):
    """
    Create Scenario object when xml_parser occurs scenario tag.
    
    All scenario attributes are designed as a string which can convert to 
    corresponding structure in every scenario python script
    """
    def __init__(self, name, category, script, parameter):
        self.name = name
        self.category = category
        self.script = script
        self.parameter = parameter

    def run (self, context):
        """TODO, workaround, should manage all CONSTANT in Config file"""
        SCENARIO_MODULE_PREFIX = 'scenarios.'

        suffixPos = self.script.find('.py')
        module = SCENARIO_MODULE_PREFIX + self.script[:suffixPos]
        run = module + ".run(context)"
        print 'module=', module
        print 'run=', run

        try:
            exec "import " + module
            exec run
        except Exception, e:
            """
            TODO, handle exception
            """
            print e
