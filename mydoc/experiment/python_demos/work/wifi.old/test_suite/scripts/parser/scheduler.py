# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

import os

from xml_parser import XmlCaseParser

class Scheduler (object):
    def __init__(self):
        """
        """

    def schedule(self, path):
        xmlCases = self.listXmlCases(path)
        parser = XmlCaseParser()

        for xmlCase in xmlCases:
            testcase = parser.parse(xmlCase)
            testcase.run()

    def listXmlCases(self, path):
        xmlFiles = []
        args = {'suffix':'.xml', 'xmlFiles':xmlFiles}
        os.path.walk(path, self.listFiles, args)
        print xmlFiles
        return xmlFiles

    def listFiles(self, args, dirname, filenames):
        for filename in filenames:
            fpath = dirname + os.sep + filename
            if os.path.isfile(fpath) and os.path.splitext(fpath)[1] == args['suffix']:
                args['xmlFiles'].append(fpath)

if __name__ == '__main__':
    scheduler = Scheduler()
    scheduler.schedule('../../cases')

