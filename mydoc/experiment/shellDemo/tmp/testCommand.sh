#!/bin/sh
#查看命令的运行返回值,具体是查看一些文件在当前目录中是否存在

find moc* \
&&find *.o \
&&find *.moc
#ls | grep -q moc* \
#&& ls | grep -q *.o \
#&& ls | grep -q lib*.so* \
#&& ls | grep -q *.moc \
#&& ls | grep -q *.pro \
#&& ls | grep -q Makefile

#逆向的查找，就是不存在返回成功
#ls | grep -vq moc* \
#&& ls | grep -vq *.o \
#&& ls | grep -lvq lib*.so* \
#&& ls | grep -vq *.moc \
#&& ls | grep -vq *.pro \
#&& ls | grep -vq Makefile

#返回0表示查找成功
if [ $? -ne 0 ] 
then
	echo "files not exists"
	exit 1
fi
echo "ok!"
