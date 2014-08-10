#!/bin/bash
# Embedding Ctl-H in a string.

a="^H^H"                  # 两个 Ctl-H's (backspaces).
echo "abcdef"             # abcdef
echo -n "abcdef$a "       # abcd f
#  Space at end  ^              ^ 两次退格.
echo -n "abcdef$a"        # abcdef
#  结尾没有空格                   没有 backspace 的效果了(why?).
                          # 结果并不像期望的那样.

echo -e "abcdef\bg"        # abcdeg
echo  "abcdef\bg"        # abcdef\bg
echo; echo
