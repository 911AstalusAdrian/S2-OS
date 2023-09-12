#!/bin/sh
c=0
s=0
cat $1 | while read L; do
	s=`expr $s + $L`
	c=`expr $c + 1`
done
echo $s
echo $c
