#!/bin/sh
#	Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma.
string=""
for E in `cat $1`; do
  email=`echo $E | sed -E "s/(.+)/\1@scs.ubbcluj.ro/"`
  string="$string,$email"
done
string=`echo $string | sed -E "s/(^,)//"`
string=`echo $string | sed -E "s/(,$)//"`
echo $string
