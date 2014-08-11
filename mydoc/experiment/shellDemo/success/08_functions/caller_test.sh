#!/bin/bash
#程序功能：测试caller内部命令的功能

#将caller命令放到函数中, 将会在stdout上打印出函数的调用者信息. 
#caller命令也可以在一个被source的脚本中返回调用者信息. 当然这个调用者就是source这个脚本的脚本. 就像函数一样, 这是一个"子例程调用".

function2()
{
	caller 0
}

function1 ()
{
  # 在 function1 () 内部.
  caller 0   # 显示调用者信息.
  function2
}

function1    # 脚本的第13行.

caller 0     # 没效果, 因为这个命令不在函数中. 

#输出
#./callerTest.sh
#19 main ./callerTest.sh
#16 function1 ./callerTest.sh

# ^                 函数调用者所在的行号.
#   ^^^^            从脚本的"main/function"部分开始调用的.
#        ^^^^^^^    调用脚本的名字.
