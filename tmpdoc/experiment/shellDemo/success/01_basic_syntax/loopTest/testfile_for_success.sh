#!/bin/bash
#程序功能：给出一个文件列表，利用循环测试这个文件列表中的文件是否存在

FILES="/usr/sbin/accept
/usr/sbin/pwck
/usr/sbin/chroot
/usr/bin/fakefile
/sbin/badblocks
/sbin/ypbind"     # 这是你所关心的文件列表.
                  # 扔进去一个假文件, /usr/bin/fakefile.

echo

for file in $FILES
do

  if [ ! -e "$file" ]       # 检查文件是否存在.
  then
    echo "$file does not exist."; echo
    continue                # 继续下一个.
   fi

  ls -l $file | awk '{ print $9 "         file size: " $5 }'  # 打印两个域.
  whatis `basename $file`   # 文件信息.
  # 注意whatis数据库需要提前建立好.
  # 要想达到这个目的, 以root身份运行/usr/bin/makewhatis.
  echo
done  

exit 0
