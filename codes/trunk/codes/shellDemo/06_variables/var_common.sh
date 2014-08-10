#!/bin/bash
#常用的一些变量

#当前进程id:
echo "current pid is $$"

#当前用户的id:
#测试是否当前是root用户
ROOT_UID=0     # $UID为0的时候,用户才具有root用户的权限
# 测试是否当前是root用户
if [ "$UID" -ne "$ROOT_UID" ]
then
	echo "Must be root to run this script."
	exit $E_NOTROOT
fi
