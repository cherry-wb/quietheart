 #!/bin/bash
 #程序功能：shift命令执行以后, $@将会保存命令行中剩余的参数, 但是没有之前的$1.
 # 使用 ./scriptname 1 2 3 4 5 来调用这个脚本
 
[ $# -ne 5 ] &&
{
	echo "Usage $0 1 2 3 4 5"
	exit 1
}
 echo "the whole arglist is: $@"    # 1 2 3 4 5
 shift
 echo "after shift the whole arglist is:$@"    # 2 3 4 5
 echo "after shift the first arg is:$1"
 shift
 echo "after shift the whole arglist is:$@"    # 3 4 5
 echo "after shift the first arg is:$1"
 
 # 每次"shift"都会丢弃$1.
 # "$@" 将包含剩下的参数. 
