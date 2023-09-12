#!/bin/sh
#Switch first col with last col using sed

sed -E "s/^([^  ]+) (.*) ([^ ]+)$/\3 \2 \1/" f.txt
