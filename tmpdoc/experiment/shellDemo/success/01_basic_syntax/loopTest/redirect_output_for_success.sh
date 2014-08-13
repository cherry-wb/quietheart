 #!/bin/bash
 #功能：循环将目录中所有文件和连接文件名保存到一个文件中，这里用到了for的重定向输出

 # symlinks.sh: 列出目录中所有的符号链接文件.
 OUTFILE=symlinks.list                         # 保存符号链接文件名的文件
 
 directory=${1-`pwd`}
 #  如果没有其他特殊的指定,
 #+ 默认为当前工作目录.
 
 
#所有文件名字
 for file in `ls`
 do
 echo "$file"
 done |sort >>filename

 echo "symbolic links in directory \"$directory\"" > "$OUTFILE"
 echo "---------------------------" >> "$OUTFILE"

 
#所有符号连接文件名字
 for file in "$( find $directory -type l )"    # -type l = 符号链接
 do
   echo "$file"
 done | sort >> "$OUTFILE"                     # 循环的stdout
 #           ^^^^^^^^^^^^^                       重定向到一个文件中.
 
 exit 0
