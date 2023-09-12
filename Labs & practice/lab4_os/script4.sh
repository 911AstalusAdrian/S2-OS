#!/bin/sh
# same as script3 but with awk

awk '{
printf("%s ", $NF);
if(NF > 1){
for(i=2; i<=NF-1; i++){
	printf("%s ", $i);
}
printf("%s\n", $1); 
}
else
printf("\n");
}' f.txt
