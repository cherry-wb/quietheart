#! /bin/bash
#程序功能：匹配字符串字串的两个方法,返回匹配的长度。
#其中，子串（第2个参数）可以是正则表达式。

#1,expr match "$string" '$substring'
#$substring是一个正则表达式.

#2,expr "$string" : '$substring'
#$substring是一个正则表达式.

stringZ=abcABC123ABCabc
#       |------|

echo `expr match "$stringZ" 'abc[A-Z]*.2'`   # 8
echo `expr "$stringZ" : 'abc[A-Z]*.2'`       # 8
