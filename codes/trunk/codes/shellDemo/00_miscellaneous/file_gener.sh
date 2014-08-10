#!/bin/bash
cat > myfile <<filecontent
This is the content of the file.
you can input any thing, with 
but \$ with \\
filecontent


#The command below run fdisk without shell intervention.
#fdisk "/dev/sdb1" << END
#n
#p
#1
#1
#+64M
#t
#e
#p
#w
#END
