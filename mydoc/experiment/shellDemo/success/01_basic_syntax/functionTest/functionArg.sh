#! /bin/bash
#功能：测试函数的定义，使用以及函数的参数。
printStr()
{
#注意这里函数的参数和脚本的参数不同,
	echo "the arg in the function is:$1,$2"

#这里是函数的参数数目
	echo "arg num:$#"

#实践发现$0还是脚本名
	echo "arg0: $0"
	#return 0 #可以用return命令来返回函数,使用exit就退出整个脚本了
}

if [ $# -eq 0 ]
then
echo "usage:`basename $0` arg1"
exit 0
fi
echo "the arg in the script is $1"
printStr "first" "second"
