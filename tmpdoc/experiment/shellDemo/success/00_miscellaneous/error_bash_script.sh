#!/bin/bash
#程序功能：查看shell脚本执行是有错误就一句也不执行还是执行到错误处才退出，还是只有错误的地方不执行。
echo test1
echo test2
eecho test3
helloworld #有这个和上面那行的错误，当作没有的命令，然后继续执行后面。
'';;;;--=-sasdlfkei #有这样的错误，一句也不会执行。
echo test4
