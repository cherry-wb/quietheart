#!/bin/bash
#程序功能：利用break和continue来控制循环。

#break命令用来跳出循环(应该是n重的循环都行), 而continue命令只会跳过本次循环, 忽略本次循环剩余的代码, 进入循环的下一次迭代. 

#break命令可以带一个参数. 一个不带参数的break命令只能退出最内层的循环, 而break N可以退出N层循环. 
#continue命令也可以象break命令一样带一个参数. 一个不带参数的continue命令只会去掉本次循环的剩余代码. 而continue N将会把N层循环的剩余代码都去掉, 但是循环的次数不变. 
# 关于循环层数，设双重循环则continue 2是在第2层循环上的continue, 也就是"外部循环"

LIMIT=19  # 上限

echo
echo "Printing Numbers 1 through 20 (but not 3 and 11)."

a=0

while [ $a -le "$LIMIT" ]
do
 a=$(($a+1))

 if [ "$a" -eq 3 ] || [ "$a" -eq 11 ]  # 除了3和11.
 then
   continue      # 跳过本次循环剩余的语句.
 fi

 echo -n "$a "   # 在$a等于3和11的时候，这句将不会执行.
done 

# 练习:
# 为什么循环会打印出20?

echo; echo

echo Printing Numbers 1 through 20, but something happens after 2.

##################################################################

# 同样的循环, 但是用'break'来代替'continue'.

a=0

while [ "$a" -le "$LIMIT" ]
do
 a=$(($a+1))

 if [ "$a" -gt 2 ]
 then
   break  # 将会跳出整个循环.
 fi

 echo -n "$a "
done

echo; echo; echo

exit 0
