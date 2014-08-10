#!/bin/bash
#程序功能：运行set将会设置脚本的参数。
#利用命令set par1 par2...将会把参数$1,$2...依次设置成为par1,par2...

# 比如, "./set-test one two three".
#打印设置之前的参数值
echo
echo "Positional parameters before  set \`uname -a\` :"
echo "Command-line argument #1 = $1"
echo "Command-line argument #2 = $2"
echo "Command-line argument #3 = $3"


#设置参数
#这里将位置参数设置为uname -a的输出。每个参数对应一个输出，每个输出用空格分开。
set `uname -a` # 把`uname -a`的命令输出设置
               # 为新的位置参数.

#打印传入的最近命令的最后一个参数
echo $_ 


#显示设置之后的参数结果
# $1, $2, $3, 等等. 这些位置参数将被重新初始化为`uname -a`的结果
echo "Positional parameters after  set \`uname -a\` :"
echo "Field #1 of 'uname -a' = $1"
echo "Field #2 of 'uname -a' = $2"
echo "Field #3 of 'uname -a' = $3"
echo "Field #4 of 'uname -a' = $4" #即使是没有被传的参数$4$5也会被设置
echo "Field #5 of 'uname -a' = $5"
echo ---
echo $_        # ---
echo

exit 0
