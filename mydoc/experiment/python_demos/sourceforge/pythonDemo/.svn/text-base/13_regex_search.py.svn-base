#!/usr/bin/python
import re
myStr = "helloworld"
myReg = "^.*lo"

match = re.search(myReg, myStr)
print match.group(0)

myHtmlPage = """
<html>
<head>
</head>
<body>
<form>
<input name="aa" value="11">
<input name="bb" value="22">
</form>
</body>
</html>
"""
myReg = r"<form.*/form>"
match = re.search(myReg, myHtmlPage, re.S)
formContent = match.group(0)
print formContent

selfMatch = re.compile(r"\s*?<input .*? name.*?>", re.S)
print selfMatch.findall(formContent)

simpleMatch = re.findall(r"\s*?<input .*? name.*?>", formContent, re.S)
print simpleMatch
for matched in simpleMatch:
    matchName = re.search(r".*?name\s*?=\s*?\"(\S*?)\"",matched, re.S).group(1)
    print "matched name:",matchName
    matchValue = re.search(r".*?value\s*?=\s*?\"(\S*?)\"",matched, re.S).group(1)
    print "matched value:",matchValue

