#!/bin/bash
###the script use to delete comment

if [ -z "$1" ];then                  #检测是否输入了源文件
     echo "ipput the source file"
     exit 1
fi

postfix=`echo $1 |cut -f 2 -d '.'`   #取文件的后缀，以便根据不同的文件进行不同的处理

if [ -n "$2" ];then                  #存放处理源文件产生的信息的文件 
     target_file=$2                  #如果给出了就直接调用 
     touch ${target_file}
else
prefix=`echo $1|cut -f 1 -d '.' ` #如果没有给出的话则生成一个和源文件名字一样，但后缀为temp的文件
     target_file=${prefix}.temp
     touch ${target_file}
fi

case "postfix" in
          sh ) 
              echo "it is shell script !"
              sed 's/[[:space:]]#.*//g' $1 |sed '/^#/d'|\
              sed '/^[[:space:]]*$/d' | sed '/^$/d' >${target_file}
              echo "the source file is $1,target file is ${target_file}"
              ;;
       c|java)
              echo "c  or java program"
              sed 's/\/\*.*\*\///g' $1|sed '/\/\*/,/.*\*\//d' |\
              sed 's/\/\/.*//g' |\
              sed '/^[[:space:]]*$/d' |sed '/^$/d' >${target_file}
              echo "the source file is $1,target file is ${target_file}"
              ;;
        *)
              echo "unknown file type !"
              rm -f ${target_file}
              ;;
esac


//-------------------------

#!/bin/sh -f

function del_comment_file()
{
#C++模式注释的删除。
#Delete the line begins with //
#首先删除//在行首的行 
sed -i '/^[ \t]*\/\//d' $file

#Delete the line ends with //
#注意已经除去了 //在行首的情况,下面匹配除去URL的//部分,因为代码中有一部分中有
#URL，形如fun（"ftp://"）
sed -i 's/\/\/[^"]*//' $file

#删除以C语言中注释只在一行的行
sed -i 's/\/\*.*\*\///' $file

#Delete the lines between /* and */
#删除C语言中注释跨行的情况
sed -i '/^[ \t]*\/\*/,/.*\*\//d' $file
}


function del_comment()
{
#$Dir=`pwd`

for file in `ls`;do
case $file in
*.c )
del_comment_file
;;
*.cpp )
del_comment_file
;;
*.h )
del_comment_file
;;
* )
if [ -d $file ];then
cd $file
del_comment
cd ..
fi
;;
esac
done 
}

Dir=$1

if [ ! -e $Dir ];then
echo "The Directory isn't exist."
exit
fi

cd $Dir

del_comment
