#! /bin/bash
#程序功能：匹配字串在字符串里面第一次出现的位置
stringZ=abcABC123ABCabc
echo `expr index "$stringZ" C12`             # 6
                                             # C 字符的位置.

echo `expr index "$stringZ" 1c`              # 3
# 'c' (in #3 position) matches before '1'.
