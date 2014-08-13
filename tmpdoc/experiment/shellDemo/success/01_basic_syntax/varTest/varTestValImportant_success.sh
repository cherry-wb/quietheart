#!/bin/bash
#程序功能：测试一个变量是否等于一个值

#需要注意的是,因为D可能为空，这时直接用$D判断会报错说没有==操作，所以用x$D。
D=$1

#如果D是33，则执行echo
[ x$D == "x33" ] && echo "D is 33"

#如果D不是33，则执行echo
[ x$D == "x33" ] || echo "D is not 33"

[ -z $D ] && echo "D is null"
