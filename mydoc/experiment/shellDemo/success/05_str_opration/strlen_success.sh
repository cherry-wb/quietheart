#! /bin/bash
#程序功能：各种计算字符串长度的方法。
#注意这里直接使用变量，而不是$变量
 stringZ=abcABC123ABCabc
 
 echo ${#stringZ}                 # 15
 echo `expr length $stringZ`      # 15
 echo `expr "$stringZ" : '.*'`    # 15
