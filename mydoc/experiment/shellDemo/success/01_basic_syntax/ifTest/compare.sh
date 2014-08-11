#!/bin/bash
#功能：测试字符串比较和算术比较。
a=4
b=5
c="good"

#  这里的"a"和"b"既可以被认为是整型也可被认为是字符串. 
#  这里在算术比较与字符串比较之间是容易让人产生混淆, 
#+ 因为Bash变量并不是强类型的.

#  Bash允许对于变量进行整形操作与比较操作.
#+ 但前提是变量中只能包含数字字符.
#  不管怎么样, 还是要小心. 

echo

if [ "$a" -ne "$b" ]
then
echo "$a is not equal to $b" #这个是算术比较
echo "(arithmetic comparison)"
fi

echo

if [ "$a" != "$b" ]
then
echo "$a is not equal to $b." #这个是字符串比较
echo "(string comparison)"
#     "4"  != "5"
# ASCII 52 != ASCII 53
fi

if [ "$1" = "good" ]
then
echo "param1 is good!"
fi

# 在这个特定的例子中, "-ne"和"!="都可以. 

echo

exit 0
