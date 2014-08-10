#!/bin/bash
#据说上面感叹号后面的空格是必须的。
#本例子主要测试各种条件
#提示：通过man test可以查看"-f"等所有的判断标记的含义。

#文件新旧
if [ $file1 -ot $file2 ]
 then
   echo "File $file1 is older than $file2."
fi

#参数$1是一个文件名字，然后检查是否存在该文件。
if [ ! -f "$1" ]
then
echo "File \"$1\" doesn't exist."
else
echo "File \"$1\" does exist."
fi

#检测一个文件，如果不存在则输出相应信息
if ! [ -e ./testfile ]; then
echo "testfile not exists"
fi
 
#相等
if [ "$a" -eq "$b" ]
then
  echo "$a is equal to $b."
fi
 
#逻辑
if [ "$c" -eq 24 -a "$d" -eq 47 ]
then
  echo "$c equals 24 and $d equals 47."
fi

###简洁测试
#测试变量值，如果是mytest则执行echo good
__myarg=mytest
[ $__myarg = "mytest" ] && echo "good"

#不存在tt1目录则执行
[ -d tt1 ] || echo "no tt1"

#存在tt2目录则执行
[ -d tt2 ] && echo "have tt"

#复合语句的实践,用{}括上，返回值是最后一条命令的返回值
[ -d tt3 ] && 
{
echo "have tt3"
echo "have tt3"
echo "have tt3"
ls |grep lll
}&&
echo "have lll"
