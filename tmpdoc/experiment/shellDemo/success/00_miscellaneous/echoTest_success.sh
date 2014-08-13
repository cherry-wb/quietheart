#!/bin/bash
# background-loop.sh

for i in 1 2 3 4 5 6 7 8 9 10            # 第一个循环.
do
   echo -n "$i "
done & # 在后台运行这个循环.
       # 在第2个循环之后, 将在某些时候执行. 
echo   # 这个'echo'某些时候将不会显示.这句话是显示一个空行？ 
for i in 11 12 13 14 15 16 17 18 19 20   # 第二个循环.
do
   echo -n "$i "
done  
echo   # 这个'echo'某些时候将不会显示. 

