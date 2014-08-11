#!/bin/sh
#程序功能：一个测试getopt命令的简单的例子

#使用方法与输出结果：
#./getoptSimple.sh -ab将输出处理a,b的相关语句
#./getoptsimple.sh -e什么也不输出
#./getoptsimple.sh -e2将输出处理e的语句
#./getoptsimple.sh -ae2b将输出处理a,e的语句
#./getoptsimple.sh -abe2将输出处理a,b,e的语句
#./getoptsimple.sh -ae2 -b将输出处理a,e,b的语句
#./getoptsimple.sh -ab2将输出处理a,b的语句

#说明:
# a, b, c, d, e, f, 和 g 被认为是选项(标志).
# 'e' 选项后边的 : 提示这个选项需要带一个参数.
# 译者注:	解释一下 'a' 前边的那个 : 的作用.
#			如果选项'e'不带参数进行调用的话, 会产生一个错误信息.
#			这个开头的 : 就是用来屏蔽掉这个错误信息的, 
#			因为我们一般都会有默认处理, 所以并不需要这个错误信息.

echo "param#1 is: $1"
while getopts ":abcde:fg" Option
do
  case $Option in
    a ) # 对选项'a'作些操作.
	echo "this is a:"
	echo "$Option"
	;;
    b ) # 对选项'b'作些操作.
	echo "this is b:"
	echo "$Option"
	;;
    e)  # 对选项'e'作些操作, 同时处理一下$OPTARG,
        # 这个变量里边将保存传递给选项"e"的参数$OPTARG.
	echo "this is e:"
	echo "$Option, and param of e is:$OPTARG"
	;;
    f)  # 对选项'f'作些操作, 同时处理一下$OPTARG,
	echo "this is f:"
	echo "$Option"
	;;
    g ) # 对选项'g'作些操作.
	echo "this is g:"
	echo "$Option"
	;;
  esac
done
shift $(($OPTIND - 1))
# 将参数指针向下移动.

# 所有这些远没有它看起来的那么复杂.<嘿嘿>.
      


