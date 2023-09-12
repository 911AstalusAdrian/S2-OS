#!/bin/sh
echo Command: $0
echo Firsf 4 args: $1 $2 $3 $4
echo All args: $@
echo Arg count: $#

shift
echo Some args: $1 $2 $3 $4
echo All args: $@
echo Arg count: $#

shift 3
echo Some args: $1 $2 $3 $4
echo All args: $@
echo Arg count: $#
