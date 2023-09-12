#!/bin/sh
#Find recursively in a directory all ".c" files having more than 500 lines.
#Stop after finding 2 such files.
count=0
for F in `find $1 -type f -name "*.c"`; do
  if [ $count -eq 2 ]; then
	break;
  fi
  N=`cat $F | wc -l`
  if [ $N -gt 500 ]; then
    count=`expr $count + 1`
    echo $F
  fi
done
