#!/bin/bash
#程序功能：read用于提示的时候

# 不敲回车, 读取一个按键字符.
#-s 选项意味着不打印输入.
#-n N 选项意味着只接受N个字符的输入.
#-p 选项意味着在读取输入之前打印出后边的提示符.
#使用这些选项是有技巧的, 因为你需要用正确的顺序来使用它们.

read -s -n1 -p "Hit a key " keypress
echo; echo "Keypress was "\"$keypress\""."

#read -p "what?"
#echo $REPLY #this is your default input store variable.

