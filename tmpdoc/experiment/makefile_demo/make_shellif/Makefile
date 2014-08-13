对于makefile，在规则命令中写shell的分支容易出错，可以这样：
#######以下是Makefile内容
  1 all:
  2     @cd mydir && pwd 
  3     @cd mydir && echo $(PWD)
  4     @cd mydir && echo $$PWD
  5     @cd mydir && ./myset.sh
  6     @[ -f testfile ] && echo have good! || cd mydir && ./myset.sh
  7     @#[ -f good ] && echo have good! || cd mydir && ./myset.sh
  8     @if [ -f good ];then \
  9         echo have good! \
 10         ;echo have good! \
 11     ;else\
 12         cd mydir && ./myset.sh \
 13     ;fi
 14     @if [ -f testfile ];then \
 15         echo have good! \
 16     ;else\
 17         cd mydir && ./myset.sh \
 18     ;fi
 19     @[ -f good ] && echo good
 20     @[ -f testfile ] && echo good || :
#######以上是Makefile内容
运行以上makefile输出如下：
[root@quietheart make]# make
/root/test/make/mydir
/root/test/make
/root/test/make/mydir
hello!
hello!
have good!
have good!
hello!
good
这里，假设当前文件下实际有"good"没有"testfile"。需要注意的是，
第7行是错误的逻辑，在good存在的时候会提示找不到./myset.sh命令，所以用8-12行的if方式修正了。
第10行表示在一个分支中使用多条命令的话，需要以';'开始，否则由于续行表示与上面在一行，成了上一个命令参数了。
第19行实际是不正确的写法，尽管因为存在"good"，所以正确地输出了，但是如果没有"good"将会报错！
第20行，修正了18行的写法，当没有"testfile"文件时，执行"||"后面的":"也就是空命令。如果没有"||:"这里就会报错。
