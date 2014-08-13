#!/bin/bash
# 程序功能：利用 case来测试字符串范围.

#注意，这个程序只能够输入一个字符，如果输入多个字符，将执行分支*的语句。
#  允许字符串的范围出现在[中括号]中,
#+ 或者出现在POSIX风格的[[双中括号中.

#  在这个例子的第一个版本中,
#+ 测试大写和小写字符串的工作使用的是
#+ [a-z] 和 [A-Z].
#  这种用法在某些特定场合的或某些Linux发行版中不能够正常工作.
#  POSIX 的风格更具可移植性.
echo; echo "Hit a key, then hit return."
read Keypress

case "$Keypress" in
[[:lower:]]   ) echo "Lowercase letter";;
[[:upper:]]   ) echo "Uppercase letter";;
[0-9]         ) echo "Digit";;
*             ) echo "Punctuation, whitespace, or other";; 
#实际这里可以有a | b)这样的表达方式
esac     

exit 0
