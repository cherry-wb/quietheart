#!/bin/bash
#程序功能：如果没有给定一个参数，那么脚本自动提供一个默认的参数。

# 如果没有指定值, 那么下面的代码块参数将会使用filename
#+ 变量的默认值"generic.data".
DEFAULT_FILENAME=generic.data
filename=${1:-$DEFAULT_FILENAME}
echo "the parameter you input is: $1"
echo "the default parameter is: $filename"
