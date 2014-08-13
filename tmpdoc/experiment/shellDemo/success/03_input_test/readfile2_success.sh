#!/bin/bash
#程序功能：更高级的利用read读取文件的方法。

#read var1 <data-file
# var1将会把"data-file"的第一行的全部内容都为它的值.
read var1 <$0
echo "var1 = $var1"
# var1将会把文件"$0"的第一行的全部内容都为它的值.

#read var2 var3 <data-file
read var2 var3 <$0
echo "var2 = $var2   var3 = $var3"
# 注意, 这里的"read"命令将会产生一种不直观的行为. 
# 1) 重新从文件的开头开始读入变量.
# 2) 每个变量都设置成了以空白分割的字符串.
#    而不是之前的以整行的内容作为变量的值.
# 3) 而最后一个变量将会取得第一行剩余的全部部分(译者注: 不管是否以空白分割).
# 4) 如果需要赋值的变量个数比文件中第一行以空白分割的字符串个数还多的话, 
#    那么这些变量将会被赋空值.

echo "------------------------------------------------"

# 如何用循环来解决上边所提到的问题:
while read line
do
  echo "$line"
done <$0
#done <data-file
# 感谢, Heiner Steven 指出了这点.

echo "------------------------------------------------"

# 使用$IFS(内部域分隔变量)来将每行的输入单独的放到"read"中,
# 前提是如果你不想使用默认空白的话.

echo "List of all users:"
OIFS=$IFS; IFS=:       # /etc/passwd 使用 ":" 作为域分隔符.
while read name passwd uid gid fullname ignore
do
  echo "$name ($fullname)"
done </etc/passwd   # I/O 重定向.
IFS=$OIFS              # 恢复原始的$IFS.
# 这段代码也是Heiner Steven编写的.



#  在循环内部设置$IFS变量, 
#+ 而不用把原始的$IFS
#+ 保存到临时变量中.
#  感谢, Dim Segebart, 指出了这点.
echo "------------------------------------------------"
echo "List of all users:"

while IFS=: read name passwd uid gid fullname ignore
do
  echo "$name ($fullname)"
done </etc/passwd   # I/O 重定向.

echo
echo "\$IFS still $IFS"


echo "------------------------------------------------"
#使用管道来读取文件
#使用管道echo输出来设置变量将会失败.
#然而, 使用管道cat输出看起来能够正常运行. 

cat $0 |
while read line
do
	echo $line
done

#但是管道也是有时候有问题的，如下：
 #!/bin/sh
 # readpipe.sh
 # 这个例子是由Bjon Eriksson所编写的.
 
# last="(null)"
# cat $0 |
# while read line
# do
#     echo "{$line}"
#     last=$line
# done
# printf "\nAll done, last:$last\n"
# 
# exit 0  # 代码结束.
#         # 下边是脚本的(部分)输出.
#         # 'echo'出了多余的大括号.
 
 #########输出####################################
 
# ./readpipe.sh 
# {#!/bin/sh}
# {last="(null)"}
# {cat $0 |}
# {while read line}
# {do}
# {echo "{$line}"}
# {last=$line}
# {done}
# {printf "nAll done, last:$lastn"}
 
 
# All done, last:(null)
 
#变量(last)被设置在子shell中, 并没有被设置在外边. 
exit 0
