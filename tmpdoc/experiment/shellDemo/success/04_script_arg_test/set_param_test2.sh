#!/bin/bash
#程序功能：一个重新设置参数的例子，这里包含把所有参数给uset了。

#如果使用参数--来调用set命令的话, 将会明确的分配位置参数. 如果--选项后边没有跟变量名的话, 那么结果就使得所有位置参数都被unsets了. 
variable="one two three four five"

set -- $variable
# 将位置参数的内容设为变量"$variable"的内容.

first_param=$1
second_param=$2
shift; shift        # 将最前面的两个位置参数移除.
remaining_params="$*"

echo
echo "first parameter = $first_param"             # one
echo "second parameter = $second_param"           # two
echo "remaining parameters = $remaining_params"   # three four five

echo; echo

# 再来一次.
set -- $variable
first_param=$1
second_param=$2
echo "first parameter = $first_param"             # one
echo "second parameter = $second_param"           # two

# ======================================================

set --
# 如果没指定变量,那么将会unset所有的位置参数.

first_param=$1
second_param=$2
echo "first parameter = $first_param"             # (null value)
echo "second parameter = $second_param"           # (null value)

exit 0
