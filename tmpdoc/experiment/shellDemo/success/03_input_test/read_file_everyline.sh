#!/bin/bash
#读取文件的每一行并打印
while read __line;
do
echo $__line
done < "$0" 

