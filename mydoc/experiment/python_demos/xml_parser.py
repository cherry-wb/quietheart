#!/usr/bin/python
from xml.dom import minidom
#Element(node,or tag + element),Element attribute,Element value.

#The file content of sample.xml is:
'''
<?xml version="1.0" encoding="UTF-8" ?>
<myroot>
    <name>sample</name>
    <mylists>
        <myitem myid="item1" myproperty="item1 property 1" />
        <myitem myid="item2" myproperty="item2 property 2" />
    </mylists>
 
    <mystruct>
        <substruct name="sub1">
            <category>category1</category>
            <file>sub1.py</file>
            <parameter></parameter>
        </substruct>

        <substruct name="sub2">
            <category>category2</category>
            <file>sub2.py</file>
            <parameter name="desc"> the sub2 </parameter>
        </substruct>

        <substruct name="sub3">
            <category>category3</category>
            <file>sub3.py</file>
            <parameter></parameter>
        </substruct>
    </mystruct>
</myroot>
'''




class MyXmlParser(object):
    def parse(self,fpath):
        doc = minidom.parse(fpath)
        print '-' * 20
        print "get root:"
        root = doc.documentElement
        print "root:",root
        print

#############'name'
        print '-' * 20
        print "get root name children"
        rootNameChildren = None
        if root:
            rootNameChildren = root.getElementsByTagName('name')
        else:
            rootNameChildren = []
        print "root name children:",rootNameChildren
        print
        nameNodeValue = rootNameChildren[0].childNodes[0].nodeValue
        print "name children[0] value:",nameNodeValue

#############'mylists'
        print '-' * 20
        print "get root mylist children"
        rootListChildren = None
        if root:
            rootListChildren = root.getElementsByTagName('mylists')
        else:
            rootListChildren = []
        print "root mylist children:",rootNameChildren
        print

        listItemChildren = None
        if rootListChildren[0]:
            listItemChildren = rootListChildren[0].getElementsByTagName('myitem')
        else:
            listItemChildren = []
        #print "listItemChildren:",listItemChildren
        for item in listItemChildren:
            itemId = item.getAttribute('myid') if item else ''
            itemP = item.getAttribute('myproperty') if item else ''
            print "item id:",itemId
            print "item myproperty:",itemP

#############'mystruct'
        print '-' * 20
        print "get root struct children"
        rootStructChildren = None
        if root:
            rootStructChildren = root.getElementsByTagName('mystruct')
        else:
            rootStructChildren = []
        print "root struct children:",rootNameChildren
        print

        structSubChildren = None
        if rootStructChildren:
            structSubChildren = rootStructChildren[0].getElementsByTagName('substruct')
        else:
            structSubChildren = []

        for sub in structSubChildren:
            subName = sub.getAttribute('name') if sub else '' #node attribute
            print "subName:",subName

            subCategoryNodes = sub.getElementsByTagName('category') #child nodes
            if subCategoryNodes is None or len(subCategoryNodes[0].childNodes) == 0:
                suCategoryNodesValue = ""
            else:
                suCategoryNodesValue = subCategoryNodes[0].childNodes[0].nodeValue #node value
            print "catagory:",suCategoryNodesValue

            subFileNodes = sub.getElementsByTagName('file')
            if subFileNodes is None or len(subFileNodes[0].childNodes) == 0:
                subFileNodesValue = ""
            else:
                subFileNodesValue = subFileNodes[0].childNodes[0].nodeValue
            print "file:",subFileNodesValue

            subParameterNodes = sub.getElementsByTagName('parameter')
            paramName = subParameterNodes[0].getAttribute('name') if subParameterNodes[0] else "" #only use the first
            print "parameter name:",paramName
            if subParameterNodes is None or len(subParameterNodes[0].childNodes) == 0:
                subParameterNodesValue = ""
            else:
                subParameterNodesValue = subParameterNodes[0].childNodes[0].nodeValue
            print "parameter value:",subParameterNodesValue

parser = MyXmlParser()
parser.parse("sample.xml")
