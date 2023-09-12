#!/bin/sh
#Display all the mounted file systems who are either smaller than than 1GB or have less than 20% free space.
for E in `cat df.fake | tail -n +2 | awk '{print $2 $5 $6}'`; do
  F=`echo $E | awk -FM '{print $1}'`
  G=`echo $E | awk -FM '{print $2}' | awk -F% '{print $1}'`
  H=`echo $E | awk -F% '{print $2}'`
  if [ $F -lt 1024 ] || [ $G -gt 80 ]; then
  	echo $H
  fi
done
