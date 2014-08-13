#!/bin/bash
#程序功能：一个比较荒唐的测试，检查是否能够用$var来进行赋值。
var=good
echo "var is: $var"
"$var"=yes #这里报错了
echo "after \"\$var=yes\",var is:$var" #结果是var的值也没有变化。
