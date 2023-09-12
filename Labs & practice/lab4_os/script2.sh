#!/bin/sh
#top 10 popular family names from etc/passwd

awk -F: 'BEGIN{
n = 0
}
{
split($5, a, " ");
if (f[a[1]] <= 0 ){
	names[n] = a[1];
	n++;
}
f[a[1]]++;
}
END{
for (i=0;i<n;i++){
	printf("%s -> %d\n",names[i], f[names[i]]); 
}
}
' /etc/passwd | sort -k3nr | head

