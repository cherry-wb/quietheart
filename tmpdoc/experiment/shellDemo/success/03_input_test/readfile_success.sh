#! /bin/bash
#程序功能：读取文件的前两行

{
	read line1
	read line2
}<$0
echo "the first two line of the $0 is:"
echo $line1
echo $line2
exit 0
