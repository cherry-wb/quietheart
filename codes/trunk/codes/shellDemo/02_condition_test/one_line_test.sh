#!/bin/bash
#注意，这里MY_E变量不能为空。
#测试结果：
#$MY_E=3 ./one_line_test.sh
#输出"what?"
#$MY_E=3
#$./one_line_test.sh
#输出"good2"

[ -z $MY_E ] && MY_E=2
#只用一行来完成测试。
if [ $MY_E = "1" ]; then echo "good1"; elif [ $MY_E = "2" ]; then echo "good2"; else echo "what?"; fi
if [ $MY_E = "1" ]; then echo "good1"; echo "good11"; elif [ $MY_E = "2" ]; then echo "good2"; else echo "what?"; fi

