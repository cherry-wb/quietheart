#! /bin/bash

#在else前面可以：elif [];then

 if cmp a b &> /dev/null  # 禁止输出.cmp逐字节比较文件，若a,b相同则cmp返回0
 then echo "Files a and b are identical."
 else echo "Files a and b differ."
 fi
 
 # 非常有用的"if-grep"结构:
 # ------------------------
 if grep -q Bash file #若找到则grep返回0
 then echo "File contains at least one occurrence of Bash."
 fi
 
 word=Linux
 letter_sequence=inu
 if echo "$word" | grep -q "$letter_sequence"
 # "-q" 选项是用来禁止输出的.
 then
   echo "$letter_sequence found in $word"
 else
   echo "$letter_sequence not found in $word"
 fi
 
 
 if COMMAND_WHOSE_EXIT_STATUS_IS_0_UNLESS_ERROR_OCCURRED
 then echo "Command succeeded."
 else echo "Command failed." #在机器上面返回的是这个
 fi

 nodefinevar=1 
 if nodefinevar
 then echo "var succeeded."
 else echo "var failed." #如果前面没有定义，或定义了没有赋值，或定义了赋值，都返回这个
 fi
