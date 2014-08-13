#!/bin/bash
#将命令的输出作为一个变量的值
echo $(date)
pwd #当前路径
echo $(cd ../;pwd) #父目录
pwd #当前路径
