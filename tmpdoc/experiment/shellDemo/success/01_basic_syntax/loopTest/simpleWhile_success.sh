#!/bin/bash
#一个简单的while循环测试程序。

#while循环更适合在循环次数未知的情况下使用.
#while [condition]
#do
#command...
#done 

#与for循环一样, while循环也可以通过(())来使用C风格的语法

#数字增1循环
var0=0
LIMIT=10

while [ "$var0" -lt "$LIMIT" ]
do
  echo -n "$var0 "        # -n 将会阻止产生新行. 
  #             ^           空格, 数字之间的分隔.

  var0=`expr $var0 + 1`   # var0=$(($var0+1))  也可以.
                          # var0=$((var0 + 1)) 也可以.
                          # let "var0 += 1"    也可以.
done                      # 使用其他的方法也行.
#注意=的左右没有空格。

echo

#检测输入循环
echo
                               # 等价于:
while [ "$var1" != "end" ]     # while test "$var1" != "end"
do
  echo "Input variable #1 (end to exit) "
  read var1                    # 为什么不使用'read $var1'?
  echo "variable #1 = $var1"   # 因为包含"#", 所以需要""
  # 如果输入为'end', 那么就在这里echo.
  # 不在这里判断结束, 在循环顶判断.
  echo
done  
 
exit 0
