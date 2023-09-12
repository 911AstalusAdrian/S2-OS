#!/bin/sh
for i in $@
do
  if test -d "$i"; then
    find "$i" -type f | while read f; do
      if file $f | grep -q "text"; then
        wc -w $f
      fi
    done
  fi
done
