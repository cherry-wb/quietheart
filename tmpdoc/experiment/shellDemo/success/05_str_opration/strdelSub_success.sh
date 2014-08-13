#! /bin/bash
#程序功能：删除字符串中最长或者最短的匹配字符串。

#####从开头删除
#${string#substring}
#从$string的开头位置截掉最短匹配的$substring. 
#${string##substring}
#从$string的开头位置截掉最长匹配的$substring.

 stringZ=abcABC123ABCabc
 #       |----|
 #       |----------|
 
 echo ${stringZ#a*C}      # 123ABCabc
 # 截掉'a'到'C'之间最短的匹配字符串.
 
 echo ${stringZ##a*C}     # abc
 # 截掉'a'到'C'之间最长的匹配字符串.


######从结尾删除
# ${string%substring}
# 从$string的结尾位置截掉最短匹配的$substring. 
# ${string%%substring}
# 从$string的结尾位置截掉最长匹配的$substring. 

 stringZ=abcABC123ABCabc
 #                    ||
 #        |------------|
 
 echo ${stringZ%b*c}      # abcABC123ABCa
 # 从$stringZ的结尾位置截掉'b'到'c'之间最短的匹配.
 
 echo ${stringZ%%b*c}     # a
 # 从$stringZ的结尾位置截掉'b'到'c'之间最长的匹配. 
