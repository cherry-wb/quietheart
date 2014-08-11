#!/bin/bash
#程序功能：一个简单的测试until的程序

#这个结构在循环的顶部判断条件, 并且如果条件一直为false, 那么就一直循环下去. (与while循环相反).
#until [condition-is-true]
#do
#nbsp;command...
#done 

END_CONDITION=end

until [ "$var1" = "$END_CONDITION" ]
# 在循环的顶部进行条件判断.
do
  echo "Input variable #1 "
  echo "($END_CONDITION to exit)"
  read var1
  echo "variable #1 = $var1"
  echo
done  

exit 0
