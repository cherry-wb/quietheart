class CustomException(Exception):
    def __init__(self,msg):
        self.msg = msg

    def __str__(self):
        return repr(self.msg)

if "__main__" == __name__:
    try:
        print 'normal.'
        raise CustomException("a warning exception.")
        print 'never reach here.'
    except (CustomException),e:
        print e
    except Exception:
        print "other exception."
