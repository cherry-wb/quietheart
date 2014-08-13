#! /bin/bash
#程序的功能，检测参数的值
#";;"相当于break了。

#注意case后面有个in
case "$1" in
abc)  echo "\$1 = abc" ;;
xyz)  echo "\$1 = xyz" ;;
esac
exit 0
