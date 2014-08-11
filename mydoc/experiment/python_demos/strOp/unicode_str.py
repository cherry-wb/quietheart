import types

def switchUnicode2String(source):
    if type(source) is types.UnicodeType:
        return source.encode()
    else:
        return source

#filehandler=file.read().decode(sys.getfilesystemencoding()).encode('utf-8')
