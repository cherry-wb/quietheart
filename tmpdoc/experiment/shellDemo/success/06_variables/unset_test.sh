#!/bin/bash
#程序功能：unset一个变量
#unset命令用来删除一个shell变量, 这个命令的效果就是把这个变量设为null. 注意: 这个命令对位置参数无效.
variable=hello                       # 初始化.
echo "variable = $variable"

unset variable                       # Unset.
                                     # 与 variable= 效果相同.
echo "(unset) variable = $variable"  # $variable 设为 null.

exit 0
