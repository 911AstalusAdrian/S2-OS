#!/bin/sh
#find recursively in a directory all the files that have write permissions for everyione. Display their names and the permissions before and after removing the write permissions for everybody. You will nered to use chmod's symbolic permissions mode, instead of the octal mode used in the class. The chmod manual for details
for F in `find $1 -type f`; do
  if [ -w $F ]; then
    echo `ls -l $F | awk '{print $1" "$9}'`
    chmod o-w $F
    echo `ls -l $F | awk '{print $1" "$9}'`
  fi
done
