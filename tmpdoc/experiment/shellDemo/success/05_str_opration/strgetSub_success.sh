#! /bin/bash
#程序功能：提取字串中的子串(主要有三种方法)。

#####第1种
#1,${string:position}
#在$string中从位置$position开始提取子串.
#如果$string是"*"或者"@", 那么将会提取从位置$position开始的位置参数. [1]

#2,${string:position:length}
#在$string中从位置$position开始提取$length长度的子串.

#echo ${*:2}          # 打印出第2个和后边所有的位置参数.
#echo ${@:2}          # 同上.
#
#echo ${*:2:3}        # 从第2个开始, 连续打印3个位置参数. 

 stringZ=abcABC123ABCabc
 #       0123456789.....
 #       0-based indexing.
 
 echo ${stringZ:0}                            # abcABC123ABCabc
 echo ${stringZ:1}                            # bcABC123ABCabc
 echo ${stringZ:7}                            # 23ABCabc
 
 echo ${stringZ:7:3}                          # 23A
                                              # 提取子串长度为3.
 
 
 
 # 能不能从字符串的右边(也就是结尾)部分开始提取子串? 
     
 echo ${stringZ:-4}                           # abcABC123ABCabc
 # 默认是提取整个字符串, 就象${parameter:-default}一样.
 # 然而 . . .
 
 echo ${stringZ:(-4)}                         # Cabc 
 echo ${stringZ: -4}                          # Cabc
 # 这样, 它就可以工作了.
 # 使用圆括号或者添加一个空格可以"转义"这个位置参数.

####第２种
#使用expr substr $string $position $length进行匹配
 stringZ=abcABC123ABCabc
 #       123456789......
 #       以1开始计算.
 
 echo `expr substr $stringZ 1 2`              # ab
 echo `expr substr $stringZ 4 3`              # ABC

#####第3种
#注意不要于match相混淆，这里需要有()的。

#expr match "$string" '\($substring\)'
#从$string的开始位置提取$substring, $substring是正则表达式.
#expr "$string" : '\($substring\)'
#从$string的开始位置提取$substring, $substring是正则表达式. 
 stringZ=abcABC123ABCabc
 #       =======	    
 echo `expr match "$stringZ" '\(.[b-c]*[A-Z]..[0-9]\)'`   # abcABC1
 echo `expr "$stringZ" : '\(.[b-c]*[A-Z]..[0-9]\)'`       # abcABC1
 echo `expr "$stringZ" : '\(.......\)'`                   # abcABC1
 # 上边的每个echo都打印出相同的结果. 

#expr match "$string" '.*\($substring\)'
#从$string的结尾提取$substring, $substring是正则表达式. 
#expr "$string" : '.*\($substring\)'
#从$string的结尾提取$substring, $substring是正则表达式. 
stringZ=abcABC123ABCabc
#                ======
echo `expr match "$stringZ" '.*\([A-C][A-C][A-C][a-c]*\)'`    # ABCabc
echo `expr "$stringZ" : '.*\(......\)'`                       # ABCabc
