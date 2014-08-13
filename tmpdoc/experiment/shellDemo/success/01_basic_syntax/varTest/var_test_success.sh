#!/bin/bash
#程序功能：检测变量是否被设置了。

#${parameter?err_msg} -- 如果parameter已经被声明, 那么就使用设置的值, 否则打印err_msg错误消息.
#${parameter:?err_msg} -- 如果parameter已经被设置, 那么就使用设置的值, 否则打印err_msg错误消息.

${var?"not set var"}
echo "can you see here?" #因没设置变量所以会打印错误并退出，不会执行到这里。
