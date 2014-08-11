
def append(self, msg):
    tlocal = ThreadLocal.getInstance()

    tobj = tlocal.get()
    if not tobj.has_key(self.LOG_KEY):
        tobj[self.LOG_KEY] = []

    tlog = tobj[self.LOG_KEY]
tlog.append(msg)
