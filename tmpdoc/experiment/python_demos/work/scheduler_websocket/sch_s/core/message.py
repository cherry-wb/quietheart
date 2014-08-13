# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.

class Message(object):

    CMD_REGISTER    = 'register'
    CMD_RELEASE     = 'release'

    STATUS_Y = 'y'
    STATUS_N = 'n'
    STATUS_BUSY = 'busy'


    def __init__(self):
        ""
        self.id = None
        self.cmd = self.CMD_REGISTER
        self.res = None
        self.status = self.STATUS_Y
        #self.status = self.STATUS_BUSY

    def getId(self):
        ""
        return self.id

    def getCmd(self):
        ""
        return self.cmd

    def getRes(self):
        ""
        return self.res

    def getStatus(self):
        ""
        return self.status

    def restore(self, json):
        ""
        message = Message()
        message.res = json
        return message