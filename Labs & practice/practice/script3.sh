#!/bin/sh
#Find recursively in a directory all the files with the extension ".log"
#and sort their lines (replace the original file with thte sorted content)
for F in `find $1 -type f -name "*.log"`; do
  cat $F | sort > new.log | rm $F | mv new.log $F
done 
