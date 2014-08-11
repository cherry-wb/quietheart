#!/bin/bash
#程序功能：测试逻辑或和逻辑与的简单版本以及非。
if [ ! -e ./logical.sh ];then
	echo "logical.sh not exists"
else
	echo "logical.sh exists"
fi

[ -e ./logical.sh ] && echo "logical.sh really exists!"

if [ ! -e ./logical3.sh ];then
	echo "logical3.sh not exists"
else
	echo "logical3.sh exists"
fi

[ -e ./logical3.sh ] || echo "logical.sh really not exists!"
