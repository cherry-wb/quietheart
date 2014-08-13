#! /bin/bash
#程序功能：检查参数个数是否为2个
#实践发现，arg数目不包括第0个参数（即脚本名称）
ARGS=2
if [ $# -ne "$ARGS" ]
then
echo "the number of args is $# but not 2"
else
echo "the number of args is $#"
fi
exit 0
