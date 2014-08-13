#!/bin/bash
#程序功能：字符串替换功能
#${string/substring/replacement}
#使用$replacement来替换第一个匹配的$substring.

#${string//substring/replacement}
#使用$replacement来替换所有匹配的$substring.

 stringZ=abcABC123ABCabc
 echo ${stringZ/abc/xyz}           # xyzABC123ABCabc
                                   # 使用'xyz'来替换第一个匹配的'abc'.
 echo ${stringZ//abc/xyz}          # xyzABC123ABCxyz
                                   # 用'xyz'来替换所有匹配的'abc'.


#${string/#substring/replacement}
#如果$substring匹配$string的开头部分, 那么就用$replacement来替换$substring.

#${string/%substring/replacement}
#如果$substring匹配$string的结尾部分, 那么就用$replacement来替换$substring.

 stringZ=abcABC123ABCabc
 echo ${stringZ/#abc/XYZ}          # XYZABC123ABCabc
                                   # 用'XYZ'替换开头的'abc'.
 echo ${stringZ/%abc/XYZ}          # abcABC123ABCXYZ
                                   # 用'XYZ'替换结尾的'abc'.
