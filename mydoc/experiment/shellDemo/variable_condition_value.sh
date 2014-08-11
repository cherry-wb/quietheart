#!/bin/bash
#使用shell命令${PAGER:-more}表示：如果PAGER定义了并且非空，那就使用PAGER的值。否则就使用字符串string.
PAGER="less"
${PAGER:-more}
#${PAGER2:-more}
echo $PAGER
#echo $PAGER2
