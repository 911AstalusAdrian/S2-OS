#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
	char* s[3]= {"a","b","c"};
	int i;
	for(i=0;i<3;i++)
		if(fork()!=0)
			execl("/bin/echo","/bin/echo",s[i],NULL);
	return 0;
}
