#!/usr/bin/python
'''an example for generate html page.
the module used is:PyH
Its home page is: http://code.google.com/p/pyh/
we can download it at:http://code.google.com/p/pyh/downloads/detail?name=PyH-0.1.1.tar.gz&can=2&q=
More things about html at:http://www.w3school.com.cn/tags/tag_div.asp
'''
from pyh import *
page = PyH("MyPage")
#page.addCSS('myStylesheet1.css', 'myStylesheet2.css')
#page.addJS('myJavascript1.js', 'myJavascript2.js')

#<h1 align="center">MyTitle1</h1>
page <<h1('MyTitle1',align='center')

#<div align="center" id="myDiv1"><p id="myp1">my paragraph1</p>
#</div>
page << div(align='center',id='myDiv1') << p('my paragraph1',id='myp1')

#<div id="myDiv2"><h2>title2 in div2<p>paragraph under title2</p>
#</h2>
#</div>
mydiv2 = page << div(id='myDiv2')
mydiv2 <<h2('title2 in div2') << p('paragraph under title2')

#<div align="right" id="myDiv3"><p>paragraph in mydiv3</p>
#</div>
mydiv3 = page << div(id='myDiv3')
mydiv3.attributes['align'] = 'right'
mydiv3 << p('paragraph in mydiv3')

#<table border="1" id="mytable1"><tr id="headline"><td>Head1<td>Head2</td>
#</td>
#</tr>
#<tr id="line1"><td>r1,c1<td>r1,c2</td>
#</td>
#</tr>
#<tr id="line2"><td>r2,c1<td>r2,c2</td>
#</td>
#</tr>
#</table>
table1 = page << table(border='1',id='mytable1')
headtr = table1 << tr(id='headline')
headtr << td('Head1') << td('Head2')

tr1  = table1 << tr(id='line1')
tr1 << td('r1,c1') <<td('r1,c2')

tr2 = table1 << tr(id='line2')
tr2 << td('r2,c1') <<td('r2,c2')



#The result is:
#<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
#<html lang="en" xmlns="http://www.w3.org/1999/xhtml"><head><title>MyPage</title>
#</head>
#<body><h1 align="center">MyTitle1</h1>
#<div align="center" id="myDiv1"><p id="myp1">my paragraph1</p>
#</div>
#<div id="myDiv2"><h2>title2 in div2<p>paragraph under title2</p>
#</h2>
#</div>
#<div align="right" id="myDiv3"><p>paragraph in mydiv3</p>
#</div>
#<table border="1" id="mytable1"><tr id="headline"><td>Head1<td>Head2</td>
#</td>
#</tr>
#<tr id="line1"><td>r1,c1<td>r1,c2</td>
#</td>
#</tr>
#<tr id="line2"><td>r2,c1<td>r2,c2</td>
#</td>
#</tr>
#</table>
#</body>
#</html>
page.printOut()

