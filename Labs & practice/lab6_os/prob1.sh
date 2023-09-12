#!/bin/sh
if [ $# -lt 1 ]; then
	echo "Usage: $0 dir1 [dirs...]"
	exit 1
fi
for p in $@; do
	if [ -d "$p" ]; then
		find $p -type f | while read v; do
			ls -l $v | awk -v u=$USER '{if (index($u,$3)>0) print $0}'
		done | wc -l
	fi
done
