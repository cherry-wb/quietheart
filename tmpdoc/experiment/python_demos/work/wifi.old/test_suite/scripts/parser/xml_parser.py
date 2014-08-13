# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

from testcase import TestCase
from testcase import Scenario
from xml.dom import minidom

class XmlParser (object):
    def __init__(self):
        """
        """

    def getAttrValue(self, node, attrName):
        return node.getAttribute(attrName) if node else ''

    def getNodeValue(self, node, index = 0):
        if node is None or len(node.childNodes) == 0:
            return ''
        else:
            return node.childNodes[index].nodeValue

    def getXmlNodes(self, node, name):
        return node.getElementsByTagName(name) if node else []


class XmlCaseParser (XmlParser):
    def __init__(self):
        """
        """

    def parse(self, xmlPath):
        doc = minidom.parse(xmlPath)
        root = doc.documentElement

        nameNodes = self.getXmlNodes(root, 'name')
        caseName = self.getNodeValue(nameNodes[0])

        apList = []
        apsNodes = self.getXmlNodes(root, 'aps')
        apNodes = self.getXmlNodes(apsNodes[0], 'ap')
        for apNode in apNodes:
            model = self.getAttrValue(apNode, 'model')
            mac = self.getAttrValue(apNode, 'mac')
            apList.append({"model":model, "mac":mac})

        dutList = []
        dutsNodes = self.getXmlNodes(root, 'duts')
        dutNodes = self.getXmlNodes(dutsNodes[0], 'dut')
        for dutNode in dutNodes:
            model = self.getAttrValue(dutNode, 'model')
            mac = self.getAttrValue(dutNode, 'mac')
            dutList.append({"model":model, "mac":mac})

        scenarioList = []
        scenariosNodes = self.getXmlNodes(root, 'scenarios')
        scenarioNodes = self.getXmlNodes(scenariosNodes[0], 'scenario')
        for scenarioNode in scenarioNodes:
            scenarioName = self.getAttrValue(scenarioNode, 'name')

            categoryNodes = self.getXmlNodes(scenarioNode, 'category')
            categoryValue = self.getNodeValue(categoryNodes[0])

            scriptNodes = self.getXmlNodes(scenarioNode, 'script')
            scriptValue = self.getNodeValue(scriptNodes[0])

            parameterNodes = self.getXmlNodes(scenarioNode, 'parameter')
            parameterValue = self.getNodeValue(parameterNodes[0])

            scenario = Scenario(scenarioName, categoryValue, scriptValue, parameterValue)
            scenarioList.append(scenario)

        testCase = TestCase()
        testCase.name = caseName
        testCase.apList = apList
        testCase.dutList = dutList
        testCase.scenarioList = scenarioList

        return testCase
