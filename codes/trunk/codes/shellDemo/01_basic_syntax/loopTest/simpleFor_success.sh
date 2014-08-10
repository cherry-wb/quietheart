#!/bin/bash
#程序功能：一个简单的循环程序

#对于for循环
#for arg in "$var1" "$var2" "$var3" ... "$varN"  
# 在第1次循环中, arg = $var1	    
# 在第2次循环中, arg = $var2	    
# 在第3次循环中, arg = $var3	    
# ...
# 在第N此循环中, arg = $varN
# 在[list]中的参数加上双引号是为了阻止单词分割.

#如果do和for想在同一行中出现, 那么在它们之间需要添加一个分号.
#for arg in [list] ; do 


# 列出所有的行星名称. (译者注: 现在的太阳系行星已经有了变化^_^)
for planet in Mercury Venus Earth Mars Jupiter Saturn Uranus Neptune Pluto
do
  echo $planet  # 每个行星都被单独打印在一行上.
done

echo

for planet in "Mercury Venus Earth Mars Jupiter Saturn Uranus Neptune Pluto"
# 所有的行星名称都打印在同一行上.
# 整个'list'都被双引号封成了一个变量. 
do
  echo $planet
done

#在一个for循环中忽略in [list]部分的话, 将会使循环操作$@ -- 从命令行传递给脚本的位置参数. 
for a
do
echo $a
done
#+ [list]是由命令替换所产生的.

NUMBERS="9 7 3 8 37.53"
for number in `echo $NUMBERS`  # for number in 9 7 3 8 37.53
do
  echo -n "$number "
 done
 
 echo 

exit 0
