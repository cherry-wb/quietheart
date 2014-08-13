#!/bin/bash
myarray=(
a
b
c
d)
echo "index3:" ${myarray[3]}

arraylen=${#myarray[@]}
echo "len:" $arraylen

echo "iterate:"
for((i=0;i<arraylen;i=i+1))
do
    echo "$i is:" ${myarray[i]}
done
