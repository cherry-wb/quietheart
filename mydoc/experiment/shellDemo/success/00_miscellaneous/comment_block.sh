#!/bin/bash
#注释shell的一段代码
#limit string用来界定命令序列的范围(译者注: 两个相同的limit string之间就是命令序列). 特殊符号<<用来标识limit string. 这个符号的作用就是将文件的输出重定向到程序或命令的stdin中.
#set -x
#set -v
:<<COMMENTBLOCK
echo good
echo good2
echo good3
COMMENTBLOCK
#set +x
echo good4
:<<BLOCK
echo good5
echo good6
BLOCK
echo good7

