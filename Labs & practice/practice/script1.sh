#!/bin/sh
#Display a report showing the full name of all the users currently connected, 
#and the number of processes belonging to each of them.
E=`who | awk '{print $1}' | sort | uniq`
for S in $E; do
  F=`finger -s $S | tail -n +2 | wc -l`
  echo $S $F
#  finger -s $S | tail -n +2 | wc -l
done
