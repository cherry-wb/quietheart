#!/bin/bash
#程序功能：一个测试exec命令效果的例子

#exec这个shell内建命令将使用一个特定的命令来取代当前进程. 一般的当shell遇到一个命令, 它会forks off一个子进程来真正的运行命令. 使用exec内建命令, shell就不会fork了, 并且命令的执行将会替换掉当前shell. 因此, 在脚本中使用时, 一旦exec所执行的命令执行完毕, 那么它就会强制退出脚本.

exec echo "hi,Exiting \"$0\"."   # 脚本应该在这里退出.

# ----------------------------------
# The following lines never execute.

echo "This echo will never echo."

exit 99                       #  脚本是不会在这里退出的.
                              #  脚本退出后会使用'echo $?'
                              #+ 来检查一下退出码.
                              #  一定 *不是* 99.
