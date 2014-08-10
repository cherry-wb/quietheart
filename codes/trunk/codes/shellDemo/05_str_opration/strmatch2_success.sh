#!/bin/bash
#程序功能：补充点，匹配之前声明过的变量名


#${!varprefix*}, ${!varprefix@}
#匹配所有之前声明过的, 并且以varprefix开头的变量
# Bash, 版本2.04, 添加了这个功能.

xyz23=whatever
xyz24=

a=${!xyz*}      # 展开所有以"xyz"开头的, 并且之前声明过的变量名.
echo "a = $a"   # a = xyz23 xyz24
a=${!xyz@}      # 同上.
echo "a = $a"   # a = xyz23 xyz24
