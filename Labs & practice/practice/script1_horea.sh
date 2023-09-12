#!/bin/sh
#1. Write a bash script that calculates the sum of the sizes (in bytes)
# of all regular files in a folder given as a parameter.
#(use test to check if the folder exists and if a given file is a 
#regular file)
if [ -z $1 ]; then
  echo "Nothing given!"
  exit 1
fi

if [ ! -d $1 ]; then
  echo "Not a dir"
  exit 1
fi
sum=0
for F in `ls $1`; do
  if [ -f $1/$F ]; then 
    b=`cat $1/$F | wc -c` 
    sum=`expr $sum + $b`
  fi
done
echo $sum
