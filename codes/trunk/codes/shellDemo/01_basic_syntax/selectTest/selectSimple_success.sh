#!/bin/bash
#程序功能：测试用select结构来建立一个菜单，select很象一个循环结构,无限次。

#select结构是建立菜单的另一种工具, 这种结构是从ksh中引入的.
#select variable [in list]
#do
# command...
# break
#done 

#语法和for的很类似
#如果忽略了in list列表, 那么select命令将会使用传递到脚本的命令行参数($@)
#注意: select命令使用PS3提示符, 默认为(#?), 当然, 这可以修改.

PS3='Choose your favorite vegetable: ' # 设置提示符字串.

echo

select vegetable in "beans" "carrots" "potatoes" "onions" "rutabagas"
do
  echo
  echo "Your favorite veggie is $vegetable."
  echo "Yuck!"
  echo
  break  # 如果这里没有 'break' 会发生什么?答案是不断地让你选择没有结束。
done

exit 0
